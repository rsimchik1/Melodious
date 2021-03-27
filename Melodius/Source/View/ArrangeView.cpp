#include "ArrangeView.h"

#include "../Exceptions/InvalidArgumentException.h"

ArrangeView::ArrangeView()
{
    pixelsPerSecond = 35;
    trackHeight = 115;
    trackPadding = 5;
    trackControlsWidth = 250.0f;
    playbackHead = 0;
    sampleRate = 1;
    scrollX = 0;

    setFramesPerSecond(60);
}

ArrangeView::~ArrangeView()
{
    for (auto* track : trackViews)
        delete track;
}

void ArrangeView::update()
{
}

void ArrangeView::paint(juce::Graphics& g)
{
    g.fillAll(findColour(BACKGROUND_COLOR));
    
    g.setColour(findColour(BORDER_LIGHT_COLOR));
	for (auto x = 0; x < (getWidth() + scrollX) / pixelsPerSecond; x++)
        g.drawVerticalLine(getX() + x * pixelsPerSecond - scrollX, getY(), getHeight());

    for (auto *track : trackViews)
        track->paint(g);

    // playback head
    float playPos = playbackHead * pixelsPerSecond / sampleRate;
    g.setColour(findColour(PLAYHEAD_COLOR));
    g.drawLine(getX() + playPos - scrollX, getY(), getX() + playPos - scrollX, getY() + getHeight(), 1);

	// controls pane
    float posX = getWidth() - trackControlsWidth;
    g.setColour(findColour(BACKGROUND_COLOR));
    g.fillRect(getX() + posX, (float) getY(), trackControlsWidth, (float) getHeight());
    for (auto* track : trackViews)
        track->getControls()->paint(g);

    g.setColour(findColour(BORDER_HEAVY_COLOR));
    g.drawLine(getX() + posX, getY(), getX() + posX, getY() + getHeight(), 3);
}

void ArrangeView::setTime(int32_t sample)
{
    this->playbackHead = sample;
}

void ArrangeView::setSampleRate(int sampleRate)
{
    this->sampleRate = sampleRate;
    for (auto t : trackViews)
        t->setSampleRate(sampleRate);
}

void ArrangeView::addTrack(TrackView *toAdd)
{
    trackViews.push_back(toAdd);
    setTrackBounds(trackViews.size() - 1);
    toAdd->setColour(TrackView::BORDER_COLOR, findColour(BORDER_LIGHT_COLOR));
    toAdd->setControlsColours(findColour(BACKGROUND_COLOR),findColour(TEXT_COLOR));
}

void ArrangeView::resized()
{
    for (auto i = 0; i < trackViews.size(); i++)
        setTrackBounds(i);
}

void ArrangeView::scrollXOffset(float offset)
{
    this->scrollX += offset;
    if (this->scrollX < 0) this->scrollX = 0;
    for (auto* t : trackViews)
        t->setScrollX(this->scrollX);
}

void ArrangeView::zoomX(float zoomAmount)
{
    pixelsPerSecond += zoomAmount;
    if (pixelsPerSecond < 1) pixelsPerSecond = 1;
    for (auto i = 0; i < trackViews.size(); i++)
        setTrackBounds(i);
}

void ArrangeView::setTrackBounds(int trackIndex)
{
    if (trackIndex < 0 || trackIndex >= trackViews.size())
        throw InvalidArgumentException();
	
	auto* track = trackViews[trackIndex]; 
    auto yOffset = trackIndex * trackHeight; 
	track->setPadding(trackPadding);
	track->setPixelsPerSecond(pixelsPerSecond);
	track->setBounds(getX(), getY() + yOffset, getWidth(), trackHeight); 
    track->setControlsWidth(trackControlsWidth);
}

void ArrangeView::mouseWheelMove(const juce::MouseEvent& event, const juce::MouseWheelDetails& wheel)
{
    if (juce::ModifierKeys::currentModifiers.isShiftDown())
        if (juce::ModifierKeys::currentModifiers.isCtrlDown()) zoomX(-wheel.deltaY * zoomSensitivity);
        else scrollXOffset(-wheel.deltaY * scrollSensitivity);
}
