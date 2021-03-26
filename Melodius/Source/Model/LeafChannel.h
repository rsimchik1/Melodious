#pragma once
#include "Channel.h"
#include "Track.h"

/**
 * Leaf node in a Channel tree, which takes input from a single Track instead of
 * multiple Channels. Attempts to modify this node's children will raise an
 * exception.
 * 
 * @authors Richard Simchik
 */
class LeafChannel : public Channel
{
public:
	/**
	 * Create a new LeafChannel.
	 * 
	 * @throw InvalidChannelTreeException If the passed parent is a LeafChannel.
	 * @param parent Initial parent for this channel (optional).
	 */
	LeafChannel(Channel* parent = nullptr);
	~LeafChannel();
	bool hasChild(const Channel* childToFind) override;
	AudioBuffer processFrames(int numFrames, const Timeline& relativeTime) override;
	void setAudioSource(AudioNode* audioSource);
protected:
	void addChild(Channel* newChild) override;
	void removeChild(Channel* childToRemove) override;
private:
	AudioNode* audioSource;
};