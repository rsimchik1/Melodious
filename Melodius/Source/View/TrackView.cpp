#include "TrackView.h"

#include "../Exceptions/InvalidArgumentException.h"

TrackView::TrackView(std::string name, int sampleRate)
{
	scrollX = 0;
	padding = 0;
	setSampleRate(sampleRate);

	controls = new TrackControlsView();
	setName(name);
	controls->setName(name);
}

TrackView::~TrackView()
{
	for (auto* c : clipViews)
		delete c;

	delete controls;
}

void TrackView::paint(juce::Graphics& g)
{
	for (auto *c : clipViews)
		c->paint(g);

	g.setColour(juce::Colour(0xff737795));
	g.drawHorizontalLine(getY(), getX(), getX() + getWidth());
	g.drawHorizontalLine(getY() + getHeight(), getX(), getX() + getWidth());
}

void TrackView::resized()
{
	for (auto* c : clipViews)
		setClipBounds(c);
}

void TrackView::setPadding(int padding)
{
	this->padding = padding;
}

void TrackView::setPixelsPerSecond(float pixelsPerSecond)
{
	if (pixelsPerSecond <= 0)
		throw InvalidArgumentException();

	this->pixelsPerSecond = pixelsPerSecond;
	for (auto* c : clipViews)
		setClipBounds(c);
}

void TrackView::setScrollX(float scrollX)
{
	this->scrollX = scrollX;
	for (auto* c : clipViews)
		setClipBounds(c);
}

void TrackView::addClip(ClipView* toAdd)
{
	clipViews.push_back(toAdd);
	setClipBounds(toAdd);
}

void TrackView::setSampleRate(int sampleRate)
{
	this->sampleRate = sampleRate;
	for (auto *c : clipViews)
		setClipBounds(c);
}

void TrackView::setControlsWidth(float width)
{
	float posX = getX() + getWidth() - width;
	controls->setBounds(posX, getY(), width, getHeight());
}

void TrackView::setControlsColours(juce::Colour background, juce::Colour text)
{
	controls->setColour(TrackControlsView::BACKGROUND_COLOR, background);
	controls->setColour(TrackControlsView::TEXT_COLOR, text);
	controls->setColour(TrackControlsView::BORDER_COLOR, findColour(BORDER_COLOR));
}

TrackControlsView* TrackView::getControls()
{
	return controls;
}

float TrackView::sampleToPixel(uint32_t sample)
{
	return (sample * pixelsPerSecond) / sampleRate;
}

void TrackView::setClipBounds(ClipView* clip)
{
	float clipX = sampleToPixel(clip->getStartSample()) - scrollX;
	float clipWidth = sampleToPixel(clip->getEndSample()) - clipX;
	clip->setBounds(clipX, getY() + padding, clipWidth - scrollX, getHeight() - padding * 2);
}

