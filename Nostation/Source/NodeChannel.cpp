#include "NodeChannel.h"

NodeChannel::NodeChannel(Channel* parent)
{
}

NodeChannel::~NodeChannel()
{
}

AudioBuffer NodeChannel::processFrames(int numFrames)
{
	return AudioBuffer(numFrames, 2);
}

bool NodeChannel::hasChild(Channel* childToFind)
{
	return false;
}

void NodeChannel::addChild(const Channel* newChild)
{
}

void NodeChannel::removeChild(const Channel* childToRemove)
{
}
