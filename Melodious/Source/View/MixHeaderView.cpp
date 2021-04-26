#include "MixHeaderView.h"

MixHeaderView::MixHeaderView()
	: lastState(false, false, false, false, false, 
				false, false, false, false, false)
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

	backImage = juce::ImageCache::getFromMemory(BinaryData::backbutton_png,
												BinaryData::backbutton_pngSize);
	rewindImage = juce::ImageCache::getFromMemory(BinaryData::frbutton_png,
												  BinaryData::frbutton_pngSize);
	playImage = juce::ImageCache::getFromMemory(BinaryData::playbutton_png,
												BinaryData::playbutton_pngSize);
	pauseImage = juce::ImageCache::getFromMemory(BinaryData::pausebutton_png,
												 BinaryData::pausebutton_pngSize);
	fastForwardImage = juce::ImageCache::getFromMemory(BinaryData::ffbutton_png,
													   BinaryData::ffbutton_pngSize);
	nextImage = juce::ImageCache::getFromMemory(BinaryData::nextbutton_png,
												BinaryData::nextbutton_pngSize);
	stopImage = juce::ImageCache::getFromMemory(BinaryData::stopbutton_png,
												BinaryData::stopbutton_pngSize);
	recordImage = juce::ImageCache::getFromMemory(BinaryData::recordbutton_png,
												  BinaryData::recordbutton_pngSize);

	const auto targetSize = 30.0f;
	backImage = backImage.rescaled(targetSize * 0.8f, targetSize * 0.8f, 
								   juce::Graphics::highResamplingQuality);
	rewindImage = rewindImage.rescaled(targetSize, targetSize,
									   juce::Graphics::highResamplingQuality);
	playImage = playImage.rescaled(targetSize, targetSize,
								   juce::Graphics::highResamplingQuality);
	pauseImage = pauseImage.rescaled(targetSize, targetSize,
									 juce::Graphics::highResamplingQuality);
	fastForwardImage = fastForwardImage.rescaled(targetSize, targetSize, 
												 juce::Graphics::highResamplingQuality);
	nextImage = nextImage.rescaled(targetSize * 0.8f, targetSize * 0.8f,
								   juce::Graphics::highResamplingQuality);
	stopImage = stopImage.rescaled(targetSize, targetSize,
								   juce::Graphics::highResamplingQuality);
	recordImage = recordImage.rescaled(targetSize, targetSize,
									   juce::Graphics::highResamplingQuality);
	
	backButton = new juce::ImageButton();
	backButton->setImages(false, false, true,
						  backImage, 1.0f, juce::Colours::transparentBlack,
						  backImage, 1.0f, juce::Colour(0x33000000),
						  backImage, 1.0f, juce::Colour(0x55000000));
	rewindButton = new juce::ImageButton();
	rewindButton->setImages(false, false, true,
						  rewindImage, 1.0f, juce::Colours::transparentBlack,
						  rewindImage, 1.0f, juce::Colour(0x33000000),
						  rewindImage, 1.0f, juce::Colour(0x55000000));
	playPauseButton = new juce::ImageButton();
	setPlayPauseButtonImage(playPauseButton, isPaused);
	fastForwardButton = new juce::ImageButton();
	fastForwardButton->setImages(false, false, true,
						  fastForwardImage, 1.0f, juce::Colours::transparentBlack,
						  fastForwardImage, 1.0f, juce::Colour(0x33000000),
						  fastForwardImage, 1.0f, juce::Colour(0x55000000));
	nextButton = new juce::ImageButton();
	nextButton->setImages(false, false, true,
						  nextImage, 1.0f, juce::Colours::transparentBlack,
						  nextImage, 1.0f, juce::Colour(0x33000000),
						  nextImage, 1.0f, juce::Colour(0x55000000));
	stopButton = new juce::ImageButton();
	stopButton->setImages(false, false, true,
						  stopImage, 1.0f, juce::Colours::transparentBlack,
						  stopImage, 1.0f, juce::Colour(0x33000000),
						  stopImage, 1.0f, juce::Colour(0x55000000));
	recordButton = new juce::ImageButton();
	recordButton->setImages(false, false, true,
						  recordImage, 1.0f, juce::Colours::transparentBlack,
						  recordImage, 1.0f, juce::Colour(0x33000000),
						  recordImage, 1.0f, juce::Colour(0xffff0000));

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
		button->addListener(this);
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

const MixHeaderView::ButtonStates& MixHeaderView::getButtonStates()
{
	return lastState;
}

void MixHeaderView::buttonStateChanged(juce::Button* button)
{
	lastState = ButtonStates(backButton == button && button->getState() == juce::Button::buttonDown,
							  rewindButton == button && button->getState() == juce::Button::buttonDown,
							  isHoldingRewind && rewindButton == button && button->getState() != juce::Button::buttonDown,
							  playPauseButton == button && button->getState() == juce::Button::buttonDown && !isPaused,
							  playPauseButton == button && button->getState() == juce::Button::buttonDown && isPaused,
							  fastForwardButton == button && button->getState() == juce::Button::buttonDown,
							  isHoldingFastForward && fastForwardButton == button && button->getState() != juce::Button::buttonDown,
							  nextButton == button && button->getState() == juce::Button::buttonDown,
							  stopButton == button && button->getState() == juce::Button::buttonDown,
							  recordButton == button && button->getState() == juce::Button::buttonDown);

	if (lastState.rewindPressed || lastState.rewindReleased)
		isHoldingRewind = !isHoldingRewind;
	
	if (lastState.fastForwardPressed || lastState.fastForwardReleased)
		isHoldingFastForward = !isHoldingFastForward;

	notifyObservers();
}

void MixHeaderView::setTimeline(Timeline& timeline)
{
	timeline.addObserver(std::shared_ptr<TimerView>(&timerView));
}

void MixHeaderView::buttonClicked(juce::Button* button)
{
	buttonStateChanged(button);

	if (button == playPauseButton)
	{
		isPaused = !isPaused;
		setPlayPauseButtonImage(playPauseButton, isPaused);
	}
	else if (button == stopButton)
	{
		isPaused = false;
		setPlayPauseButtonImage(playPauseButton, isPaused);
	}
}

void MixHeaderView::setPlayPauseButtonImage(juce::ImageButton* button, bool isPaused)
{
	auto image = isPaused ? pauseImage : playImage;
	button->setImages(false, false, true,
						  image, 1.0f, juce::Colours::transparentBlack,
						  image, 1.0f, juce::Colour(0x33000000),
						  image, 1.0f, juce::Colour(0x55000000));
}
