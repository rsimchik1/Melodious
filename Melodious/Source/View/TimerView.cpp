#include "TimerView.h"

TimerView::TimerView()
{
	setColour(backgroundColourId, juce::Colour(defaultBackgroundColour));
	setColour(borderColourId, juce::Colour(defaultBorderColour));
	setColour(textColourId, juce::Colour(defaultTextColour));

	auto font = juce::Font("Alata", 20, juce::Font::FontStyleFlags::plain);

	beatText.setEditable(true);
	beatText.setFont(font);
	beatText.setColour(juce::Label::textColourId, findColour(textColourId));
	beatText.setJustificationType(juce::Justification::centred);
	addAndMakeVisible(beatText);
	tempoText.setEditable(true);
	tempoText.setFont(font);
	tempoText.setColour(juce::Label::textColourId, findColour(textColourId));
	tempoText.setJustificationType(juce::Justification::centred);
	addAndMakeVisible(tempoText);
	meterTopText.setEditable(true);
	meterTopText.setFont(font);
	meterTopText.setColour(juce::Label::textColourId, findColour(textColourId));
	meterTopText.setJustificationType(juce::Justification::centred);
	addAndMakeVisible(meterTopText);
	meterBottomText.setEditable(true);
	meterBottomText.setFont(font);
	meterBottomText.setColour(juce::Label::textColourId, findColour(textColourId));
	meterBottomText.setJustificationType(juce::Justification::centred);
	addAndMakeVisible(meterBottomText);
	for (auto i = 0; i < numBarDigits; i++)
	{
		barText.push_back(new juce::Label());
		barText[i]->setEditable(true);
		barText[i]->setFont(font);
		barText[i]->setColour(juce::Label::textColourId, findColour(textColourId));
		barText[i]->setJustificationType(juce::Justification::centred);
		addAndMakeVisible(barText[i]);
	}

	barLabel.setEditable(false);
	barLabel.setFont(font);
	barLabel.setText("BAR", juce::dontSendNotification);
	barLabel.setColour(juce::Label::textColourId, findColour(textColourId));
	barLabel.setJustificationType(juce::Justification::centred);
	addAndMakeVisible(barLabel);
	barBeatDot.setEditable(false);
	barBeatDot.setFont(font);
	barBeatDot.setText(".", juce::dontSendNotification);
	barBeatDot.setColour(juce::Label::textColourId, findColour(textColourId));
	barBeatDot.setJustificationType(juce::Justification::centred);
	addAndMakeVisible(barBeatDot);
	beatLabel.setEditable(false);
	beatLabel.setFont(font);
	beatLabel.setText("BEAT", juce::dontSendNotification);
	beatLabel.setColour(juce::Label::textColourId, findColour(textColourId));
	beatLabel.setJustificationType(juce::Justification::centred);
	addAndMakeVisible(beatLabel);
	tempoLabel.setEditable(false);
	tempoLabel.setFont(font);
	tempoLabel.setText("TEMPO", juce::dontSendNotification);
	tempoLabel.setColour(juce::Label::textColourId, findColour(textColourId));
	tempoLabel.setJustificationType(juce::Justification::centred);
	addAndMakeVisible(tempoLabel);
	meterLabel.setEditable(false);
	meterLabel.setFont(font);
	meterLabel.setText("METER", juce::dontSendNotification);
	meterLabel.setColour(juce::Label::textColourId, findColour(textColourId));
	meterLabel.setJustificationType(juce::Justification::centred);
	addAndMakeVisible(meterSlashText);
	meterSlashText.setEditable(false);
	meterSlashText.setFont(font);
	meterSlashText.setText("/", juce::dontSendNotification);
	meterSlashText.setColour(juce::Label::textColourId, findColour(textColourId));
	meterSlashText.setJustificationType(juce::Justification::centred);
	addAndMakeVisible(meterSlashText);

	setTempo(120);
	setMeter(4, 4);
	setBarAndBeat(1, 1);
}

TimerView::~TimerView()
{
	for (auto *label : barText)
	{
		delete label;
		label = nullptr;
	}
	barText.clear();
}

void TimerView::paint(juce::Graphics& g)
{
	g.setColour(findColour(backgroundColourId));
	g.fillRoundedRectangle(0, 0, getWidth(), getHeight(), borderRadius);

	g.setColour(findColour(borderColourId));
	g.drawRoundedRectangle(borderThickness/2, borderThickness/2,
		getWidth() - borderThickness, getHeight() - borderThickness,
		borderRadius, borderThickness);

	auto x = getWidth() * barAndBeatPercentWidth;
	g.drawLine(x, 0, x, getHeight(), borderThickness);
	x += getWidth() * tempoPercentWidth;
	g.drawLine(x, 0, x, getHeight(), borderThickness);
}

void TimerView::resized()
{
	auto textWidth = (getWidth() * barAndBeatPercentWidth) / 7;
	juce::Font mainFont("Arial", textWidth*1.5, juce::Font::FontStyleFlags::bold);
	auto curBounds = juce::Rectangle<int>( 0, 0,
		textWidth, getHeight());
	for (auto i = 0; i < numBarDigits; i++)
	{
		curBounds.translate(textWidth, 0);
		barText[i]->setBounds(curBounds);
		barText[i]->setFont(mainFont);
	}
	curBounds.translate(textWidth, 0);
	barBeatDot.setBounds(curBounds);
	barBeatDot.setFont(mainFont);
	curBounds.translate(textWidth, 0);
	beatText.setBounds(curBounds);
	beatText.setFont(mainFont);

	curBounds.setX(getWidth() * barAndBeatPercentWidth);
	curBounds.setWidth(getWidth() * tempoPercentWidth);
	tempoText.setBounds(curBounds);
	tempoText.setFont(mainFont);

	curBounds.setX(getWidth() - (getWidth() * meterPercentWidth));
	auto increment = (getWidth() * meterPercentWidth) / 5;
	curBounds.setWidth(textWidth);
	curBounds.translate(increment, 0);
	meterTopText.setBounds(curBounds);
	meterTopText.setFont(mainFont);
	curBounds.translate(increment, 0);
	meterSlashText.setBounds(curBounds);
	meterSlashText.setFont(mainFont);
	curBounds.translate(increment, 0);
	meterBottomText.setBounds(curBounds);
	meterBottomText.setFont(mainFont);
}

void TimerView::setTempo(unsigned tempo)
{
	this->tempo = tempo;
	tempoText.setText(std::to_string(this->tempo), juce::NotificationType::dontSendNotification);
}

void TimerView::setMeter(unsigned numerator, unsigned denominator)
{
	meter.first = numerator;
	meter.second = denominator;
	meterTopText.setText(std::to_string(meter.first), juce::NotificationType::dontSendNotification);
	meterBottomText.setText(std::to_string(meter.second), juce::NotificationType::dontSendNotification);
}

void TimerView::setBarAndBeat(unsigned bar, unsigned beat)
{
	barAndBeat.first = bar;
	barAndBeat.second = beat;

	std::ostringstream padStream;
	padStream << std::setw(numBarDigits) << std::setfill('0') << bar;
	auto paddedBar = padStream.str();
	for (auto i = 0; i < numBarDigits; i++)
	{
		barText[i]->setText(paddedBar.substr(i, 1), juce::dontSendNotification);
	}

	beatText.setText(std::to_string(beat), juce::dontSendNotification);
}
