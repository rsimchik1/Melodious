#pragma once
#include <cstdint>

#include "../Utils/File.h"

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
	/**
	 * Create a new clip that starts and ends at frame 0.
	 */
	Clip();

	/**
	 * Copy the given clip.
	 */
	Clip(const Clip& toCopy);

	/**
	 * Set the start and end frames of this clip.
	 *
	 * @throw InvalidArgumentException If newEnd < newStart.
	 * @param newStart The new starting sample of this clip.
	 * @param newEnd The new ending sample of this clip.
	 */
	void setStartEndFrames(uint32_t newStart, uint32_t newEnd);

	/**
	 * Get the start frame of this clip.
	 *
	 * @return The start frame of this clip.
	 */
	uint32_t getStartFrame();

	/**
	 * Get the end frame of this clip.
	 *
	 * @return The end frame of this clip.
	 */
	uint32_t getEndFrame();
private:
	uint32_t startFrame;
	uint32_t endFrame;
};
