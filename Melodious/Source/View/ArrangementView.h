#pragma once

#include "JuceHeader.h"
#include "PlayheadView.h"
#include "TimelineView.h"

#include "TrackControlsListView.h"
#include "TrackLaneListView.h"
#include "../Controller/TrackListController.h"

class ArrangementView : public juce::AnimatedAppComponent,
                        public juce::ScrollBar::Listener
{
public:
	ArrangementView();
	~ArrangementView() override;

	void resized() override;

    void createAndAppendTrack();
    void createClipOnTrack(int trackIndex, float startPixel, float length);
    int getNumTracks();
	void scrollBarMoved(juce::ScrollBar* scrollBarThatHasMoved, double newRangeStart) override;
	void update() override;
	void paint(juce::Graphics& g) override;
private:
    class ScrollBarLookAndFeel;
	
    const int scrollBarSize = 20;
    const int timelineHeight = 35;
    double scrollX = 0, scrollY = 0;

    int numTracks = 0;
    TrackControlsListView trackControlsList;
    TrackLaneListView trackLaneList;
    std::shared_ptr<TrackListController> trackListController;
    TimelineView timelineView;
    PlayheadView playheadView;
    
    juce::ScrollBar *verticalScroll;
    juce::ScrollBar *horizontalScroll;
    ScrollBarLookAndFeel* scrollBarLookAndFeel;
	juce::ResizableBorderComponent* resizable;
};

class ArrangementView::ScrollBarLookAndFeel : public juce::LookAndFeel_V4
{
public:
    enum ColourIds
    {
	    borderColourId = 0x20000061
    };

    enum DefaultColours
    {
	    defaultTrackColour = 0xff304097,
    	defaultThumbColour = 0xff0271ff,
        defaultBorderColour = 0xff737795
    };

    ScrollBarLookAndFeel();
    void drawScrollbar(juce::Graphics&, juce::ScrollBar&, int x, int y, int width, int height, bool isScrollbarVertical,
	    int thumbStartPosition, int thumbSize, bool isMouseOver, bool isMouseDown) override;
private:
    int padding = 2;
};
