#pragma once

#include "JuceHeader.h"

class PlayheadView : public juce::Component
{
public:
	enum ColourIds
	{
		markerColourId = 0xff0000081,
		lineColourId = 0xfffff082
	};

	enum DefaultColours
	{
		defaultMarkerColour = 0xffffffff,
		defaultLineColour = 0xffffffff
	};

	PlayheadView();
	~PlayheadView();

	void paint(juce::Graphics& g) override;

	void setPlayheadPos(int xPos);
	void setPlayheadMarkerHeight(int height);
private:
	int playheadX;
	int markerHeight;

	int lineThickness = 1;
};
