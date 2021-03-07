#pragma once
#include "AudioFrame.h"

/**
 * Standard n-dimensional container for streams of audio data
 * (n = number of channels).
 *
 * Smallest unit of audio data is a sample, a single float that represents air
 * pressure at a point in time. A frame contains one or more samples that occur
 * at the same time. A mono (1-channel) audio frame contains one sample, and a
 * stereo (2-channel) audio frame contains two samples.
 *
 * All frames in an AudioBuffer must contain the same number of
 * samples/channels. An AudioBuffer's size is fixed at instantiation.
 *
 * @authors Richard Simchik
 */
class AudioBuffer
{
public:
	/**
	 * Create a new AudioBuffer of fixed size {numFrames * numChannels}.
	 *
	 * @throw InvalidBufferException If numFrames <=0 or numChannels <= 0.
	 */
	AudioBuffer(int numFrames, int numChannels);

	/**
	 * Delete this AudioBuffer.
	 */
	~AudioBuffer();
	
	/**
	 * Return a frame containing sample(s) at the given index.
	 *
	 * @throw IndexOutOfBoundsException If the index is not contained by this
	 * buffer.
	 * @param frameIndex Index of the frame to be read.
	 * @return An AudioFrame object containing 
	 */
	const AudioFrame readFrameAt(int frameIndex);

	/**
	 * Set frame at the given index.
	 *
	 * @throw InvalidFrameException If the number of channels in frame does not
	 * match number of channels in buffer.
	 * @throw IndexOutOfBoundsException If frameIndex is less than zero or too
	 * large for this buffer.
	 * @param frameIndex Index at which the frame will be written.
	 * @param frame The frame to be written to this buffer.
	 */
	void writeFrameAt(int frameIndex, const AudioFrame& frame);

	/**
	 * Return the individual sample at the given frame and channel index.
	 *
	 * @throw IndexOutOfBoundsException If frameIndex or channelIndex is less
	 * than zero or too large for this buffer.
	 * @param frameIndex Index of the frame containing the sample.
	 * @param channelIndex of the channel containing the sample.
	 * @return The sample (float) at the given indexes.
	 */
	float readSampleAt(int frameIndex, int channelIndex);

	/**
	 * Write an individual sample at the given frame and channel index.
	 *
	 * @throw IndexOutOfBoundsException If frameIndex or channelIndex is less
	 * than zero or too large for this buffer.
	 * @throw InvalidSample If sample is less than -1 or greater than 1.
	 * @param frameIndex Index of the frame to which the sample will be written.
	 * @param channelIndex Index of the channel to which the sample will be
	 * written.
	 */
	void writeSampleAt(int frameIndex, int channelIndex, float sample);

	/**
	 * Get the total number of frames in this buffer.
	 *
	 * @return The number of frames.
	 */
	int getNumFrames();

	/**
	 * Get the number of channels in this buffer.
	 *
	 * @return The number of channels.
	 */
	int getNumChannels();
private:
	int numChannels;
	int numFrames;
	float* samples;	// 1-dim for quick access - client can use frames if needed

	bool isFrameInBounds(int frameIndex);
	bool isSampleValid(float sample);
	bool isChannelInBounds(int channelIndex);
	bool isFrameValid(const AudioFrame& frame);
	int getSampleIndex(int frameIndex, int channelIndex);
};