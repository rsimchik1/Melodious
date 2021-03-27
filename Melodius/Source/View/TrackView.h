#pragma once

#include "ClipView.h"
#include "JuceHeader.h"
#include "TrackControlsView.h"

class TrackView : public juce::Component
{
public:
	static const int BORDER_COLOR = 1;
	
	TrackView(std::string name, int sampleRate);
	~TrackView();
	void paint(juce::Graphics& g) override;
	void resized() override;
	void setPadding(int padding);
	void setPixelsPerSecond(float pixelsPerSecond);
	void setScrollX(float scrollX);
	void addClip(ClipView *toAdd);
	void setSampleRate(int sampleRate);
	void setControlsWidth(float width);
	void setControlsColours(juce::Colour background, juce::Colour text);
	TrackControlsView* getControls();
private:
	float pixelsPerSecond;
	int padding;
	std::vector<ClipView *> clipViews;
	int sampleRate;
	TrackControlsView *controls;
	float scrollX;

	float sampleToPixel(uint32_t sample);
	void setClipBounds(ClipView* clip);
};
