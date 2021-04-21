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

AudioFile::AudioFile(std::string absolutePath): File(absolutePath)
{
	this->extension = std::filesystem::path(absolutePath).extension().string();
	if (!isExtensionValid(extension))
		throw FileFormatException();

	this->file = std::make_unique<juce::File>(juce::File(absolutePath));
	this->formatManager = new juce::AudioFormatManager();
	formatManager->registerBasicFormats();
	this->format = formatManager->findFormatForFileExtension(extension);

	if (file->exists())
		initializeRead();
}

AudioFile::~AudioFile()
{
	delete formatManager;
}

void AudioFile::writeBuffer(AudioBuffer buffer)
{
}

AudioBuffer AudioFile::readFrames(int numFrames)
{
	return AudioBuffer(numFrames, 2);
}

void AudioFile::moveToFrame(uint32_t frame)
{
}

void AudioFile::open()
{
}

void AudioFile::close()
{
}

bool AudioFile::isOpen()
{
	return false;
}

void AudioFile::createOnDisk()
{
	if (!file->exists())
	{
		file->create();
		try
		{
			initializeWrite(48000, 2, 24);
			initializeRead();
		}
		catch (std::exception& e) { throw e; }
	}
}

void AudioFile::deleteFromDisk()
{
	if (file->exists())
	{
		file->deleteFile();
		writer.release();
		writeStream.release();
		reader.release();
		readStream.release();
		moveToFrame(0);
	}
}

void AudioFile::initializeRead()
{
	readStream = file->createInputStream();

	reader = std::unique_ptr<juce::AudioFormatReader>(
		(format->createReaderFor(readStream.get(), false)));

	if (reader == nullptr )
		throw FileAccessException();
}

void AudioFile::initializeWrite(int sampleRate, int numChannels, int bitDepth)
{
	writeStream = file->createOutputStream();

	auto possibleSampleRates = format->getPossibleSampleRates();
	auto isSampleRateValid = possibleSampleRates.contains(sampleRate);
	auto possibleBitDepths = format->getPossibleBitDepths();
	auto isBitDepthValid = possibleBitDepths.contains(bitDepth);

	if (!isSampleRateValid || !isBitDepthValid)
		throw FileFormatException();
	
	writer = std::unique_ptr<juce::AudioFormatWriter>(
		format->createWriterFor(writeStream.get(),
								sampleRate, numChannels,
								bitDepth, {}, 0));
	if (writer == nullptr)
		throw FileAccessException();
}
