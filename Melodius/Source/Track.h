#pragma once
#include "AudioBuffer.h"
#include "AudioNode.h"
#include "AudioClip.h"
#include "ClipReader.h"

/**
 * Class for managing related audio clips.
 *
 * @authors Richard Simchik
 */
class Track : AudioNode
{
public:
	/**
	 * Create an empty Track.
	 */
	Track();

	/**
	 * Create a deep copy of another Track.
	 */
	Track(Track* other);

	/**
	 * Delete this Track, and all clips associated with it.
	 */
	~Track();

	AudioBuffer processFrames(int numFrames, const Timeline& relativeTime) override;
private:
	std::vector<AudioClip*> clips;
	ClipReader reader;
};
