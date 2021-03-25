#include "Timeline.h"

Timeline::Timeline(int sampleRate)
{
	this->sampleRate = sampleRate;
}

int Timeline::getSampleRate() const
{
	return sampleRate;
}
