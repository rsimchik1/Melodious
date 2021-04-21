#pragma once

#include "ButtonLookAndFeel.h"
#include "JuceHeader.h"
#include "TimerView.h"

class MixHeaderView : public juce::Component
{
public:
	enum ColourIds
	{
		backgroundColourId = 0x20000051,
		borderColourId = 0x20000052
	};

	enum DefaultColours
	{
		defaultBackgroundColour = 0xff131b5d,
		defaultBorderColour = 0xffffffff
	};

	MixHeaderView();
	~MixHeaderView();
	void paint(juce::Graphics& g) override;
	void resized() override;
private:
	int borderThickness = 4;
	int padding = 20;

	juce::TextButton* backButton;
	juce::TextButton* rewindButton;
	juce::TextButton* playPauseButton;
	juce::TextButton* fastForwardButton;
	juce::TextButton* nextButton;
	juce::TextButton* stopButton;
	juce::TextButton* recordButton;
	std::vector<juce::Button*> buttons;
	juce::DrawableRectangle buttonsBackground;

	TimerView timerView;
	ButtonLookAndFeel *buttonLookAndFeel;
};
