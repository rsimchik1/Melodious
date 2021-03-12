#include "LeafChannel.h"
#include "Exceptions/InvalidChannelTreeException.h"

LeafChannel::LeafChannel(Channel* parent)
{
	// TODO parameterize audioSource when Track class is more fleshed out?
	audioSource = new Track();
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

AudioBuffer LeafChannel::processFrames(int numFrames, const Timeline &referenceTimeline)
{
	// TODO get frames from audioSource
	return AudioBuffer(numFrames, 2);
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
