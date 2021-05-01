#include "ArrangementView.h"

ArrangementView::ArrangementView(std::shared_ptr<TrackListController> trackListController)
{
    setFramesPerSecond(60);
    trackControlsList.setSize(TrackControlsListView::DEFAULT_WIDTH, getHeight() - scrollBarSize);
    trackControlsList.addObserver(trackListController);

    this->resizable = new juce::ResizableBorderComponent(&trackControlsList, nullptr);
    resizable->setBorderThickness(juce::BorderSize<int>(0, 5, 0, 0));
    
    verticalScroll = new juce::ScrollBar(true);
    horizontalScroll = new juce::ScrollBar(false);
    scrollBarLookAndFeel = new ScrollBarLookAndFeel();

    verticalScroll->setLookAndFeel(scrollBarLookAndFeel);
    verticalScroll->addListener(this);
    verticalScroll->setAutoHide(true);
    verticalScroll->setCurrentRangeStart(0, juce::NotificationType::dontSendNotification);

    horizontalScroll->setLookAndFeel(scrollBarLookAndFeel);
    horizontalScroll->addListener(this);
    horizontalScroll->setAutoHide(true);
    horizontalScroll->setCurrentRangeStart(0, juce::NotificationType::dontSendNotification);

    playheadView.setPlayheadPos(0);

    setMeter(4, 4);
    setTempo(beatsPerMinute);
    setSampleRate(samplesPerSecond);

    addAndMakeVisible(verticalScroll);
    addAndMakeVisible(horizontalScroll);
    addAndMakeVisible(trackControlsList);
    addAndMakeVisible(resizable);
    addAndMakeVisible(trackLaneList);
    addAndMakeVisible(timelineView);
    addAndMakeVisible(playheadView);
}

ArrangementView::~ArrangementView()
{
    verticalScroll->setLookAndFeel(nullptr);
    horizontalScroll->setLookAndFeel(nullptr);

    delete scrollBarLookAndFeel;
    scrollBarLookAndFeel = nullptr;
	
    delete verticalScroll;
    verticalScroll = nullptr;
	
    delete horizontalScroll;
    horizontalScroll = nullptr;

    delete resizable;
    resizable = nullptr;
}

