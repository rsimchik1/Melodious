#pragma once
#include <iostream>

#include "Clip.h"
#include "../Utils/AudioFile.h"

class AudioClip : public Clip
{
public:
	AudioClip();
	~AudioClip();
	void setName(std::string name);
	std::string getName();
	void setFileHandle(int handle);
	int getFileHandle();
private:
	std::string name;
	int fileHandle;
};
