#include "LeafChannel.h"

LeafChannel::LeafChannel(Channel* parent)
{
}

LeafChannel::~LeafChannel()
{
}

AudioBuffer LeafChannel::processFrames(int numFrames)
{
	return AudioBuffer(numFrames, 2);
}

bool LeafChannel::hasChild(Channel* childToFind)
{
	return false;
}

void LeafChannel::addChild(const Channel* newChild)
{
}

void LeafChannel::removeChild(const Channel* childToRemove)
{
}
