#include "AudioBuffer.h"
#include "../Exceptions/InvalidFrameException.h"
#include "../Exceptions/InvalidBufferException.h"
#include "../Exceptions/InvalidSampleException.h"
#include "../Exceptions/IndexOutOfBoundsException.h"
#include "../Exceptions/InvalidArgumentException.h"

float AudioBuffer::clipSample(float sample)
{
	if (sample > 1.0f)
		sample = 1.0f;
	if (sample < -1.0f)
		sample = -1.0f;
	return sample;
}

AudioBuffer::AudioBuffer(int numFrames, int numChannels)
{
	if (numFrames <= 0 || numChannels <= 0)
		throw InvalidBufferException();

	this->numChannels = numChannels;
	this->numFrames = numFrames;

	samples = std::vector<float>(numFrames * numChannels);
	for (auto i = 0; i < numFrames * numChannels; i++)
		samples[i] = 0.0f;
}

AudioBuffer::AudioBuffer(const AudioBuffer& toCopy)
{
	this->numChannels = toCopy.numChannels;
	this->numFrames = toCopy.numFrames;

	samples = std::vector<float>(numFrames * numChannels);
	std::copy(std::begin(toCopy.samples), std::end(toCopy.samples), std::begin((samples)));
}

AudioFrame AudioBuffer::readFrameAt(int frameIndex) const
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

float AudioBuffer::readSampleAt(int frameIndex, int channelIndex) const
{
	if (!isFrameInBounds(frameIndex) || !isChannelInBounds(channelIndex))
		throw IndexOutOfBoundsException();

	return samples[getSampleIndex(frameIndex, channelIndex)];
}

void AudioBuffer::writeSampleAt(int frameIndex, int channelIndex, float sample)
{
	if (!isFrameInBounds(frameIndex) || !isChannelInBounds(channelIndex))
		throw IndexOutOfBoundsException();
	
	sample = clipSample(sample);

	samples[getSampleIndex(frameIndex, channelIndex)] = sample;
}

void AudioBuffer::addBuffer(const AudioBuffer& otherBuffer)
{
	if (otherBuffer.numFrames != this->numFrames || 
		otherBuffer.numChannels != this->numChannels)
	{
		throw InvalidArgumentException();
	}
	else
	{
		for (int i = 0; i < numFrames * numChannels; i++)
		{
			this->samples[i] = clipSample(this->samples[i] + otherBuffer.samples[i]);
		}
	}
}

int AudioBuffer::getNumFrames() const
{
	return numFrames;
}

int AudioBuffer::getNumChannels() const
{
	return numChannels;
}

bool AudioBuffer::isFrameInBounds(int frameIndex) const
{
	return frameIndex >= 0 && frameIndex < numFrames;
}

bool AudioBuffer::isSampleValid(float sample) const
{
	return sample >= -1 && sample <= 1;
}

bool AudioBuffer::isChannelInBounds(int channelIndex) const
{
	return channelIndex >= 0 && channelIndex < numChannels;
}

bool AudioBuffer::isFrameValid(const AudioFrame& frame) const
{
	return frame.getNumChannels() == getNumChannels();
}


int AudioBuffer::getSampleIndex(int frameIndex, int channelIndex) const
{
	return channelIndex + frameIndex * numChannels;
}