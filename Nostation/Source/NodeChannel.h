#pragma once
#include "Channel.h"

/**
 * Interior or root node in a Channel tree.
 */
class NodeChannel : Channel
{
public:
	int processFrames(int numFrames) override;
protected:
	void addChild(const Channel* newChild) override;
	void removeChild(const Channel* childToRemove) override;
};