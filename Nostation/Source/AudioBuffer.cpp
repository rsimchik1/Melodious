#include "AudioBuffer.h"
#include "Exceptions/InvalidFrameException.h"
#include "Exceptions/InvalidBufferException.h"
#include "Exceptions/InvalidSampleException.h"
#include "Exceptions/IndexOutOfBoundsException.h"

AudioBuffer::AudioBuffer(int numFrames, int numChannels)
{
}

AudioBuffer::~AudioBuffer()
{
}

AudioFrame AudioBuffer::readFrameAt(int frameIndex)
{
	return AudioFrame(2);
}

void AudioBuffer::writeFrameAt(int frameIndex, const AudioFrame& frame)
{
}

float AudioBuffer::readSampleAt(int frameIndex, int channelIndex)
{
	return 0.0f;
}

void AudioBuffer::writeSampleAt(int frameIndex, int channelIndex, float sample)
{
}

int AudioBuffer::getNumFrames()
{
	return 0;
}

int AudioBuffer::getNumChannels()
{
	return 0;
}
