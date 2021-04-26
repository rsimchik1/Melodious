#pragma once

#include "ButtonLookAndFeel.h"
#include "JuceHeader.h"
#include "TimerView.h"
#include "../Controller/Observable.h"

class MixHeaderView : public juce::Component,
                      public juce::Button::Listener,
                      public Observable<MixHeaderView>
{
public:
	struct ButtonStates
	{
		ButtonStates(bool back, bool rewindOn, bool rewindOff, bool play, 
					 bool pause, bool fastForwardOn, bool fastForwardOff, 
					 bool next, bool stop, bool record)
			: backPressed(back),
			rewindPressed(rewindOn),
			rewindReleased(rewindOff),
			playPressed(play),
			pausePressed(pause),
			fastForwardPressed(fastForwardOn),
			fastForwardReleased(fastForwardOff),
			nextPressed(next),
			stopPressed(stop),
			recordPressed(record)
		{}
		
		bool backPressed;
		bool rewindPressed;
		bool rewindReleased;
		bool playPressed;
		bool pausePressed;
		bool fastForwardPressed;
		bool fastForwardReleased;
		bool nextPressed;
		bool stopPressed;
		bool recordPressed;
	};

	enum ColourIds
	{
		backgroundColourId = 0x20000051,
		borderColourId = 0x20000052
	};

	enum DefaultColours
	{
		defaultBackgroundColour = 0xff131b5d,
		defaultBorderColour = 0xffffffff
	};

	MixHeaderView();
	~MixHeaderView();
	void paint(juce::Graphics& g) override;
	void resized() override;

	const ButtonStates& getButtonStates();
	void buttonStateChanged(juce::Button*) override;
	void setTimeline(Timeline& timeline);
private:
	int borderThickness = 4;
	int padding = 20;

	juce::Image backImage;
	juce::Image rewindImage;
	juce::Image playImage;
	juce::Image pauseImage;
	juce::Image fastForwardImage;
	juce::Image nextImage;
	juce::Image stopImage;
	juce::Image recordImage;
	
	juce::ImageButton* backButton;
	juce::ImageButton* rewindButton;
	juce::ImageButton* playPauseButton;
	juce::ImageButton* fastForwardButton;
	juce::ImageButton* nextButton;
	juce::ImageButton* stopButton;
	juce::ImageButton* recordButton;
	std::vector<juce::Button*> buttons;
	juce::DrawableRectangle buttonsBackground;

	TimerView timerView;
	ButtonLookAndFeel *buttonLookAndFeel;
	ButtonStates lastState;
	bool isPaused = false;
	bool isHoldingRewind = false;
	bool isHoldingFastForward = false;

	void buttonClicked(juce::Button*) override;
	void setPlayPauseButtonImage(juce::ImageButton *button, bool isPaused);
};
