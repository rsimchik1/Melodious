#include "OscClipReader.h"

AudioBuffer OscClipReader::processFrames(int numFrames, const Timeline& relativeTime)
{
	auto outBuffer = AudioBuffer(numFrames, 2);
	auto playbackStart = relativeTime.getPlaybackHead();
	auto playbackEnd = playbackStart + numFrames;
	auto startSample = (attachedClip->getStartFrame() <= playbackStart) ?
		0 : attachedClip->getStartFrame() - playbackStart;
	auto endSample = (attachedClip->getEndFrame() >= playbackEnd) ?
		numFrames : playbackEnd - attachedClip->getEndFrame();
	for (auto sample = startSample; sample < endSample; sample++)
	{
		float frequencyOffset = ((relativeTime.getPlaybackHead() + sample) % 
			relativeTime.getSampleRate()) * 0.01;
		for (int channel = 0; channel < outBuffer.getNumChannels(); channel++)
		{
			outBuffer.writeSampleAt(sample, channel, 
				std::sin(attachedClip->getPhase()) * attachedClip->getAmplitude());
		}
		attachedClip->incrementPhase(relativeTime.getSampleRate());
	}

	return outBuffer;
}
