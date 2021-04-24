#pragma once
#include <atomic>
#include <string>

#include "AudioBuffer.h"

/**
 * Class that modifies the data that flows through a channel.
 */
class ChannelModifiers
{
public:
	ChannelModifiers();
	ChannelModifiers(const std::string& name, float volume, float pan);
	ChannelModifiers(const ChannelModifiers& toCopy);
	void setName(const std::string& name);
	std::string getName();
	void setVolume(float volume);
	void setPan(float pan);

	AudioBuffer getModifiedBuffer(const AudioBuffer& originalBuffer);
private:
	std::string name;
	std::atomic<float> volume;
	std::atomic<float> pan;
};
