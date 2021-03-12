#pragma once
#include "AudioBuffer.h"
#include "Channel.h"
#include "AudioNode.h"

class NodeChannel;
/**
 * Class that allows client code to sort and access channels by index and
 * modify a channel tree via an abstract interface.
 *
 * TODO find a replacement for the "create...Channel()" methods
 * 
 * @authors Richard Simchik
 */
class ChannelMixer : AudioNode
{
public:
	/**
	 * Create a new ChannelMixer. Automatically creates a master output channel.
	 */
	ChannelMixer();

	/**
	 * Delete this ChannelMixer. DELETES ALL ASSOCIATED CHANNELS.
	 */
	~ChannelMixer();

	/**
	 * Read the given number of frames from the master output channel (and all
	 * connected channels by extension).
	 *
	 * @param numFrames Number of frames to be read.
	 * @param relativeTime Timeline to be referenced when reading frames.
	 * @return AudioBuffer containing the samples that were read.
	 */
	AudioBuffer processFrames(int numFrames, const Timeline& relativeTime) override;

	/**
	 * Get the number of channels that are currently stored in this mixer.
	 *
	 * @return The number of channels.
	 */
	int getNumChannels();

	/**
	 * Create a new audio source channel at the specified index, shifting
	 * existing channels to accomodate it.
	 *
	 * Channel output will automatically be set to master output.
	 *
	 * @throw IndexOutOfBoundsException If the index is greater than the total
	 * number of channels.
	 * @param index The index at which the channel will be inserted. If no index
	 * is specified or index < 0, the channel will be appended to the list.
	 */
	void createAudioChannel(int index = -1);

	/**
	 * Create a new bus channel at the specified index, shifting existing
	 * channels to accomodate it. Bus channels are used to combine the outputs
	 * of other audio and/or bus channels in parallel.
	 *
	 * Channel output will automatically be set to master output.
	 *
	 * @throw IndexOutOfBoundsException If the index is greater than the total
	 * number of channels.
	 * @param index The index at which the channel will be inserted. If no index
	 * is specified or index < 0, the channel will be appended to the list.
	 */
	void createBusChannel(int index = -1);

	/**
	 * Delete the channel at the specified index.
	 *
	 * @throw IndexOutOfBoundsException If the index is negative or greater than
	 * the total number of channels - 1.
	 * @param index The index of the channel to be deleted.
	 */
	void deleteChannel(int index);

	/**
	 * Move a channel from index to another, shifting existing channels to
	 * accomodate the change.
	 *
	 * @throw IndexOutOfBoundsException If either index is negative or greater
	 * than the total number of channels.
	 * @param fromIndex The index of the channel to be moved.
	 * @param toIndex The index to which the channel will be moved.
	 */
	void moveChannelToIndex(int fromIndex, int toIndex);

	/**
	 * Connect a source channel's output to a destination channel's input. The
	 * source channel may be any channel. The destination channel may only be
	 * a bus channel. The two channels may not be the same. If the channels are
	 * already connected, nothing will be changed.
	 *
	 * @throw InvalidChannelTreeException If the destination channel is not a
	 * bus channel, or if the source and destination are the same channel.
	 * @param sourceIndex The index of the source channel.
	 * @param destinationIndex The index of the destination channel.
	 */
	void connectChannels(int sourceIndex, int destinationIndex);

	/**
	 * Connect a source channel's output to the master output channel. The
	 * source channel may be any channel. If the channel is already connected to
	 * master output, nothing will be changed.
	 *
	 * @throw IndexOutOfBoundsException If the index is negative or greater than
	 * the total number of channels - 1.
	 * @param sourceIndex The index of the source channel.
	 */
	void connectToMasterOutput(int sourceIndex);
private:
	std::vector<Channel*> channels;
	NodeChannel* rootChannel;
};