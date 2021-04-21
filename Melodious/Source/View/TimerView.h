#pragma once

#include "JuceHeader.h"

class TimerView : public juce::Component
{
public:
	enum ColourIds
	{
		backgroundColourId = 0x20000071,
		borderColourId = 0x20000072,
		textColourId = 0x20000073
	};

	enum DefaultColours
	{
		defaultBackgroundColour = 0xff030b47,
		defaultBorderColour = 0xff19247c,
		defaultTextColour = 0xffffffff
	};
	TimerView();
	~TimerView() override;
	void paint(juce::Graphics& g) override;
	void resized() override;

	void setTempo(unsigned int tempo);
	void setMeter(unsigned int numerator, unsigned int denominator);
	void setBarAndBeat(unsigned int bar, unsigned int beat);
private:
	unsigned int tempo;
	std::pair<unsigned int, unsigned int> meter;
	std::pair<unsigned int, unsigned int> barAndBeat;

	int borderRadius = 5;
	int borderThickness = 3;

	float barAndBeatPercentWidth = 0.5;
	float meterPercentWidth = 0.25;
	float tempoPercentWidth = 0.25;

	int numBarDigits = 3;
	juce::Label barLabel;
	std::vector<juce::Label *> barText;
	juce::Label beatLabel;
	juce::Label beatText;
	juce::Label barBeatDot;

	juce::Label meterLabel;
	juce::Label meterTopText;
	juce::Label meterBottomText;
	juce::Label meterSlashText;

	juce::Label tempoLabel;
	juce::Label tempoText;
};
