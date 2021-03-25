#include "ChannelMixer.h"

#include "LeafChannel.h"
#include "Exceptions/IndexOutOfBoundsException.h"
#include "Exceptions/InvalidChannelTreeException.h"

ChannelMixer::ChannelMixer()
{
	rootChannel = new NodeChannel();
}

ChannelMixer::~ChannelMixer()
{
	for (auto i = 0; i < channels.size(); i++)
		delete channels[i];
	channels.clear();
	delete rootChannel;
}

AudioBuffer ChannelMixer::processFrames(int numFrames, const Timeline& relativeTime)
{
	return rootChannel->processFrames(numFrames, relativeTime);
}

int ChannelMixer::getNumChannels() const
{
	return channels.size();
}

void ChannelMixer::createAudioChannel(int index)
{
	auto *newChannel = new LeafChannel();
	try { insertChannel(index, newChannel); }
	catch (const std::exception& e)
	{
		delete newChannel;
		throw e;
	}
}

void ChannelMixer::createBusChannel(int index)
{
	auto *newChannel = new NodeChannel();
	try { insertChannel(index, newChannel); }
	catch (const std::exception& e)
	{
		delete newChannel;
		throw e;
	}
}

void ChannelMixer::deleteChannel(int index)
{
	if (!isIndexInRange(index)) throw IndexOutOfBoundsException();
	auto *toDelete = channels[index];
	for (auto i = 0; i < channels.size(); i++)
		if (toDelete->hasChild(channels[i]))
			channels[i]->setParent(rootChannel);
	channels.erase(channels.begin() + index);
	delete toDelete;
}

void ChannelMixer::moveChannelToIndex(int fromIndex, int toIndex)
{
	if (!isIndexInRange(fromIndex) || !isIndexInRange(toIndex))
		throw IndexOutOfBoundsException();

	std::move(channels.begin() + fromIndex, channels.begin() + fromIndex,
		channels.begin() + toIndex);
}

void ChannelMixer::connectChannels(int sourceIndex, int destinationIndex)
{
	if (!isIndexInRange(sourceIndex) || !isIndexInRange(destinationIndex))
		throw IndexOutOfBoundsException();

	try { channels[sourceIndex]->setParent(channels[destinationIndex]); }
	catch (const std::exception& e)
	{
		throw e;
	}
}

void ChannelMixer::connectToMasterOutput(int sourceIndex)
{
	if (!isIndexInRange(sourceIndex)) throw IndexOutOfBoundsException();

	try { channels[sourceIndex]->setParent(rootChannel); }
	catch (const std::exception& e) { throw e; }
}

Channel *ChannelMixer::getChannelAt(int index)
{
	if (!isIndexInRange(index)) throw IndexOutOfBoundsException();

	return channels[index];
}

void ChannelMixer::insertChannel(int index, Channel* channel)
{
	if (index > 0 && index > channels.size()) 
		throw IndexOutOfBoundsException();
	if (index == channels.size()) index = -1;	// assumes user wants to append
	try { channel->setParent(rootChannel); }
	catch (InvalidChannelTreeException e) { throw e; }
	if (index < 0) 
		channels.push_back(channel);
	else
		channels.insert(std::begin(channels) + index, channel);
}

bool ChannelMixer::isIndexInRange(int index)
{
	return index >= 0 && index < channels.size();
}

