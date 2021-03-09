#pragma once
#include "AudioBuffer.h"


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
	 * @return The processed frames.
	 */
	virtual AudioBuffer processFrames(int numFrames) = 0;
	
	/**
	 * Set this node's parent to the given node. If this node already has a
	 * parent, it will be replaced. If input is null, this node will be detached
	 * from the parent. Parent node will have its children updated.
	 *
	 * @throw InvalidChannelTreeException If the parent channel is a leaf node.
	 * @param newParent The new parent node of this Channel.
	 */
	void setParent(Channel *newParent);

	/**
	 * Detach this node from parent. Same as calling setParent(nullptr). If
	 * node is already detached, nothing will happen.
	 */
	void removeParent();

	/**
	 * Get the pointer to this Channel's parent.
	 *
	 * @return Parent Channel's pointer, or null if there is none.
	 */
	Channel* getParent();

	/**
	 * Determine whether this Channel has a parent.
	 *
	 * @return True if node has a parent, false otherwise.
	 */
	bool hasParent();

	/**
	 * Search this Channel's children for the given Channel.
	 *
	 * @param childToFind Pointer to the Channel to be found.
	 * @return True if childToFind is a child of this Channel, false otherwise.
	 */
	virtual bool hasChild(Channel* childToFind) = 0;
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