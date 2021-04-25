#include "ClipReader.h"



#include "AudioClip.h"
#include "OscClip.h"
#include "../Exceptions/InvalidArgumentException.h"

template <typename T>
void ClipReader<T>::attachToClip(T* clip)
{
	if (clip)
	{
		attachedClip = clip;
	}
	else throw InvalidArgumentException();
}

template <typename T>
void ClipReader<T>::prepareToRead(int blockSize, int sampleRate,
	int numChannels)
{
	this->blockSize = blockSize;
	this->sampleRate = sampleRate;
	this->numChannels = numChannels;
}

template class ClipReader<OscClip>;
template class ClipReader<AudioClip>;
