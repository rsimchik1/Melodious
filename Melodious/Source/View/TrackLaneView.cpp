#include "TrackLaneView.h"

TrackLaneView::TrackLaneView()
{
	auto tempColour = getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId);
	getLookAndFeel().setColour(borderColourId, tempColour.brighter());
}

TrackLaneView::~TrackLaneView()
{
	for (auto *clipView : clipViews)
	{
		delete clipView;
		clipView = nullptr;
	}
	clipViews.clear();
}

void TrackLaneView::paint(juce::Graphics& g)
{
	g.setColour(getLookAndFeel().findColour(borderColourId));
	g.drawHorizontalLine(getHeight() - 1, 0, getWidth());
}

void TrackLaneView::resized()
{
}

ClipView *TrackLaneView::createClip(float startPixel, float length)
{
	auto *newClip = new ClipView();
	newClip->setBounds(startPixel, 0, length, 0);
	newClip->setTrueX(startPixel);
	clipViews.push_back(newClip);
	return newClip;
}

float TrackLaneView::getContentWidth()
{
	float width = 0;
	for (auto *clipView : clipViews)
	{
		auto clipEdge = clipView->getBounds().getWidth() + clipView->getTrueX();
		if (clipEdge > width) width = clipEdge;
	}

	return width;
}

std::vector<ClipView*>& TrackLaneView::getClipViews()
{
	return clipViews;
}
