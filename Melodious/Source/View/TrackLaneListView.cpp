#include "TrackLaneListView.h"

#include "TrackControlsView.h"

TrackLaneListView::TrackLaneListView()
{
	getLookAndFeel().setColour(backgroundColourId, juce::Colour(defaultBackgroundColour));
	getLookAndFeel().setColour(majorLineColourId, juce::Colour(defaultMajorLineColour));
	getLookAndFeel().setColour(minorLineColourId, juce::Colour(defaultMinorLineColour));

	this->lineSpacing = 70;
	this->scrollXAmount = 0;
	this->scrollYAmount = 0;
	this->scrollXBounds = std::pair<float, float>(0, 0);
	this->scrollYBounds = std::pair<float, float>(0, 0);
}

TrackLaneListView::~TrackLaneListView()
{
	for (auto *child : children)
	{
		delete child;
		child = nullptr;
	}
	children.clear();
}

void TrackLaneListView::paint(juce::Graphics& g)
{
	g.fillAll(getLookAndFeel().findColour(backgroundColourId));

	float measureSpacing = numSubdivisions * lineSpacing;
	for (auto x = fmod(-scrollXAmount, measureSpacing); x < getWidth(); x += measureSpacing)
	{
		g.setColour(findColour(majorLineColourId));
		g.drawVerticalLine(x, 0, getHeight());
		for (auto sub = 1; sub < numSubdivisions; sub++)
		{
			auto xi = x + (measureSpacing / numSubdivisions) * sub;
			g.setColour(findColour(minorLineColourId));
			g.drawVerticalLine(xi, 0, getHeight());
		}
	}
}

void TrackLaneListView::resized()
{
	calculateScrollXBounds();
	calculateScrollYBounds();

	auto trackLaneBounds = getLocalBounds();
	trackLaneBounds.translate(0, -scrollYAmount);

	for (auto *child : children)
	{
		trackLaneBounds.setSize(getWidth(), child->getHeight());
		child->setBounds(trackLaneBounds);

		auto clipViewBounds = trackLaneBounds;
		clipViewBounds.removeFromBottom(TrackLaneView::paddingPixels);
		clipViewBounds.removeFromTop(TrackLaneView::paddingPixels);

		for (auto *clipView : child->getClipViews())
		{
			auto oldBounds = clipView->getBounds();
			clipViewBounds.setX(clipView->getTrueX());
			clipViewBounds.setWidth(oldBounds.getWidth());
			clipViewBounds.translate(-scrollXAmount, 0);
			clipView->setBounds(clipViewBounds);
		}

		trackLaneBounds.translate(0, child->getHeight());
	}
}

TrackLaneView* TrackLaneListView::appendNewTrackLane()
{
	auto *newLane = new TrackLaneView();
	newLane->setLookAndFeel(&getLookAndFeel());
	children.push_back(newLane);
	addAndMakeVisible(newLane);
	resized();
	return newLane;
}

TrackLaneView* TrackLaneListView::getTrackLaneAt(int index)
{
	return children[index];
}

void TrackLaneListView::scrollX(float deltaX)
{
	setScrollX(scrollXAmount + deltaX);
}

void TrackLaneListView::scrollY(float deltaY)
{
	setScrollY(scrollYAmount + deltaY);
}

void TrackLaneListView::setScrollX(float x)
{
	scrollXAmount = x;
	if (scrollXAmount < scrollXBounds.first) scrollXAmount = scrollXBounds.first;
	if (scrollXAmount > scrollXBounds.second) scrollXAmount = scrollXBounds.second;

	resized();
	repaint();
}

void TrackLaneListView::setScrollY(float y)
{
	scrollYAmount = y;
	if (scrollYAmount < scrollYBounds.first) scrollYAmount = scrollYBounds.first;
	if (scrollYAmount > scrollYBounds.second) scrollYAmount = scrollYBounds.second;

	resized();
	repaint();
}

float TrackLaneListView::getContentHeight()
{
	float height = 0;
	for (auto* child : children)
		height += child->getHeight();

	height += TrackControlsView::DEFAULT_HEIGHT;

	return height;
}

float TrackLaneListView::getContentWidth()
{
	float width = 0;
	for (auto *child : children)
	{
		auto childWidth = child->getContentWidth();
		if (childWidth > width) width = childWidth;
	}

	return width;
}

void TrackLaneListView::setSubdivisionWidth(float widthPixels)
{
	lineSpacing = widthPixels;
}

void TrackLaneListView::setNumSubdivisions(int subdivisions)
{
	this->numSubdivisions = subdivisions;
}

void TrackLaneListView::calculateScrollXBounds()
{
	scrollXBounds.first = 0;
	scrollXBounds.second = getContentWidth() > getWidth() ? 
		getContentWidth() - getWidth() :
		0;
}

void TrackLaneListView::calculateScrollYBounds()
{
	scrollYBounds.first = 0;
	scrollYBounds.second = getContentHeight() > getHeight() ? 
		getContentHeight() - getHeight() :
		0;
}
