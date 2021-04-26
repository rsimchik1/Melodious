#pragma once

#include "JuceHeader.h"

class AddTrackView : public juce::Component
{
public:
	AddTrackView();
	~AddTrackView();
	void paint(juce::Graphics& g) override;
	void resized() override;

	void addListener(juce::Button::Listener *listener);
private:
	class AddButtonLookAndFeel;
	juce::TextButton addButton;
	AddButtonLookAndFeel* addButtonLookAndFeel;
	int borderSize = 1;
};

class AddTrackView::AddButtonLookAndFeel : public juce::LookAndFeel_V4
{
public:
	enum DefaultColours
	{
		defaultTextColour = 0xff4443eb
	};

	AddButtonLookAndFeel();
	juce::Font getTextButtonFont(juce::TextButton&, int buttonHeight) override;
private:
	int fontSize = 35;
};
