#pragma once

/**
 * Container for concurrent audio samples.
 */
class AudioFrame
{
public:
	/**
	 * Create new AudioFrame with the given number of channels.
	 */
	AudioFrame(int numChannels);

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
	float readSampleAt(int channelIndex);

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
	int getNumChannels();
};