#pragma once

#include "JuceHeader.h"
class ArrangeView : public juce::AnimatedAppComponent
{
public:
	ArrangeView();
	void update() override;
	void paint(juce::Graphics& g) override;
	void setTime(int32_t sample);
	void setSampleRate(int sampleRate);
	float starts[4];
	float ends[4];
private:
	float beatSpacing;
	float trackSpacing;
	float trackPadding;
	int32_t sample;
	int sampleRate;
};
