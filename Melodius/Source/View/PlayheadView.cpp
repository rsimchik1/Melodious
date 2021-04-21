#include "PlayheadView.h"

PlayheadView::PlayheadView()
{
	playheadX = 0;
	markerHeight = 20;

	setColour(markerColourId, juce::Colour(defaultMarkerColour));
	setColour(lineColourId, juce::Colour(defaultLineColour));
}

PlayheadView::~PlayheadView()
{
}

void PlayheadView::paint(juce::Graphics& g)
{
	g.setColour(findColour(lineColourId));
	g.drawLine(playheadX, markerHeight, playheadX, getBottom(), lineThickness);

	g.setFillType(findColour(markerColourId));
	juce::Path marker;
	float x1, y1, x2, y2, x3, y3;
	x1 = playheadX;
	y1 = markerHeight;
	x2 = playheadX - (markerHeight / 2);
	y2 = 0;
	x3 = playheadX + (markerHeight / 2);
	y3 = 0;
	marker.startNewSubPath(x1, y1);
	marker.lineTo(x2, y2);
	marker.lineTo(x3, y3);
	marker.closeSubPath();
	g.fillPath(marker);
}

void PlayheadView::setPlayheadPos(int xPos)
{
	playheadX = xPos;
}

void PlayheadView::setPlayheadMarkerHeight(int height)
{
	markerHeight = height;
}
