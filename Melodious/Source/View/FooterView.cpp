#include "FooterView.h"

FooterView::FooterView()
	: logoImage(juce::ImageFileFormat::loadFrom(juce::File(logoPath)))
{
	setColour(backgroundColourId, juce::Colour(defaultBackgroundColour));
	setColour(borderColourId, juce::Colour(defaultBorderColour));
	setColour(textColourId, juce::Colour(defaultTextColour));

	;

	logo.setImage(logoImage);

	renderButton.setButtonText("Render");
	renderButton.setColour(juce::TextButton::textColourOnId, 
						   findColour(textColourId));
	renderButton.setColour(juce::TextButton::textColourOffId,
						   findColour(textColourId));
	renderButton.setColour(juce::TextButton::buttonColourId,
						   juce::Colours::transparentBlack);
	renderButton.setColour(juce::TextButton::buttonOnColourId,
						   juce::Colour(0x44000000));
	renderButton.setColour(juce::ComboBox::outlineColourId, 
						   juce::Colours::transparentBlack);

	addAndMakeVisible(logo);
	addAndMakeVisible(renderButton);
}

FooterView::~FooterView()
{
}

void FooterView::paint(juce::Graphics& g)
{
	g.fillAll(findColour(backgroundColourId));

	g.setColour(findColour(borderColourId));
	auto borderY = static_cast<float>(borderThickness) / 2;
	g.drawLine(0, borderY, getWidth(), borderY, borderThickness);
}

void FooterView::resized()
{
	auto contentHeight = (getHeight() - borderThickness) - padding * 2;

	auto contentBounds = juce::Rectangle<int>(padding, borderThickness + padding,
											  contentHeight, contentHeight);
	logo.setBounds(contentBounds);
	logo.setImage(logoImage.rescaled(logo.getWidth(), logo.getHeight(),
									 juce::Graphics::highResamplingQuality));

	contentBounds.setX(logo.getRight() + padding);
	contentBounds.setWidth(renderButton.getBestWidthForHeight(contentHeight));
	renderButton.setBounds(contentBounds);
}
