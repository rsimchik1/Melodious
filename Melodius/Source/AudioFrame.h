#pragma once

#include <iostream>

/**
 * Container for concurrent audio samples.
 *
 * @authors Richard Simchik
 */
class AudioFrame
{
public:
	/**
	 * Create new AudioFrame with the given number of channels.
	 *
	 * @throw InvalidFrameException If numChannels is not greater than zero.
	 */
	AudioFrame(int numChannels);

	/**
	 * Creates a copy of the passed AudioFrame.
	 *
	 * @param AudioFrame to copy.
	 */
	AudioFrame(const AudioFrame& toCopy);

	/**
	 * Delete this AudioFrame.
	 */
	~AudioFrame();

	/**
	 * Read the sample at a given channelIndex.
	 *
	 * @throw IndexOutOfBoundsException If channelIndex is less than zero or too
	 * large for this frame.
	 * @param channelIndex Index of the channel to be read.
	 * @return The sample at the given index.
	 */
	float readSampleAt(int channelIndex) const;

	/**
	 * Write a given sample to a given channel.
	 *
	 * @throw IndexOutOfBoundsException If channelIndex is less than zero or too
	 * large for this frame.
	 * @throw InvalidSampleException If sample is less than -1 or greater than 1.
	 * @param channelIndex Index of the channel to which the sample will be
	 * written.
	 * @param sample The sample to write.
	 */
	void writeSampleAt(int channelIndex, float sample);

	/**
	 * Get the number of channels in this frame.
	 *
	 * @return The number of channels.
	 */
	int getNumChannels() const;
private:
	float* samples;
	int numChannels;

	bool isChannelInBounds(int channelIndex) const;
	bool isSampleInBounds(float sample) const;
};