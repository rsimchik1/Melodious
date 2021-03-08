#pragma once
#include "Channel.h"

/**
 * Leaf node in a Channel tree, which takes input from a single Track instead of
 * multiple Channels. Attempts to modify this node's children will raise an
 * exception.
 */
class LeafChannel : Channel
{
public:
	int processFrames(int numFrames) override;
protected:
	void addChild(const Channel* newChild) override;
	void removeChild(const Channel* childToRemove) override;
};