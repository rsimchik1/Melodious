#pragma once


/**
 * Interface for a Channel, which is a node in a tree structure for processing
 * and combining audio tracks.
 *
 * TODO allow channel to have additional outputs ("sends")
 * TODO add modifiers for gain, pan, mute, and solo
 * TODO support toggleable mono and stereo channels
 * TODO add effects processing chain ("inserts")
 */
class Channel
{
public:
	/**
	 * Get the output of this channel combined with any children or inputs.
	 * Children are processed depth-first.
	 *
	 * @param numFrames The number of frames to process.
	 * @return The number of frames that were processed (should match input).
	 */
	virtual int processFrames(int numFrames) = 0;

	/**
	 * Set this node's parent to the given node. If this node already has a
	 * parent, it will be replaced. If input is null, this node will be detached
	 * from the tree. Parent nodes will have their children updated here.
	 *
	 * @throw InvalidChannelTreeException If the output channel is a leaf node,
	 * or if null is passed while this node is already detached.
	 * @param newParent The new parent node of this Channel.
	 */
	void setParent(Channel *newParent);
protected:
	/**
	 * Add the given node to this node's children.
	 *
	 * @throw InvalidChannelTreeException If this is a leaf node, or if the node
	 * already exists in the tree.
	 * @param newChild The node to be added.
	 */
	virtual void addChild(const Channel *newChild) = 0;

	/**
	 * Search children for the given node, and remove it if found.
	 *
	 * @throw InvalidChannelTreeException If this is a leaf node, or if the
	 * input node cannot be found.
	 * @throw InvalidArgumentException If the input is null.
	 * @param childToRemove The node to remove.
	 */
	virtual void removeChild(const Channel *childToRemove) = 0;
private:
	Channel* parent;
};