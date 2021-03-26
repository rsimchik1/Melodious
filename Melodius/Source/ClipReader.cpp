#include "ClipReader.h"



#include "AudioClip.h"
#include "OscClip.h"
#include "Exceptions/InvalidArgumentException.h"

template <typename T>
void ClipReader<T>::attachToClip(T* clip)
{
	if (clip)
	{
		attachedClip = clip;
	}
	else throw InvalidArgumentException();
}

template class ClipReader<OscClip>;
template class ClipReader<AudioClip>;
