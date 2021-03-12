#include "ChannelMixer.h"

ChannelMixer::ChannelMixer()
{
}

ChannelMixer::~ChannelMixer()
{
}

AudioBuffer ChannelMixer::processFrames(int numFrames, const Timeline& referenceTimeline)
{
	return AudioBuffer(numFrames, 2);
}

int ChannelMixer::getNumChannels()
{
	return -1;
}

void ChannelMixer::createAudioChannel(int index)
{
}

void ChannelMixer::createBusChannel(int index)
{
}

void ChannelMixer::deleteChannel(int index)
{
}

void ChannelMixer::moveChannelToIndex(int fromIndex, int toIndex)
{
}

void ChannelMixer::connectChannels(int sourceIndex, int destinationIndex)
{
}

void ChannelMixer::connectToMasterOutput(int sourceIndex)
{
}
