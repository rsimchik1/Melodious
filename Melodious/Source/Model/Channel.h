#pragma once
#include "AudioBuffer.h"
#include "AudioNode.h"
#include "ChannelModifiers.h"

class Timeline;
/**
 * Interface for a Channel, which is a node in a tree structure for processing
 * and combining audio tracks.
 *
 * TODO allow channel to have additional outputs ("sends")
 * TODO add modifiers for gain, pan, mute, and solo - encapsulate?
 * TODO support toggleable mono and stereo channels
 * TODO add effects processing chain ("inserts")
 * 
 * @authors Richard Simchik
 */
class Channel : public AudioNode
{
public:
	Channel();
	~Channel();

	/**
	 * Get the output of this channel combined with any children or inputs.
	 * Children are processed depth-first.
	 *
	 * @param numFrames The number of frames to process.
	 * @param relativeTime The timeline to reference when reading frames.
	 * @return The processed frames.
	 */
	AudioBuffer processFrames(int numFrames, const Timeline &relativeTime) override = 0;

	/**
	 * Search this Channel's children for the given Channel.
	 *
	 * @param childToFind Pointer to the Channel to be found.
	 * @return True if childToFind is a child of this Channel, false otherwise.
	 */
	virtual bool hasChild(const Channel* childToFind) = 0;
	
	/**
	 * Set this node's parent to the given node. If this node already has a
	 * parent, it will be replaced. If input is null, this node will be detached
	 * from the parent. Parent node will have its children updated.
	 *
	 * @throw InvalidChannelTreeException If the parent channel is a leaf node,
	 * if the parent channel is this channel, or if the parent channel is a
	 * child of this channel.
	 * @param newParent The new parent node of this Channel.
	 */
	void setParent(Channel *newParent);

	/**
	 * Get the pointer to this Channel's parent.
	 *
	 * @return Parent Channel's pointer, or null if there is none.
	 */
	Channel* getParent();

	/**
	 * Detach this node from parent. Same as calling setParent(nullptr). If
	 * node is already detached, nothing will happen.
	 *
	 * @throw InvalidChannelTreeException If this Channel's parent is a
	 * LeafChannel (this should never happen).
	 */
	void removeParent();

	/**
	 * Determine whether this Channel has a parent.
	 *
	 * @return True if node has a parent, false otherwise.
	 */
	bool hasParent();

	ChannelModifiers *getModifiers();
protected:
	ChannelModifiers *modifiers;

	/**
	 * Add the given node to this node's children.
	 *
	 * @throw InvalidChannelTreeException If this is a leaf node.
	 * @throw InvalidArgumentException If the child already exists.
	 * @param newChild The node to be added.
	 */
	virtual void addChild(Channel *newChild) = 0;

	/**
	 * Search children for the given node, and remove it if found.
	 *
	 * @throw InvalidChannelTreeException If this is a leaf node.
	 * @throw InvalidArgumentException If the input is null or cannot be found.
	 * @param childToRemove The node to remove.
	 */
	virtual void removeChild(Channel *childToRemove) = 0;
private:
	Channel* parent = nullptr;
};