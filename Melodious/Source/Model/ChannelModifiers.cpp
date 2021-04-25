#include "ChannelModifiers.h"

ChannelModifiers::ChannelModifiers() : ChannelModifiers("", 1, 0)
{}

ChannelModifiers::ChannelModifiers(const std::string& name, float volume, float pan)
	: name(name),
	volume(volume),
	pan(pan)
{}

ChannelModifiers::ChannelModifiers(const ChannelModifiers& toCopy)
	: name(toCopy.name),
	volume(toCopy.volume.load()),
	pan(toCopy.pan.load())
{}

void ChannelModifiers::setName(const std::string& name)
{
	this->name = name;
}

std::string ChannelModifiers::getName()
{
	return name;
}

void ChannelModifiers::setVolume(float volume)
{
	this->volume = volume;
}

void ChannelModifiers::setPan(float pan)
{
	this->pan = pan;
}

AudioBuffer ChannelModifiers::getModifiedBuffer(
	const AudioBuffer& originalBuffer)
{
	auto modifiedBuffer = AudioBuffer(originalBuffer.getNumFrames(), 2);

	// Constant power pan law
	const double piOver2 = 4.0 * atan(1.0) * 0.5;
	const double root2Over2 = sqrt(2.0) * 0.5;
	double scaledPosition = pan * piOver2;
	double angle = scaledPosition * 0.5;
	double lGain = root2Over2 * (cos(angle) - sin(angle));
	double rGain = root2Over2 * (cos(angle) + sin(angle));

	int rChannelIndex = originalBuffer.getNumChannels() > 1;
	for (auto frame = 0; frame < originalBuffer.getNumFrames(); frame++)
	{
		auto lSample = originalBuffer.readSampleAt(frame, 0);
		auto rSample = originalBuffer.readSampleAt(frame, rChannelIndex);
		modifiedBuffer.writeSampleAt(frame, 0, lSample * lGain * volume);
		modifiedBuffer.writeSampleAt(frame, 1, rSample * rGain * volume);
	}

	return modifiedBuffer;
}
