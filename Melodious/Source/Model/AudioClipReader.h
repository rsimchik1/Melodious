#pragma once
#include "AudioClip.h"
#include "ClipReader.h"
#include "../Utils/FileManager.h"

class AudioClipReader : public ClipReader<AudioClip>
{
public:
	AudioClipReader(FileManager* manager);
	AudioBuffer processFrames(int numFrames, const Timeline& relativeTime) override;
	void attachToClip(AudioClip* clip) override;
	void prepareToRead(int blockSize, int sampleRate, int numChannels) override;
private:
	FileManager* fileManager;
	AudioFile* currentFile;
};
