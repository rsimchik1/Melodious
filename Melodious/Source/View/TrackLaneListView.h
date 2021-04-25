#pragma once

#include "JuceHeader.h"
#include "ScrollableContent.h"
#include "TrackLaneView.h"

class TrackLaneListView : public juce::Component,
						  public ScrollableContent
{
public:
	enum ColourId
	{
		backgroundColourId = 0x20000021,
		majorLineColourId = 0x20000022,
		minorLineColourId = 0x20000023
	};

	enum DefaultColours
	{
		defaultBackgroundColour = 0xff030b47,
		defaultMajorLineColour = 0xffc5c8de,
		defaultMinorLineColour = 0xff747896
	};

	TrackLaneListView();
	~TrackLaneListView() override;

	void paint(juce::Graphics& g) override;
	void resized() override;

	TrackLaneView* appendNewTrackLane();
	TrackLaneView* getTrackLaneAt(int index);

	void scrollX(float deltaX) override;
	void scrollY(float deltaY) override;
	void setScrollX(float x) override;
	void setScrollY(float y) override;
	float getContentHeight() override;
	float getContentWidth() override;
	void setSubdivisionWidth(float widthPixels);
	void setNumSubdivisions(int subdivisions);
private:
	std::vector<TrackLaneView*> children;

	float lineSpacing;

	float scrollXAmount;
	float scrollYAmount;
	std::pair<float, float> scrollXBounds;
	std::pair<float, float> scrollYBounds;
	int numSubdivisions;

	void calculateScrollXBounds();
	void calculateScrollYBounds();
};
