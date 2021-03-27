#include "Clip.h"

Clip::Clip()
{
	startFrame = endFrame = 0;
}

Clip::Clip(const Clip& toCopy)
{
	startFrame = toCopy.startFrame;
	endFrame = toCopy.endFrame;
}

void Clip::setStartEndFrames(int32_t newStart, int32_t newEnd)
{
	// TODO check bounds
	startFrame = newStart;
	endFrame = newEnd;
}

int32_t Clip::getStartFrame()
{
	return startFrame;
}

int32_t Clip::getEndFrame()
{
	return endFrame;
}
