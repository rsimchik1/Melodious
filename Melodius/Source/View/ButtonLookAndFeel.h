#pragma once

#include "JuceHeader.h"

class ButtonLookAndFeel : public juce::LookAndFeel_V4
{
public:
	ButtonLookAndFeel();
	~ButtonLookAndFeel() override;
	void drawButtonBackground(juce::Graphics&, juce::Button&, const juce::Colour& backgroundColour,
		bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override;

	void setBorderThickness(int thickness);
private:
	int borderThickness;
};
