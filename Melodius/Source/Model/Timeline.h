#pragma once
#include <cstdint>

/**
 * Class that is responsible for keeping time. Time is stored in samples.
 */
class Timeline
{
public:
	/**
	 * Create a new timeline with the playback head set to 0 samples.
	 *
	 * @param sampleRate The number of samples per second.
	 */
	Timeline(int sampleRate = 44100);

	/**
	 * Return the number of samples (frames) played per second.
	 */
	int getSampleRate() const;

	/**
	 * Return the current playback location.
	 *
	 * @return An integer representing the current sample.
	 */
	uint32_t getPlaybackHead() const;

	/**
	 * Move the current playback location to a new sample.
	 *
	 * @param newLocation The new playback location.
	 */
	void movePlaybackHead(uint32_t newLocation);

	/**
	 * Shift the playback location forward or backward by a given number of samples.
	 *
	 * @throw IndexOutOfBoundsException If the new location is less than zero or
	 * causes 32-bit integer overflow.
	 * @param offset The number of samples to shift.
	 */
	void shiftPlaybackHead(int32_t offset);
private:
	int sampleRate;
	uint32_t playbackLocation;
};
