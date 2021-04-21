#include "MixHeaderView.h"

MixHeaderView::MixHeaderView()
{
	setColour(backgroundColourId, juce::Colour(defaultBackgroundColour));
	setColour(borderColourId, juce::Colour(defaultBorderColour));

	addAndMakeVisible(timerView);

    buttonLookAndFeel = new ButtonLookAndFeel();
    buttonLookAndFeel->setColour(juce::ComboBox::outlineColourId, juce::Colours::transparentBlack);
    buttonLookAndFeel->setColour(juce::TextButton::buttonColourId, juce::Colour(TimerView::defaultBackgroundColour));
    buttonLookAndFeel->setColour(juce::TextButton::textColourOffId, juce::Colours::white);
	buttonLookAndFeel->setBorderThickness(0);

	buttonsBackground.setFill(juce::Colour(TimerView::defaultBorderColour));
	buttonsBackground.setCornerSize(juce::Point<float>(5, 5));
	addAndMakeVisible(buttonsBackground);

	backButton = new juce::TextButton();
	backButton->setButtonText("<<");
	rewindButton = new juce::TextButton();
	rewindButton->setButtonText("<");
	playPauseButton = new juce::TextButton();
	playPauseButton->setButtonText("PLAY");
	fastForwardButton = new juce::TextButton();
	fastForwardButton->setButtonText(">");
	nextButton = new juce::TextButton();
	nextButton->setButtonText(">>");
	stopButton = new juce::TextButton();
	stopButton->setButtonText("STOP");
	recordButton = new juce::TextButton();
	recordButton->setButtonText("REC");

	buttons.push_back(backButton);
	buttons.push_back(rewindButton);
	buttons.push_back(playPauseButton);
	buttons.push_back(fastForwardButton);
	buttons.push_back(nextButton);
	buttons.push_back(stopButton);
	buttons.push_back(recordButton);

	for (auto* button : buttons)
	{
		button->setLookAndFeel(buttonLookAndFeel);
		addAndMakeVisible(button);
	}
}

MixHeaderView::~MixHeaderView()
{
	for (auto *button : buttons)
	{
		delete button;
		button = nullptr;
	}
	buttons.clear();
	delete buttonLookAndFeel;
}

void MixHeaderView::paint(juce::Graphics& g)
{
	g.fillAll(findColour(backgroundColourId));
	g.setColour(findColour(borderColourId));
	auto y = getHeight() - borderThickness / 2;
	g.drawLine(0, y, getWidth(), y, borderThickness);
}

void MixHeaderView::resized()
{
	int buttonMargin = 3;
	auto numButtons = buttons.size();
	auto buttonHeight = getHeight() - borderThickness - padding * 2 - buttonMargin * 2;
	auto buttonBounds = juce::Rectangle<int>(
		getWidth() - (padding + buttonHeight), padding + buttonMargin,
		buttonHeight, buttonHeight);
	for (auto i = numButtons; i >= 1; i--)
	{
		buttons[i - 1]->setBounds(buttonBounds);
		buttonBounds.translate(-buttonBounds.getWidth() - buttonMargin, 0);
	}

	auto buttonBackgroundBounds = buttonBounds;
	buttonBackgroundBounds.translate(0, -buttonMargin);
	buttonBackgroundBounds.setHeight(buttonBackgroundBounds.getHeight() + buttonMargin * 2);
	buttonBackgroundBounds.setX(buttons[0]->getX() - buttonMargin);
	buttonBackgroundBounds.setWidth(buttons[numButtons - 1]->getRight() - buttons[0]->getX() + buttonMargin * 2);
	buttonsBackground.setRectangle(buttonBackgroundBounds.toType<float>());

	auto timerHeight = getHeight() - borderThickness - padding * 2;
	timerView.setBounds(padding, padding, timerHeight * 5, timerHeight);
}
