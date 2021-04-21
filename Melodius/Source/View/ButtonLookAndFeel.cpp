#include "ButtonLookAndFeel.h"

ButtonLookAndFeel::ButtonLookAndFeel()
{
	borderThickness = 2;
}

ButtonLookAndFeel::~ButtonLookAndFeel()
{
}

void ButtonLookAndFeel::drawButtonBackground(juce::Graphics& g, juce::Button& button, const juce::Colour& backgroundColour,
	bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown)
{
	auto buttonArea = button.getLocalBounds();
	auto adjustedColour = backgroundColour;
	if (shouldDrawButtonAsDown) adjustedColour = adjustedColour.darker();
	if (shouldDrawButtonAsHighlighted) adjustedColour = adjustedColour.brighter();
	g.setColour(adjustedColour);
	g.fillRect(buttonArea);
	g.setColour(findColour(juce::ComboBox::outlineColourId));
	g.drawRect(buttonArea);
}

void ButtonLookAndFeel::setBorderThickness(int thickness)
{
	borderThickness = thickness;
}
