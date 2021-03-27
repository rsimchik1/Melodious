#include "TrackControlsView.h"

TrackControlsView::TrackControlsView()
{
}

void TrackControlsView::paint(juce::Graphics& g)
{
	g.setColour(findColour(BACKGROUND_COLOR));
	g.fillRect(getBounds());

	g.setColour(findColour(TEXT_COLOR));
	auto titleFont = juce::Font("Arial", fontSize, juce::Font::plain);
	g.setFont(titleFont);
	g.drawText(getName(), getX() + padding + leftMargin, getY() + padding, getWidth() - 30.0f - padding * 2 - leftMargin, fontSize, juce::Justification::left, true);

	g.setColour(findColour(BORDER_COLOR));
	g.drawHorizontalLine(getY(), getX(), getX() + getWidth());
	g.drawHorizontalLine(getY() + getHeight(), getX(), getX() + getWidth());
}

void TrackControlsView::resized()
{
}
