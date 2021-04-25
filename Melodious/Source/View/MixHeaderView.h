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
		ButtonStates(bool back, bool rewind, bool play, bool pause,
					 bool fastForward, bool next, bool stop, bool record)
			: backPressed(back),
			rewindPressed(rewind),
			playPressed(play),
			pausePressed(pause),
			fastForwardPressed(fastForward),
			nextPressed(next),
			stopPressed(stop),
			recordPressed(record)
		{}
		
		bool backPressed;
		bool rewindPressed;
		bool playPressed;
		bool pausePressed;
		bool fastForwardPressed;
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
	void buttonClicked(juce::Button*) override;
private:
	int borderThickness = 4;
	int padding = 20;

	juce::TextButton* backButton;
	juce::TextButton* rewindButton;
	juce::TextButton* playPauseButton;
	juce::TextButton* fastForwardButton;
	juce::TextButton* nextButton;
	juce::TextButton* stopButton;
	juce::TextButton* recordButton;
	std::vector<juce::Button*> buttons;
	juce::DrawableRectangle buttonsBackground;

	TimerView timerView;
	ButtonLookAndFeel *buttonLookAndFeel;
	ButtonStates lastState;
	bool isPauseToggled = false;
};
