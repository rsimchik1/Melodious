#include "TimerView.h"

TimerView::TimerView()
{
	setColour(backgroundColourId, juce::Colour(defaultBackgroundColour));
	setColour(borderColourId, juce::Colour(defaultBorderColour));
	setColour(textColourId, juce::Colour(defaultTextColour));

	mainFont = juce::Font(juce::Typeface::createSystemTypefaceFor(
		BinaryData::AlataRegular_ttf,
		BinaryData::AlataRegular_ttfSize));

	beatText.setEditable(true);
	allLabels.push_back(&beatText);
	tempoText.setEditable(true);
	allLabels.push_back(&tempoText);
	meterTopText.setEditable(true);
	allLabels.push_back(&meterTopText);
	meterBottomText.setEditable(true);
	allLabels.push_back(&meterBottomText);

	for (auto i = 0; i < numBarDigits; i++)
	{
		barText.push_back(new juce::Label());
		barText[i]->setEditable(true);
		allLabels.push_back(barText[i]);
	}

	barLabel.setEditable(false);
	barLabel.setText("BAR", juce::dontSendNotification);
	allLabels.push_back(&barLabel);
	barBeatDot.setEditable(false);
	barBeatDot.setText(".", juce::dontSendNotification);
	allLabels.push_back(&barBeatDot);
	beatLabel.setEditable(false);
	beatLabel.setText("BEAT", juce::dontSendNotification);
	allLabels.push_back(&beatLabel);
	tempoLabel.setEditable(false);
	tempoLabel.setText("TEMPO", juce::dontSendNotification);
	allLabels.push_back(&tempoLabel);
	meterLabel.setEditable(false);
	meterLabel.setText("METER", juce::dontSendNotification);
	allLabels.push_back(&meterLabel);
	meterSlashText.setEditable(false);
	meterSlashText.setText("/", juce::dontSendNotification);
	allLabels.push_back(&meterSlashText);

	for (auto label : allLabels)
	{
		label->setColour(juce::Label::textColourId, findColour(textColourId));
		label->setJustificationType(juce::Justification::verticallyCentred);
		addAndMakeVisible(label);
	}

	tempoText.setJustificationType(juce::Justification::centred);
	barLabel.setJustificationType(juce::Justification::centred);
	beatLabel.setJustificationType(juce::Justification::centred);
	tempoLabel.setJustificationType(juce::Justification::centred);
	meterLabel.setJustificationType(juce::Justification::centred);

	setTempo(120);
	setMeter(4, 4);
	setBeat(0);

	startTimer(40);
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
	mainFont.setHeight(textWidth*2.5);
	auto labelWidth = textWidth * 1.5;
	auto curBounds = juce::Rectangle<int>( 0, borderThickness,
		labelWidth, getHeight() * (1-labelPercentHeight) - borderThickness);
	auto textColour = findColour(textColourId);
	auto thisColour = textColour.withAlpha(0.5f);
	for (auto i = 0; i < numBarDigits; i++)
	{
		if (barText[i]->getText() != "0")
			thisColour = textColour;

		curBounds.translate(textWidth, 0);
		barText[i]->setBounds(curBounds);
		barText[i]->setFont(mainFont);
		barText[i]->setColour(juce::Label::textColourId, thisColour);
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
	auto increment = (getWidth() * meterPercentWidth) / 6;
	labelWidth *= 0.8;
	mainFont.setHeight(mainFont.getHeight() * 0.8);
	curBounds.setWidth(labelWidth);
	curBounds.translate(increment, 0);
	meterTopText.setBounds(curBounds);
	meterTopText.setFont(mainFont);
	curBounds.translate(increment, 0);
	meterSlashText.setBounds(curBounds);
	meterSlashText.setFont(mainFont);
	curBounds.translate(increment, 0);
	meterBottomText.setBounds(curBounds);
	meterBottomText.setFont(mainFont);

	mainFont.setHeight(getHeight() * labelPercentHeight);
	curBounds.setHeight(mainFont.getHeight());
	curBounds.setY(getHeight() - curBounds.getHeight() - borderThickness * 2);
	curBounds.setWidth(barText[1]->getWidth());
	curBounds.setX(barText[1]->getX());
	barLabel.setFont(mainFont);
	barLabel.setBounds(curBounds);
	
	curBounds.setWidth(beatText.getWidth());
	curBounds.setX(beatText.getX());
	beatLabel.setFont(mainFont);
	beatLabel.setBounds(curBounds);

	curBounds.setWidth(tempoText.getWidth());
	curBounds.setX(tempoText.getX());
	tempoLabel.setFont(mainFont);
	tempoLabel.setBounds(curBounds);

	curBounds.setWidth(meterBottomText.getRight() - meterTopText.getX());
	curBounds.setX(meterTopText.getX());
	meterLabel.setFont(mainFont);
	meterLabel.setBounds(curBounds);
}

void TimerView::setTempo(unsigned tempo)
{
	this->tempo = tempo;
	tempoText.setText(std::to_string(this->tempo), juce::NotificationType::sendNotification);
}

void TimerView::setMeter(unsigned numerator, unsigned denominator)
{
	meter.first = numerator;
	meter.second = denominator;
	meterTopText.setText(std::to_string(meter.first), juce::NotificationType::sendNotification);
	meterBottomText.setText(std::to_string(meter.second), juce::NotificationType::sendNotification);
}

void TimerView::setBarAndBeat(unsigned bar, unsigned beat)
{
	std::ostringstream padStream;
	padStream << std::setw(numBarDigits) << std::setfill('0') << barAndBeat.first;
	auto paddedBar = padStream.str();
	for (auto i = 0; i < numBarDigits; i++)
	{
		barText[i]->setText(paddedBar.substr(i, 1), juce::sendNotification);
	}

	beatText.setText(std::to_string(barAndBeat.second), juce::sendNotification);
}

void TimerView::labelTextChanged(juce::Label* labelThatHasChanged)
{
	resized();
}

void TimerView::notify(Timeline* caller)
{
	auto samplesPerBeat = caller->getSamplesPerBeat(tempo);
	auto numSamples = caller->getPlaybackHead();
	setBeat(numSamples / samplesPerBeat);
}

void TimerView::timerCallback()
{
	if (update)
		setBarAndBeat(barAndBeat.first, barAndBeat.second);
}

void TimerView::setBeat(uint64_t beat)
{
	barAndBeat.first = beat / meter.second + 1;
	barAndBeat.second = beat % meter.first + 1;
	update = true;
}
