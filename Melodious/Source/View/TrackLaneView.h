#pragma once

#include "ClipView.h"
#include "JuceHeader.h"

class TrackLaneView : public juce::Component
{
public:
	enum ColourIds
	{
		backgroundColourId = 0x2000031,
		borderColourId = 0x2000032
	};

	static const int paddingPixels = 10;

	TrackLaneView();
	~TrackLaneView() override;

	void paint(juce::Graphics& g) override;
	void resized() override;

	// Caller is responsible for setting clip's parent
	ClipView *createClip(float startPixel, float length = 0.0f);
	float getContentWidth();
	std::vector<ClipView *>& getClipViews();
private:
	std::vector<ClipView*> clipViews;
};