void ArrangementView::resized()
{
    auto timelineStripBounds = getLocalBounds();
    timelineStripBounds.setHeight(timelineHeight);
    timelineStripBounds.setY(0);


	// TODO find a better way to update scrollbar sizes based on visibility
    auto verticalScrollbarBounds = getLocalBounds();
    verticalScrollbarBounds.removeFromLeft(getWidth() - scrollBarSize);
    verticalScrollbarBounds.removeFromTop(timelineStripBounds.getHeight());
    verticalScroll->setBounds(verticalScrollbarBounds);
    
    auto horizontalScrollbarBounds = getLocalBounds();
    horizontalScrollbarBounds.removeFromTop(getHeight() - scrollBarSize);
    horizontalScrollbarBounds.removeFromRight(trackControlsList.getWidth() +
        scrollBarSize);
    horizontalScroll->setBounds(horizontalScrollbarBounds);

    verticalScroll->setRangeLimits(0,trackControlsList.getContentHeight());
    verticalScroll->setCurrentRange(verticalScroll->getCurrentRangeStart(),
        verticalScroll->getHeight(), juce::dontSendNotification);

    horizontalScroll->setRangeLimits(0,trackLaneList.getContentWidth());
    horizontalScroll->setCurrentRange(horizontalScroll->getCurrentRangeStart(),
        horizontalScroll->getWidth(), juce::dontSendNotification);

    auto vScrollbarSize = verticalScroll->isVisible() ? scrollBarSize : 0;
    auto hScrollbarSize = horizontalScroll->isVisible() ? scrollBarSize : 0;

    verticalScrollbarBounds = getLocalBounds();
    verticalScrollbarBounds.removeFromLeft(getWidth() - scrollBarSize);
    verticalScrollbarBounds.removeFromTop(timelineStripBounds.getHeight());
    verticalScroll->setBounds(verticalScrollbarBounds);
    
    horizontalScrollbarBounds = getLocalBounds();
    horizontalScrollbarBounds.removeFromTop(getHeight() - scrollBarSize);
    horizontalScrollbarBounds.removeFromRight(trackControlsList.getWidth() +
        vScrollbarSize);
    horizontalScroll->setBounds(horizontalScrollbarBounds);

    verticalScroll->setRangeLimits(0,trackControlsList.getContentHeight());
    verticalScroll->setCurrentRange(verticalScroll->getCurrentRangeStart(),
        verticalScroll->getHeight(), juce::dontSendNotification);

    horizontalScroll->setRangeLimits(0,trackLaneList.getContentWidth());
    horizontalScroll->setCurrentRange(horizontalScroll->getCurrentRangeStart(),
        horizontalScroll->getWidth(), juce::dontSendNotification);


    auto trackControlsListBounds = getLocalBounds();
    trackControlsListBounds.removeFromTop(timelineStripBounds.getHeight());
    trackControlsListBounds.removeFromLeft(getWidth() - 
        trackControlsList.getWidth() - vScrollbarSize);
    trackControlsListBounds.removeFromRight(vScrollbarSize);
	trackControlsList.setBounds(trackControlsListBounds);
    resizable->setBounds(trackControlsListBounds);

	for (auto i = 0; i < numTracks; i++)
	{
        auto* trackLane = trackLaneList.getTrackLaneAt(i);
        auto* trackControls = trackControlsList.getTrackAt(i);
        // leave other positioning to TrackLaneListView, just link heights here
        trackLane->setSize(trackLane->getWidth(), trackControls->getHeight());
	}

    auto trackLaneListBounds = getLocalBounds();
    trackLaneListBounds.removeFromTop(trackControlsList.getY());
    trackLaneListBounds.removeFromRight(getWidth() - trackControlsList.getX());
    trackLaneListBounds.removeFromBottom(hScrollbarSize);
    trackLaneList.setBounds(trackLaneListBounds);

    timelineView.setBounds(timelineStripBounds);
    timelineView.setSpacerWidth(getWidth() - trackControlsList.getX());

    auto playheadViewBounds = trackLaneListBounds;
    auto playheadMarkerSize = timelineStripBounds.getHeight() / 3;
    playheadViewBounds.translate(0, -playheadMarkerSize);
    playheadViewBounds.setHeight(playheadViewBounds.getHeight() + playheadMarkerSize);
    playheadView.setBounds(playheadViewBounds);
    playheadView.setPlayheadMarkerHeight(playheadMarkerSize);
}

ArrangementView::TrackView ArrangementView::createAndAppendTrack()
{
    TrackView combined;
    combined.controls = trackControlsList.appendNewTrackControls();
    combined.controls->setName("Track " + std::to_string(numTracks + 1));
    combined.lane = trackLaneList.appendNewTrackLane();
    this->numTracks++;

    return combined;
}

ClipView* ArrangementView::createClipOnTrack(int trackIndex, uint64_t startSample, uint64_t lengthInSamples)
{
    auto trackAtIndex = trackLaneList.getTrackLaneAt(trackIndex);
    auto startPixel = startSample * samplesPerPixel;
    auto lengthPixels = lengthInSamples * samplesPerPixel;
    auto newClip = trackAtIndex->createClip(startPixel, lengthPixels);
    newClip->setSampleRate(samplesPerSecond);
    newClip->setStartEndSample(startSample, lengthInSamples);
    resizeClipView(newClip);
    trackLaneList.addAndMakeVisible(newClip);
    return newClip;
}

int ArrangementView::getNumTracks()
{
    return numTracks;
}

void ArrangementView::scrollBarMoved(juce::ScrollBar* scrollBarThatHasMoved, double newRangeStart)
{
    if (scrollBarThatHasMoved->isVertical())
    {
        scrollY = newRangeStart;
		trackControlsList.setScrollY(scrollY);
		trackLaneList.setScrollY(scrollY);
    }
    else
    {
        scrollX = newRangeStart;
		trackLaneList.setScrollX(scrollX);
		timelineView.setScrollX(scrollX);
    }
}

