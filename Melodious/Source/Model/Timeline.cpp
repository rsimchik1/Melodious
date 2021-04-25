#include "Timeline.h"


#include "../Exceptions/IndexOutOfBoundsException.h"
#include "../Exceptions/InvalidArgumentException.h"

Timeline::Timeline(int sampleRate)
{
	if (sampleRate <= 0) throw InvalidArgumentException();
	this->sampleRate = sampleRate;
	this->playbackLocation = 0;
}

int Timeline::getSampleRate() const
{
	return sampleRate;
}

uint64_t Timeline::getPlaybackHead() const
{
	return playbackLocation;
}

void Timeline::movePlaybackHead(uint64_t newLocation)
{
	playbackLocation = newLocation;
}

void Timeline::shiftPlaybackHead(int32_t offset)
{
	auto newVal = static_cast<int64_t>(playbackLocation) + offset;
	if (newVal < 0 || newVal > UINT32_MAX)
		throw IndexOutOfBoundsException();

	playbackLocation += offset;
}

float Timeline::getSamplesPerBeat(float beatsPerMinute)
{
	if (beatsPerMinute < 1 || beatsPerMinute > 500)
		throw InvalidArgumentException();

	float oneBeatPerSecond = 60.0;
	return (sampleRate / beatsPerMinute) * oneBeatPerSecond;
}
