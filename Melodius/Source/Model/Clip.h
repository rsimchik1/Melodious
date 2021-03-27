#pragma once
#include <cstdint>

#include "File.h"

/**
 * Bare Clip class containing the basic attributes of all clips. Not especially
 * useful on its own, but can be extended to include information specific to
 * different types of media (e.g. AudioClip, MIDIClip, VideoClip).
 *
 * @authors Richard Simchik
 */
class Clip
{
public:
	Clip();
	Clip(const Clip& toCopy);
	void setStartEndFrames(int32_t newStart, int32_t newEnd);
	int32_t getStartFrame();
	int32_t getEndFrame();
private:
	int32_t startFrame;
	int32_t endFrame;
};
