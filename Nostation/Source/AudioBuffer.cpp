#include "AudioBuffer.h"
#include "Exceptions/InvalidFrameException.h"
#include "Exceptions/InvalidBufferException.h"
#include "Exceptions/InvalidSampleException.h"
#include "Exceptions/IndexOutOfBoundsException.h"

AudioBuffer::AudioBuffer(int numFrames, int numChannels)
{
	if (numFrames <= 0 || numChannels <= 0)
		throw InvalidBufferException();

	this->numChannels = numChannels;
	this->numFrames = numFrames;

	samples = new float[numFrames * numChannels];
	for (auto i = 0; i < numFrames * numChannels; i++)
		samples[i] = 0.0f;
}

AudioBuffer::~AudioBuffer()
{
	delete[] samples;
}

const AudioFrame AudioBuffer::readFrameAt(int frameIndex)
{
	if (!isFrameInBounds(frameIndex))
		throw IndexOutOfBoundsException();
	
	AudioFrame frame(getNumChannels());
	for (auto channel = 0; channel < numChannels; channel++)
		frame.writeSampleAt(channel, samples[getSampleIndex(frameIndex, channel)]);

	return frame;
}

void AudioBuffer::writeFrameAt(int frameIndex, const AudioFrame& frame)
{
	if (!isFrameValid(frame))
		throw InvalidFrameException();
	if (!isFrameInBounds(frameIndex))
		throw IndexOutOfBoundsException();

	for (auto channel = 0; channel < numChannels; channel++)
		samples[getSampleIndex(frameIndex, channel)] = frame.readSampleAt(channel);
}

float AudioBuffer::readSampleAt(int frameIndex, int channelIndex)
{
	if (!isFrameInBounds(frameIndex) || !isChannelInBounds(channelIndex))
		throw IndexOutOfBoundsException();

	return samples[getSampleIndex(frameIndex, channelIndex)];
}

void AudioBuffer::writeSampleAt(int frameIndex, int channelIndex, float sample)
{
	if (!isFrameInBounds(frameIndex) || !isChannelInBounds(channelIndex))
		throw IndexOutOfBoundsException();
	if (!isSampleValid(sample))
		throw InvalidSampleException();

	samples[getSampleIndex(frameIndex, channelIndex)] = sample;
}

int AudioBuffer::getNumFrames()
{
	return numFrames;
}

int AudioBuffer::getNumChannels()
{
	return numChannels;
}

bool AudioBuffer::isFrameInBounds(int frameIndex)
{
	return frameIndex >= 0 && frameIndex < numFrames;
}

bool AudioBuffer::isSampleValid(float sample)
{
	return sample >= -1 && sample <= 1;
}

bool AudioBuffer::isChannelInBounds(int channelIndex)
{
	return channelIndex >= 0 && channelIndex < numChannels;
}

bool AudioBuffer::isFrameValid(const AudioFrame& frame)
{
	return frame.getNumChannels() == getNumChannels();
}


int AudioBuffer::getSampleIndex(int frameIndex, int channelIndex)
{
	return channelIndex + frameIndex * numChannels;
}