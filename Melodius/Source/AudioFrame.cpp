#include "AudioFrame.h"
#include "Exceptions/IndexOutOfBoundsException.h"
#include "Exceptions/InvalidFrameException.h"
#include "Exceptions/InvalidSampleException.h"

AudioFrame::AudioFrame(int numChannels)
{
	if (numChannels <= 0)
		throw InvalidFrameException();
	
	this->numChannels = numChannels;
	samples = new float[numChannels];
	for (auto i = 0; i < numChannels; i++)
		samples[i] = 0.0f;
}

AudioFrame::AudioFrame(const AudioFrame& toCopy)
{
	this->numChannels = toCopy.numChannels;
	samples = new float[numChannels];
	for (auto i = 0; i < numChannels; i++)
		samples[i] = toCopy.samples[i];
}

AudioFrame::~AudioFrame()
{
	delete[] samples;
}

float AudioFrame::readSampleAt(int channelIndex) const
{
	if (!isChannelInBounds(channelIndex)) 
		throw IndexOutOfBoundsException();
	
	return samples[channelIndex];
}

void AudioFrame::writeSampleAt(int channelIndex, float sample)
{
	if (!isChannelInBounds(channelIndex))
		throw IndexOutOfBoundsException();
	if (!isSampleInBounds(sample))
		throw InvalidSampleException();

	samples[channelIndex] = sample;
}

int AudioFrame::getNumChannels() const
{
	return numChannels;
}

bool AudioFrame::isChannelInBounds(int channelIndex) const
{
	return channelIndex >= 0 && channelIndex < getNumChannels();
}

bool AudioFrame::isSampleInBounds(float sample) const
{
	return sample >= -1.0f && sample <= 1.0f;
}
