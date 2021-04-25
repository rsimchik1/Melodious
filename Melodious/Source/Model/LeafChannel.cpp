#include "LeafChannel.h"
#include "../Exceptions/InvalidChannelTreeException.h"

LeafChannel::LeafChannel(Channel* parent)
{
	audioSource = nullptr;
	try
	{
		setParent(parent);
	}
	catch (InvalidChannelTreeException e)
	{
		throw e;
	}
}

LeafChannel::~LeafChannel()
{
	removeParent();
	delete audioSource;
}

AudioBuffer LeafChannel::processFrames(int numFrames, const Timeline &relativeTime)
{
	auto output = (audioSource) ? 
		audioSource->processFrames(numFrames, relativeTime) :
		AudioBuffer(numFrames, 2);

	return modifiers->getModifiedBuffer(output);
}

void LeafChannel::setAudioSource(AudioNode *audioSource)
{
	delete this->audioSource;
	this->audioSource = audioSource;
}

bool LeafChannel::hasChild(const Channel* childToFind)
{
	return false;
}

void LeafChannel::addChild(Channel* newChild)
{
	throw InvalidChannelTreeException();
}

void LeafChannel::removeChild(Channel* childToRemove)
{
	throw InvalidChannelTreeException();
}
