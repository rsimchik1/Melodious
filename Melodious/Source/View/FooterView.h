#pragma once

#include "JuceHeader.h"

class FooterView : public juce::Component
{
public:
	enum ColourIds
	{
		backgroundColourId = 0x20000111,
		borderColourId = 0x2000012,
		textColourId = 0x2000013
	};

	enum DefaultColours
	{
		defaultBackgroundColour = 0xff131b5d,
		defaultBorderColour = 0xffffffff,
		defaultTextColour = 0xffffffff
	};

	FooterView();
	~FooterView() override;

	void paint(juce::Graphics& g) override;
	void resized() override;
private:
	const std::string logoPath = "D:/Documents/dev/Melodious/Melodious/Source/img/logo.png";

	int padding = 2;
	int borderThickness = 4;
	
	juce::Image logoImage;
	juce::ImageComponent logo;
	juce::TextButton renderButton;
};