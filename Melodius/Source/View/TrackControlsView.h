#pragma once

#include "JuceHeader.h"

class TrackControlsView : public juce::Component
{
public:
	static const int BACKGROUND_COLOR = 1;
	static const int TEXT_COLOR = 2;
	static const int BORDER_COLOR = 3;

	TrackControlsView();
	void paint(juce::Graphics& g) override;
	void resized() override;
private:
	const float fontSize = 25.0f;
	const float padding = 10.0f;
	const float leftMargin = 10.0f;
};
