#pragma once
#include "Channel.h"

#include <vector>

/**
 * Interior or root node in a Channel tree.
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
	AudioBuffer processFrames(int numFrames) override;
	bool hasChild(Channel* childToFind) override;
protected:
	void addChild(const Channel* newChild) override;
	void removeChild(const Channel* childToRemove) override;
private:
	std::vector<Channel*> children;
};