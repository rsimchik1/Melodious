#include "AudioFile.h"

#include <filesystem>

#include "../Exceptions/FileAccessException.h"
#include "../Exceptions/FileFormatException.h"

const std::vector<std::string> AudioFile::SUPPORTED_EXTENSIONS 
	{ ".wav", ".mp3", ".ogg", ".flac", ".aif" };

bool AudioFile::isExtensionValid(const std::string &extension)
{
	auto arrBegin = SUPPORTED_EXTENSIONS.begin();
	auto arrEnd = SUPPORTED_EXTENSIONS.end();
	return std::find(arrBegin, arrEnd, extension) != arrEnd;
}

AudioFile::AudioFile(std::string absolutePath): File(absolutePath),
	currentlyOpen(false),
	readerBlockSize(-1),
	readerSampleRate(44100),
	readWriteHead(0),
	fileSampleRate(0),
	fileNumChannels(0),
	fileBitDepth(0)
{
	formatManager.registerBasicFormats();

	this->extension = std::filesystem::path(absolutePath).extension().string();
	if (!isExtensionValid(extension))
		throw FileFormatException();

	this->file = std::make_unique<juce::File>(juce::File(absolutePath));

	this->juceBuffer = std::make_unique<juce::AudioTransportSource>();

	if (file->exists())
		initializeRead();
}

AudioFile::~AudioFile()
{
}

void AudioFile::writeBlock(AudioBuffer block)
{
	if (!isOpen())
		throw FileAccessException();

	auto numFrames = block.getNumFrames();
	auto numChannels = block.getNumChannels();
	auto writeBuffer = juce::AudioBuffer<float>(numChannels,
												numFrames);
	for (auto channel = 0; channel < numChannels; channel++)
		for (auto frame = 0; frame < numFrames; frame++)
			writeBuffer.setSample(channel, frame, 
										 block.readSampleAt(frame, channel));

	writer->writeFromAudioSampleBuffer(writeBuffer, readWriteHead, numFrames);
	readWriteHead += numFrames;
	writer->flush();
	initializeRead();
}

AudioBuffer AudioFile::readFrames()
{
	if (!isOpen())
		throw FileAccessException();

	auto innerBuffer = juce::AudioBuffer<float>(readerNumChannels, readerBlockSize);
	auto readBuffer = juce::AudioSourceChannelInfo(innerBuffer);
	auto returnBuffer = AudioBuffer(readerBlockSize, readerNumChannels);

	transportSource->setNextReadPosition(readWriteHead);
	transportSource->getNextAudioBlock(readBuffer);
	for (auto channel = 0; channel < returnBuffer.getNumChannels(); channel++)
		for (auto frame = 0; frame < readerBlockSize; frame++)
			returnBuffer.writeSampleAt(frame, channel, 
									   readBuffer.buffer->getSample(channel, frame));

	readWriteHead += readerBlockSize;
	return returnBuffer;
}

void AudioFile::prepareToWrite(int sampleRate, int numChannels, int bitDepth)
{
	fileSampleRate = sampleRate;
	fileNumChannels = numChannels;
	fileBitDepth = bitDepth;
	initializeWrite(fileSampleRate, fileNumChannels, fileBitDepth);
}

void AudioFile::prepareToRead(int framesPerBlock, int sampleRate, int numChannels)
{
	readerBlockSize = framesPerBlock;
	readerSampleRate = sampleRate;
	readerNumChannels = numChannels;
	if (transportSource->isPlaying())
		transportSource->stop();
	transportSource->prepareToPlay(framesPerBlock, sampleRate);
	transportSource->start();
}

void AudioFile::moveToFrame(uint32_t frame)
{
	readWriteHead = frame;
}

void AudioFile::open()
{
	currentlyOpen = true;
}

void AudioFile::close()
{
	currentlyOpen = false;
}

bool AudioFile::isOpen()
{
	return currentlyOpen;
}

void AudioFile::createOnDisk()
{
	if (!file->existsAsFile())
	{
		if (!file->create())
			throw FileAccessException();
	}
}

void AudioFile::deleteFromDisk()
{
	if (file->existsAsFile())
	{
		writer.reset();
		moveToFrame(0);
		if (!file->deleteFile())
			throw FileAccessException();
	}
}

void AudioFile::initializeRead()
{
	auto* reader = formatManager.createReaderFor(*file);

	if (reader != nullptr)
	{
		transportSource = std::make_unique<juce::AudioTransportSource>();
		std::unique_ptr<juce::AudioFormatReaderSource> newSource(
			new juce::AudioFormatReaderSource(reader, true) );
		transportSource->setSource(newSource.get(), 0, nullptr, reader->sampleRate);
		readerSource.reset(newSource.release());
	}
}

void AudioFile::initializeWrite(int sampleRate, int numChannels, int bitDepth)
{
	auto format = formatManager.findFormatForFileExtension(extension);
	auto possibleSampleRates = format->getPossibleSampleRates();
	auto isSampleRateValid = possibleSampleRates.contains(sampleRate);
	auto possibleBitDepths = format->getPossibleBitDepths();
	auto isBitDepthValid = possibleBitDepths.contains(bitDepth);

	if (!isSampleRateValid || !isBitDepthValid)
		throw FileFormatException();
	
	writer = std::unique_ptr<juce::AudioFormatWriter>(
		format->createWriterFor(new juce::FileOutputStream(*file),
								sampleRate, numChannels,
								bitDepth, juce::StringPairArray(), 0));
	if (writer == nullptr)
		throw FileAccessException();
}
