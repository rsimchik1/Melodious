#pragma once
#include "AudioNode.h"
#include "Clip.h"

template<typename T = Clip>
class ClipReader : public AudioNode
{
public:
	/**
	 * Set the clip object to be read. If the clip is already attached, nothing
	 * will be changed.
	 *
	 * @throw InvalidArgumentException If the input is null.
	 * @param clip The clip to be read.
	 */
	void attachToClip(T* clip);

	virtual AudioBuffer processFrames(int numFrames, const Timeline& relativeTime) override = 0;
protected:
	T* attachedClip;
};
