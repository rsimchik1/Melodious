#include "AudioFile.h"

AudioFile::AudioFile(std::string path)
{
}

AudioFile::~AudioFile()
{
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
