#include "OscClip.h"

#include "juce_core/juce_core.h"

OscClip::OscClip(float frequency, float amplitude)
{
	this->frequency = frequency;
	this->amplitude = amplitude;
	this->phase = 0;
}

float OscClip::getFrequency()
{
	return frequency;
}

float OscClip::getAmplitude()
{
	return amplitude;
}

float OscClip::getPhase()
{
	return phase;
}

void OscClip::incrementPhase(float sampleRate)
{
	phase += juce::MathConstants<float>::twoPi * 
			(frequency / sampleRate);
	if (phase >= juce::MathConstants<float>::twoPi) phase -= juce::MathConstants<float>::twoPi;
}
