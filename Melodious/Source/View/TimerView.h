#pragma once

#include "JuceHeader.h"
#include "../Controller/Observer.h"
#include "../Model/Timeline.h"

class TimerView : public juce::Component,
                  public juce::Label::Listener,
                  public Observer<Timeline>,
				  public juce::Timer
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

	void labelTextChanged(juce::Label* labelThatHasChanged) override;
	void notify(Timeline* caller) override;
	void timerCallback() override;
private:
	unsigned int tempo;
	std::pair<unsigned int, unsigned int> meter;
	std::pair<unsigned int, unsigned int> barAndBeat;

	int borderRadius = 5;
	int borderThickness = 3;

	bool update = true;

	float barAndBeatPercentWidth = 0.5f;
	float meterPercentWidth = 0.25f;
	float tempoPercentWidth = 0.25f;
	float labelPercentHeight = 0.3f;

	int numBarDigits = 3;
	juce::Font mainFont;
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
	std::vector<juce::Label*> allLabels;

	void setBeat(uint64_t beat);
};
