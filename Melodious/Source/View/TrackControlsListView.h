#pragma once

#include "AddTrackView.h"
#include "JuceHeader.h"
#include "ScrollableContent.h"
#include "TrackControlsView.h"

class TrackControlsListView : public juce::Component,
							  public ScrollableContent
{
public:
	enum ColourIds
	{
		backgroundColourId = 0x20000001,
		borderColourId = 0x20000002
	};

	enum DefaultColours
	{
		defaultBackgroundColour = 0xff030b47,
		defaultBorderColour = 0xffffffff
	};

	static const int DEFAULT_WIDTH = 350;

	TrackControlsListView();
	~TrackControlsListView() override;

	void paint(juce::Graphics& g) override;
	void resized() override;

	void appendNewTrackControls();
	TrackControlsView* getTrackAt(int index);

	void scrollX(float deltaX) override;
	void scrollY(float deltaY) override;
	void setScrollX(float x) override;
	void setScrollY(float y) override;
	float getContentWidth() override;
	float getContentHeight() override;
private:
    std::vector<TrackControlsView *> children;
	AddTrackView addTrackView;

	int borderThickness = 2;

	float scrollYAmount;
	float scrollYMin;
	float scrollYMax;

	void calculateScrollYMax();
};

