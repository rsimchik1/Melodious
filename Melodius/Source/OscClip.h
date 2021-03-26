#pragma once
#include "Clip.h"

class OscClip : public Clip
{
public:
	OscClip(float frequency, float amplitude);
	float getFrequency();
	float getAmplitude();
	float getPhase();
	void incrementPhase(float sampleRate);
private:
	float frequency;
	float phase;
	float amplitude;
};
