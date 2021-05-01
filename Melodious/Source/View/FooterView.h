#pragma once

#include "ButtonLookAndFeel.h"
#include "JuceHeader.h"
#include "../Controller/Observable.h"

class FooterView : public juce::Component,
                   public Observable<FooterView>,
	public juce::Button::Listener
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
	void buttonClicked(juce::Button*) override;
	void showLoadingMessage();
	void hideLoadingMessage();
private:
	int padding = 10;
	int borderThickness = 4;
	
	juce::Image logoImage;
	juce::ImageComponent logo;
	juce::TextButton renderButton;
	ButtonLookAndFeel buttonLookAndFeel;
};