void ArrangementView::update()
{
}

void ArrangementView::paint(juce::Graphics& g)
{
}

void ArrangementView::setSampleRate(int sampleRate)
{
    this->samplesPerSecond = sampleRate;
    resizeTimeline(samplesPerSecond, beatsPerMinute);
    for (int i = 0; i < numTracks; i++)
    {
        auto track = trackLaneList.getTrackLaneAt(i);
        for (auto clipView : track->getClipViews())
            clipView->setSampleRate(sampleRate);
    }
}

void ArrangementView::setPlayheadSample(uint64_t sample)
{
    auto xPos = (sample / samplesPerPixel) - scrollX;
    playheadView.setPlayheadPos(xPos);
}

void ArrangementView::setMeter(int numerator, int denominator)
{
    timelineView.setMeter(numerator, denominator);
    trackLaneList.setNumSubdivisions(numerator);
}

void ArrangementView::setTempo(double beatsPerMinute)
{
    this->beatsPerMinute = beatsPerMinute;
    resizeTimeline(samplesPerSecond, beatsPerMinute);
}

void ArrangementView::resizeTimeline(double sampleRate, double beatsPerMinute)
{
	double oneBeatPerSecond = 60.0;
	auto samplesPerBeat = (sampleRate / beatsPerMinute) * oneBeatPerSecond;
    timelineView.setSubdivisionWidth(samplesPerBeat / samplesPerPixel);
    trackLaneList.setSubdivisionWidth(samplesPerBeat / samplesPerPixel);
    for (auto i = 0; i < numTracks; i++)
        for (auto* clipView : trackLaneList.getTrackLaneAt(i)->getClipViews())
            resizeClipView(clipView);
	
    resized();
}

void ArrangementView::resizeClipView(ClipView* clipView)
{
	auto clipBounds = clipView->getLocalBounds();
	clipBounds.setWidth(clipView->getLengthInSamples() / samplesPerPixel);
	clipView->setBounds(clipBounds);
}

ArrangementView::ScrollBarLookAndFeel::ScrollBarLookAndFeel()
{
    setColour(juce::ScrollBar::trackColourId, juce::Colour(defaultTrackColour));
    setColour(juce::ScrollBar::thumbColourId, juce::Colour(defaultThumbColour));
    setColour(borderColourId, juce::Colour(defaultBorderColour));
}

void ArrangementView::ScrollBarLookAndFeel::drawScrollbar(juce::Graphics& g, juce::ScrollBar& sb, int x, int y, int width,
	int height, bool isScrollbarVertical, int thumbStartPosition, int thumbSize, bool isMouseOver, bool isMouseDown)
{
    g.fillAll(findColour(juce::ScrollBar::trackColourId));

    auto thumbColour = findColour(juce::ScrollBar::thumbColourId);
    if (isMouseDown)
        thumbColour = thumbColour.darker(0.1);
    else if (isMouseOver)
        thumbColour = thumbColour.brighter(0.1);

    g.setColour(thumbColour);
    int rectX = x, rectY = y, rectW = width, rectH = height;
    int lineX1 = x, lineY1 = y, lineX2 = x + width, lineY2 = y + height;
    if (isScrollbarVertical)
    {
        rectY = thumbStartPosition;
        rectH = thumbSize;
        lineX2 = lineX1;
    }
    else
    {
        rectX = thumbStartPosition;
        rectW = thumbSize;
        lineY2 = lineY1;
    }

    rectX += padding;
    rectY += padding;
    rectW -= padding * 2;
    rectH -= padding * 2;
    g.fillRoundedRectangle(rectX, rectY, rectW, rectH, 3);
    g.setColour(juce::Colour(findColour(borderColourId)));
    g.drawLine(lineX1, lineY1, lineX2, lineY2, 1);
}
