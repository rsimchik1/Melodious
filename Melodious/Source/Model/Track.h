#pragma once
#include "AudioBuffer.h"
#include "AudioNode.h"
#include "Clip.h"
#include "ClipReader.h"
#include "OscClip.h"

/**
 * Class for managing related clips. Can only store one type of clip.
 *
 * @param <T> The type of clip that will be stored in this track.
 * @authors Richard Simchik
 */
template <typename T = Clip>
class Track : public AudioNode
{
public:
	/**
	 * Create an empty track.
	 *
	 * @param reader The ClipReader to use to convert clips to a waveform.
	 */
	Track(ClipReader<T> *reader);

	/**
	 * Delete this track and all contained clip objects.
	 */
	~Track();

	/**
	 * Make a deep copy of another track.
	 *
	 * @param toCopy The track to copy.
	 */
	Track(const Track& toCopy);
	
	/**
	 * Insert an existing clip into this track.
	 *
	 * @param clip The clip to insert.
	 */
	void insertClip(T* clip);

	/**
	 * Remove a clip contained in this track. The clip object will not be deleted.
	 *
	 * @param clip The clip to remove.
	 */
	void removeClip(T* clip);

	/**
	 * Determine whether this track contains the given clip.
	 *
	 * @param clip The clip to search for.
	 * @return true if the clip is found, false otherwise.
	 */
	bool hasClip(T* clip);
	
	AudioBuffer processFrames(int numFrames, const Timeline& relativeTime) override;
private:
	std::vector<T *> clips;
	ClipReader<T> *reader;
};
