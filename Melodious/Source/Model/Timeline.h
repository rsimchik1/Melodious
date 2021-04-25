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
	uint64_t getPlaybackHead() const;

	/**
	 * Move the current playback location to a new sample.
	 *
	 * @param newLocation The new playback location.
	 */
	void movePlaybackHead(uint64_t newLocation);

	/**
	 * Shift the playback location forward or backward by a given number of samples.
	 *
	 * @throw IndexOutOfBoundsException If the new location is less than zero or
	 * causes 32-bit integer overflow.
	 * @param offset The number of samples to shift.
	 */
	void shiftPlaybackHead(int32_t offset);

	/**
	 * Find the number of samples per beat at the given tempo.
	 *
	 * @throw InvalidArgumentException If the tempo is invalid.
	 * @param beatsPerMinute The tempo of the music.
	 *		  { 1 <= beatsPerMinute <= 500 }
	 * @return The number of samples in every beat. Represented as a float to
	 * maintain precision.
	 */
	float getSamplesPerBeat(float beatsPerMinute);
private:
	int sampleRate;
	uint64_t playbackLocation;
};
