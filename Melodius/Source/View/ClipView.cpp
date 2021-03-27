#include "ClipView.h"

#include "../Exceptions/InvalidArgumentException.h"

ClipView::ClipView(uint32_t start, uint32_t end)
{
	this->start = start;
	this->end = end;
}

void ClipView::paint(juce::Graphics& g)
{
	g.setColour(fillColor);
	g.fillRoundedRectangle(getX(), getY(), getWidth(), getHeight(), borderRadius);

	g.setColour(borderColor);
	g.drawRoundedRectangle(getX(), getY(), getWidth(), getHeight(), borderRadius, borderThickness);
}

uint32_t ClipView::getStartSample()
{
	return start;
}

uint32_t ClipView::getEndSample()
{
	return end;
}

void ClipView::setStartEndSample(uint32_t start, uint32_t end)
{
	if (end < start)
		throw InvalidArgumentException();

	this->start = start;
	this->end = end;
}

void ClipView::setColor(juce::Colour fillColor)
{
	this->fillColor = fillColor;
	this->borderColor = fillColor.darker(0.8f);
}
