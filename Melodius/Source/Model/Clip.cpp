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

void Clip::setStartEndFrames(uint32_t newStart, uint32_t newEnd)
{
	if (newEnd < newStart) throw InvalidArgumentException();
	startFrame = newStart;
	endFrame = newEnd;
}

uint32_t Clip::getStartFrame()
{
	return startFrame;
}

uint32_t Clip::getEndFrame()
{
	return endFrame;
}
