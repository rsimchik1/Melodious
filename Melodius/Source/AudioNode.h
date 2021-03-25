#pragma once
#include "AudioBuffer.h"
#include "Timeline.h"

/**
 * Interface for any class that processes streams of audio data.
 */
class AudioNode
{
public:
	virtual ~AudioNode();
	/**
	 * Get a given number of output frames from this AudioNode.
	 *
	 * @throw InvalidArgumentException If numFrames is negative.
	 * @param numFrames The number of frames to process.
	 * @param relativeTime The timeline to reference when processing frames.
	 * @return An AudioBuffer containing the output frames.
	 */
	virtual AudioBuffer processFrames(int numFrames, const Timeline& relativeTime) = 0;
};

inline AudioNode::~AudioNode()
{
}
