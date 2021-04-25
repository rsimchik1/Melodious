#include "Clip.h"

#include "../Exceptions/InvalidArgumentException.h"

Clip::Clip()
{
	startFrame = endFrame = 0;
}

Clip::Clip(const Clip& toCopy)
{
	startFrame = toCopy.startFrame;
	endFrame = toCopy.endFrame;
}

void Clip::setStartEndFrames(uint64_t newStart, uint64_t newEnd)
{
	if (newEnd < newStart) throw InvalidArgumentException();
	startFrame = newStart;
	endFrame = newEnd;
}

uint64_t Clip::getStartFrame()
{
	return startFrame;
}

uint64_t Clip::getEndFrame()
{
	return endFrame;
}
