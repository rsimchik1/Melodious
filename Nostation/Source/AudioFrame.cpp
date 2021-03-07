#include "AudioFrame.h"

AudioFrame::AudioFrame(int numChannels)
{
}

AudioFrame::~AudioFrame()
{
}

float AudioFrame::readSampleAt(int channelIndex)
{
	return -1.0f;
}

void AudioFrame::writeSampleAt(int channelIndex, float sample)
{
}

int AudioFrame::getNumChannels()
{
	return -1;
}