#pragma once
#include "Track.h"

class OscTrack : public Track
{
public:
	OscTrack(float frequency, float amplitude);
	AudioBuffer processFrames(int numFrames, const Timeline& relativeTime) override;
private:
	float phase;
	float amplitude;
	float frequency;
};
