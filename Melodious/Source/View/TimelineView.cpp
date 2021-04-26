#include "TimelineView.h"

TimelineView::TimelineView()
	: measureSizePixels(70),
	subdivideBy(2),
	numSubdivisions(2),
	minSpacingPixels(10),
	paddingPixels(10),
	borderThickness(2),
	spacerWidth(0),
	spacerBorderThickness(2),
	minScrollX(0),
	scrollXAmount(minScrollX)
{
	measureTextFont = juce::Font(juce::Typeface::createSystemTypefaceFor(
		BinaryData::AlataRegular_ttf,
		BinaryData::AlataRegular_ttfSize));

	setSubdivisionWidth(20);

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
	const auto xOffset = paddingPixels / 3;
	const auto yOffset = paddingPixels / 2 + borderThickness;
	measureTextFont.setHeight(getHeight() - yOffset);
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
			const auto subYOffset = (yOffset - borderThickness) / 2.0f + borderThickness;
			if (xi > getWidth() - spacerWidth) break;
			g.setColour(getLookAndFeel().findColour(minorLineColourId));
			g.drawVerticalLine(xi, getHeight() - subYOffset, 
							   getHeight());
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

void TimelineView::setMeter(int numerator, int denominator)
{
	this->subdivideBy = numerator;
	this->numSubdivisions = 1; // TODO figure this out
}

void TimelineView::setSubdivisionWidth(double samplesPerBeat)
{
	measureSizePixels = samplesPerBeat * subdivideBy * numSubdivisions;
}
