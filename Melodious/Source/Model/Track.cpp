#include "Track.h"


#include "AudioClip.h"
#include "../Exceptions/InvalidArgumentException.h"

template <typename T>
Track<T>::Track(ClipReader<T> *reader)
{
	this->reader = reader;
}

template <typename T>
Track<T>::~Track()
{
	for (auto *clip : clips)
		delete clip;
	delete reader;
}

template <typename T>
Track<T>::Track(const Track& toCopy)
{
	std::copy(toCopy.clips.begin(), toCopy.clips.end(), clips.begin());
	this->reader = toCopy.reader;
}

template <typename T>
void Track<T>::insertClip(T* clip)
{
	clips.push_back(clip);
}

template <typename T>
void Track<T>::removeClip(T* clip)
{
	if (clip == nullptr || !hasClip(clip)) throw InvalidArgumentException();

	clips.erase(std::find(clips.begin(), clips.end(), clip));
}

template <typename T>
bool Track<T>::hasClip(T* clip)
{
	return std::find(clips.begin(), clips.end(), clip) != clips.end();
}

template <typename T>
AudioBuffer Track<T>::processFrames(int numFrames, const Timeline& relativeTime)
{
	auto startFrame = relativeTime.getPlaybackHead();
	auto endFrame = startFrame + numFrames;

	std::vector<T*> found;
	for (auto* clip : clips)
		if ((clip->getStartFrame() >= startFrame && clip->getStartFrame() <= endFrame) ||
			(clip->getEndFrame() >= startFrame && clip->getEndFrame() <= endFrame) ||
			(clip-> getStartFrame() < startFrame && clip->getEndFrame() > endFrame))
			found.push_back(clip);

	auto outBuffer = AudioBuffer(numFrames, 2);

	for (auto *clip : found)
	{
		reader->attachToClip(clip);
		reader->prepareToRead(numFrames, relativeTime.getSampleRate(), 2);
		outBuffer.addBuffer(reader->processFrames(numFrames, relativeTime));
	}

	return outBuffer;
}

template class Track<OscClip>;
template class Track<AudioClip>;
