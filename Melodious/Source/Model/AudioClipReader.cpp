#include "AudioClipReader.h"

#include "../Exceptions/InvalidArgumentException.h"

AudioClipReader::AudioClipReader(FileManager* manager)
	: fileManager(manager),
	currentFile(nullptr)
{}

AudioBuffer AudioClipReader::processFrames(int numFrames,
	const Timeline& relativeTime)
{
	if (attachedClip && currentFile)
	{
		try
		{
			// TODO account for a ton of shit
			currentFile->moveToFrame(relativeTime.getPlaybackHead());
			auto result = currentFile->readFrames();
			return result;
		}
		catch (std::exception& e) { throw e; }
	}

	else throw InvalidArgumentException();
}

void AudioClipReader::attachToClip(AudioClip* clip)
{
	ClipReader::attachToClip(clip);
	try
	{
		auto *newFile = static_cast<AudioFile*>(fileManager->getFile(
			attachedClip->getFileHandle()));
		if (currentFile != newFile)
		{
			if (currentFile) currentFile->close();
			currentFile = newFile;
			currentFile->open();
		}
	}
	catch (std::exception& e) { throw e; }
}

void AudioClipReader::prepareToRead(int blockSize, int sampleRate,
	int numChannels)
{
	if (this->blockSize != blockSize || this->sampleRate != sampleRate || this->numChannels != numChannels)
	{
		this->blockSize = blockSize;
		this->sampleRate = sampleRate;
		this->numChannels = numChannels;
		
		if (currentFile)
			currentFile->prepareToRead(blockSize, sampleRate, numChannels);
	}
}
