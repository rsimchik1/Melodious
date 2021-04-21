#pragma once

#include "JuceHeader.h"
#include "ScrollableContent.h"

class TimelineView : public juce::Component,
                     public ScrollableContent
{
public:
	enum ColourIds
	{
		backgroundColourId = 0x20000041,
		textColourId = 0x20000042,
		majorLineColourId = 0x20000043,
		minorLineColourId = 0x20000044,
		borderColourId = 0x20000045,
		spacerBorderColourId = 0x20000046
	};

	enum DefaultColours
	{
		defaultBackgroundColour = 0xff19247c,
		defaultTextColour = 0xffffffff,
		defaultMajorLineColour = 0xffc5c8de,
		defaultMinorLineColour = 0xff747896,
		defaultBorderColour = 0xffb2b5cb,
		defaultSpacerBorderColour = 0xffffffff
	};

	TimelineView();
	~TimelineView() override;

	void paint(juce::Graphics& g) override;
	void resized() override;

	void scrollX(float deltaX) override;
	void scrollY(float deltaY) override;
	void setScrollX(float x) override;
	void setScrollY(float y) override;
	float getContentWidth() override;
	float getContentHeight() override;

	void setSpacerWidth(float newWidth);
private:
	float measureSizePixels;
	int beatsPerMeasure;
	int subdivideBy;
	int numSubdivisions;
	int minSpacingPixels;

	float paddingPixels;
	int borderThickness;
	int spacerWidth;
	int spacerBorderThickness;

	float scrollXAmount;
	int minScrollX;
};
