#pragma once

#include "JuceHeader.h"

class ClipView : public juce::Component
{
public:
	ClipView(uint32_t start = 0, uint32_t end = 0);
	void paint(juce::Graphics& g) override;
	uint32_t getStartSample();
	uint32_t getEndSample();
	void setStartEndSample(uint32_t start, uint32_t end);
	void setColor(juce::Colour fillColor);
private:
	const float borderRadius = 3;
	const float borderThickness = 2;
	uint32_t start;
	uint32_t end;
	juce::Colour fillColor;
	juce::Colour borderColor;
};
