#include "TimelineView.h"

TimelineView::TimelineView()
{
	this->minSpacingPixels = 10;
	this->subdivideBy = 2;
	this->numSubdivisions = 2;
	this->measureSizePixels = 70;
	this->paddingPixels = 10;
	this->borderThickness = 2;
	this->minScrollX = 0;
	this->scrollXAmount = minScrollX;
	this->spacerWidth = 0;
	this->spacerBorderThickness = 2;

	getLookAndFeel().setColour(backgroundColourId, juce::Colour(defaultBackgroundColour));
	getLookAndFeel().setColour(textColourId, juce::Colour(defaultTextColour));
	getLookAndFeel().setColour(majorLineColourId, juce::Colour(defaultMajorLineColour));
	getLookAndFeel().setColour(minorLineColourId, juce::Colour(defaultMinorLineColour));
	getLookAndFeel().setColour(borderColourId, juce::Colour(defaultBorderColour));
	getLookAndFeel().setColour(spacerBorderColourId, juce::Colour(defaultSpacerBorderColour));
}

TimelineView::~TimelineView()
{
}

void TimelineView::paint(juce::Graphics& g)
{
	g.fillAll(getLookAndFeel().findColour(backgroundColourId));

	// Measure text and major ticks
	auto xOffset = paddingPixels / 3;
	auto yOffset = paddingPixels / 2 + borderThickness;
	auto measureTextFont = juce::Font("Calibri Light", getHeight() - (paddingPixels * 5/3), juce::Font::plain);
	g.setFont(measureTextFont);
	int i = (scrollXAmount / measureSizePixels) + 1;
	for (auto x = fmod(-scrollXAmount, measureSizePixels); x < getWidth() - spacerWidth; x+=measureSizePixels)
	{

		g.setColour(getLookAndFeel().findColour(textColourId));
		g.drawText(std::to_string(i), x + xOffset, 0, getHeight(), getHeight() - yOffset, 
			juce::Justification::left, false);
		
		g.setColour(getLookAndFeel().findColour(majorLineColourId));
		g.drawVerticalLine(x, getHeight() - yOffset, getHeight());
		g.drawHorizontalLine(getHeight() - yOffset, x, x + xOffset);

		for (auto sub = 1; sub < numSubdivisions * subdivideBy; sub++)
		{
			auto xi = x + (measureSizePixels / (numSubdivisions * subdivideBy)) * sub;
			if (xi > getWidth() - spacerWidth) break;
			g.setColour(getLookAndFeel().findColour(minorLineColourId));
			g.drawVerticalLine(xi, getHeight() - yOffset, getHeight());
		}

		i++;
	}

	g.setColour(getLookAndFeel().findColour(borderColourId));
	g.drawLine(0, getHeight() - borderThickness / 2, getWidth(),
		getHeight() - borderThickness / 2, borderThickness);

	auto spacerX = getWidth() - spacerWidth + spacerBorderThickness / 2;
	g.setColour(findColour(backgroundColourId));
	g.fillRect(spacerX, 0, spacerWidth, getHeight() - borderThickness
	);
	
	g.setColour(getLookAndFeel().findColour(spacerBorderColourId));
	g.drawLine(spacerX, 0, spacerX, getHeight(), spacerBorderThickness);
}

void TimelineView::resized()
{
}

void TimelineView::scrollX(float deltaX)
{
	setScrollX(scrollXAmount + deltaX);
}

// can't scroll Y
void TimelineView::scrollY(float deltaY)
{
	return;
}

void TimelineView::setScrollX(float x)
{
	scrollXAmount = x;
	if (scrollXAmount < minScrollX) scrollXAmount = minScrollX;

	repaint();
}

// can't scroll Y
void TimelineView::setScrollY(float y)
{
	return;
}

// shouldn't force parent to show scrollbar
float TimelineView::getContentWidth()
{
	return 0;
}

float TimelineView::getContentHeight()
{
	return 0;
}

void TimelineView::setSpacerWidth(float newWidth)
{
	this->spacerWidth = newWidth;
	resized();
	repaint();
}
