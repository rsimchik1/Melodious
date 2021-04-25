#include "AudioClip.h"

AudioClip::AudioClip()
	: fileHandle(-1),
	  name("")
{}

AudioClip::~AudioClip()
{}

void AudioClip::setName(std::string name)
{
	this->name = name;
}

std::string AudioClip::getName()
{
	return name;
}

void AudioClip::setFileHandle(int handle)
{
	fileHandle = handle;
}

int AudioClip::getFileHandle()
{
	return fileHandle;
}
