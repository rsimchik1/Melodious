#pragma once

#include "JuceHeader.h"
#include "PlayheadView.h"
#include "TimelineView.h"

#include "TrackControlsListView.h"
#include "TrackLaneListView.h"
#include "../Controller/TrackListController.h"

class TrackListController;

class ArrangementView : public juce::AnimatedAppComponent,
                        public juce::ScrollBar::Listener
{
public:
    struct TrackView;

	ArrangementView(std::shared_ptr<TrackListController> trackListController);
	~ArrangementView() override;

	void resized() override;

    TrackView createAndAppendTrack();
    ClipView* createClipOnTrack(int trackIndex, uint64_t startSample, uint64_t lengthInSamples);
    int getNumTracks();
	void scrollBarMoved(juce::ScrollBar* scrollBarThatHasMoved, double newRangeStart) override;
	void update() override;
	void paint(juce::Graphics& g) override;

    void setSampleRate(int sampleRate);
    void setPlayheadSample(uint64_t sample);
    void setMeter(int numerator, int denominator);
    void setTempo(double beatsPerMinute);
private:
    class ScrollBarLookAndFeel;
	
    const int scrollBarSize = 20;
    const int timelineHeight = 35;
    double scrollX = 0, scrollY = 0;

    double samplesPerPixel = 1000;
    double samplesPerSecond = 44100;
    double beatsPerMinute = 120;

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

    void resizeTimeline(double sampleRate, double beatsPerMinute);
    void resizeClipView(ClipView* clipView);
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

struct ArrangementView::TrackView
{
	TrackControlsView* controls;
	TrackLaneView* lane;
};
