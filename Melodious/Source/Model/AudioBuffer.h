#pragma once
#include "AudioFrame.h"

#include <vector>

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
 * TODO allow conversions between buffers of different dimensions
 *
 * @authors Richard Simchik
 */
class AudioBuffer
{
public:
	/**
	 * Truncate samples that fall outside of the range -1 -> 1.
	 *
	 * @param sample The sample to clip.
	 * @return A sample between -1 and 1.
	 */
	static float clipSample(float sample);

	/**
	 * Create a new AudioBuffer of fixed size {numFrames * numChannels}.
	 *
	 * @throw InvalidBufferException If numFrames <=0 or numChannels <= 0.
	 */
	AudioBuffer(int numFrames, int numChannels);

	AudioBuffer(const AudioBuffer& toCopy);
	
	/**
	 * Return a frame containing sample(s) at the given index.
	 *
	 * @throw IndexOutOfBoundsException If the index is not contained by this
	 * buffer.
	 * @param frameIndex Index of the frame to be read.
	 * @return An AudioFrame object containing 
	 */
	AudioFrame readFrameAt(int frameIndex) const;

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
	float readSampleAt(int frameIndex, int channelIndex) const;

	/**
	 * Write an individual sample at the given frame and channel index. If the
	 * sample is out of the range -1 -> 1, it will be truncated.
	 *
	 * @throw IndexOutOfBoundsException If frameIndex or channelIndex is less
	 * than zero or too large for this buffer.
	 * @param frameIndex Index of the frame to which the sample will be written.
	 * @param channelIndex Index of the channel to which the sample will be
	 * written.
	 * @param sample Value of the sample to be written.
	 */
	void writeSampleAt(int frameIndex, int channelIndex, float sample);

	/**
	 * Add all samples in otherBuffer to this buffer's samples. If the sum falls
	 * outside of the range -1 -> 1, it will be truncated.
	 * a[i] += b[i]
	 *
	 * @throw InvalidArgumentException If otherBuffer's dimensions do not match
	 * this buffer's dimensions.
	 * @param otherBuffer Buffer whose samples will be added to this buffer's
	 * samples.
	 */
	void addBuffer(const AudioBuffer& otherBuffer);

	/**
	 * Get the total number of frames in this buffer.
	 *
	 * @return The number of frames.
	 */
	int getNumFrames() const;

	/**
	 * Get the number of channels in this buffer.
	 *
	 * @return The number of channels.
	 */
	int getNumChannels() const;
private:
	int numChannels;
	int numFrames;
	std::vector<float> samples;	// 1-dim for internal quick access

	bool isFrameInBounds(int frameIndex) const;
	bool isSampleValid(float sample) const;
	bool isChannelInBounds(int channelIndex) const;
	bool isFrameValid(const AudioFrame& frame) const;
	int getSampleIndex(int frameIndex, int channelIndex) const;
};