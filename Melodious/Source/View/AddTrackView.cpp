#include "AddTrackView.h"

#include "TrackControlsView.h"

AddTrackView::AddTrackView()
{
	setColour(TrackControlsView::borderColourId, juce::Colour(TrackControlsView::defaultBorderColour));
	setColour(TrackControlsView::backgroundColourId, juce::Colour(TrackControlsView::defaultBackgroundColour));
	addButtonLookAndFeel = new AddButtonLookAndFeel();
	addButton.setLookAndFeel(addButtonLookAndFeel);
	addButton.setButtonText("+ Add New");
	addAndMakeVisible(addButton);
}

AddTrackView::~AddTrackView()
{
	addButton.setLookAndFeel(nullptr);
	delete addButtonLookAndFeel;
	addButtonLookAndFeel = nullptr;
}

void AddTrackView::paint(juce::Graphics& g)
{
	g.fillAll(findColour(TrackControlsView::backgroundColourId));
	g.setColour(findColour(TrackControlsView::borderColourId));
	g.drawHorizontalLine(getHeight() - borderSize, 0, getWidth());
}

void AddTrackView::resized()
{
	auto addButtonBounds = getLocalBounds();
	addButtonBounds.removeFromBottom(borderSize);
	addButton.setBounds(addButtonBounds);
}

void AddTrackView::addListener(juce::Button::Listener* listener)
{
	addButton.addListener(listener);
}

AddTrackView::AddButtonLookAndFeel::AddButtonLookAndFeel()
{
	setColour(juce::TextButton::buttonColourId, juce::Colours::transparentBlack);
	setColour(juce::TextButton::textColourOffId, juce::Colour(defaultTextColour));
	setColour(juce::ComboBox::outlineColourId, juce::Colours::transparentBlack);
}

juce::Font AddTrackView::AddButtonLookAndFeel::getTextButtonFont(juce::TextButton&, int buttonHeight)
{
	return juce::Font("Arial", fontSize, juce::Font::FontStyleFlags::bold);
}
