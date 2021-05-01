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
	void drawImageButton(juce::Graphics& g, juce::Image* image, int imageX, int imageY,
		int imageW, int imageH, const juce::Colour& overlayColour,
		float imageOpacity, juce::ImageButton& button) override;
	void setButtonFont(juce::Font font);
	juce::Font getTextButtonFont(juce::TextButton&, int buttonHeight) override;
private:
	int borderThickness;
	juce::Font buttonFont;
};
