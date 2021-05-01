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

void ButtonLookAndFeel::drawImageButton(juce::Graphics& g, juce::Image* image,
	int imageX, int imageY, int imageW, int imageH,
	const juce::Colour& overlayColour, float imageOpacity, juce::ImageButton& button)
{
	drawButtonBackground(g, button, findColour(juce::TextButton::buttonColourId),
						 false, false);
	LookAndFeel_V4::drawImageButton(g, image, imageX, imageY, imageW, imageH, 
									overlayColour, imageOpacity, button);
}

void ButtonLookAndFeel::setButtonFont(juce::Font font)
{
	this->buttonFont = font;
}

juce::Font ButtonLookAndFeel::getTextButtonFont(juce::TextButton&,
	int buttonHeight)
{
	return buttonFont;
}
