#pragma once
#include "Channel.h"

#include <vector>

/**
 * Interior or root node in a Channel tree.
 * 
 * @authors Richard Simchik
 */
class NodeChannel : public Channel
{
public:
	/**
	 * Create a new NodeChannel. Automatically create a new track for this
	 * channel (will likely change in the future).
	 *
	 * @throw InvalidChannelTreeException If the passed parent is a LeafChannel.
	 * @param parent Initial parent for this channel (optional).
	 */
	NodeChannel(Channel* parent = nullptr);
	~NodeChannel();
	bool hasChild(const Channel* childToFind) override;
	AudioBuffer processFrames(int numFrames, const Timeline& relativeTime) override;
protected:
	void addChild(Channel* newChild) override;
	void removeChild(Channel* childToRemove) override;
private:
	std::vector<Channel*> children;
};