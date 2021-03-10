#include "NodeChannel.h"

#include "Exceptions/InvalidArgumentException.h"
#include "Exceptions/InvalidChannelTreeException.h"

NodeChannel::NodeChannel(Channel* parent)
{
	try
	{
		setParent(parent);
	}
	catch (InvalidChannelTreeException& e)
	{
		throw e;
	}
}

NodeChannel::~NodeChannel()
{
	for(auto *child : children)
	{
		child->removeParent();
	}
	removeParent();
}

AudioBuffer NodeChannel::processFrames(int numFrames)
{
	// TODO change numChannels below when implementing mono/stereo channels.
	AudioBuffer toReturn(numFrames, 2);
	for(auto *child : children)
	{
		toReturn.addBuffer(child->processFrames(numFrames));
	}
	return toReturn;
}

bool NodeChannel::hasChild(const Channel* childToFind)
{
	return std::find(children.begin(), children.end(), 
		childToFind) != children.end();
}

void NodeChannel::addChild(Channel* newChild)
{
	if (hasChild(newChild))
		throw InvalidArgumentException();

	children.push_back(newChild);
}

void NodeChannel::removeChild(Channel* childToRemove)
{
	if (childToRemove == nullptr || !hasChild(childToRemove))
		throw InvalidArgumentException();

	children.erase(std::find(children.begin(), children.end(),
		childToRemove));
}
