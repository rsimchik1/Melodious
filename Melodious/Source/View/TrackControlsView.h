#pragma once

#include "ButtonLookAndFeel.h"
#include "JuceHeader.h"

class TrackControlsView : public juce::Component, juce::Label::Listener
{
public:
    enum ColourIds
    {
        backgroundColourId = 0x20000011,
    	borderColourId = 0x20000012,
    	buttonColourId = 0x20000013,
    	buttonBorderColourId = 0x20000014
    };

	enum DefaultColours
	{
		defaultBackgroundColour = 0xff030b47,
		defaultBorderColour = 0xff737795,
		defaultButtonColour = 0xff,
		defaultButtonBorderColour = 0xff
	};

	static const int DEFAULT_HEIGHT = 120;

	TrackControlsView();
	~TrackControlsView() override;

	void paint(juce::Graphics& g) override;
	void resized() override;
    void setName(const juce::String& newName) override;
    void labelTextChanged(juce::Label* labelThatHasChanged) override;
private:
    class VolumeLookAndFeel;
    class PanLookAndFeel;

    juce::Slider volumeSlider;
    juce::Slider panSlider;
    juce::Label title;
    juce::TextButton muteButton;
    juce::TextButton soloButton;
    juce::TextButton recordButton;
    juce::TextButton monitorButton;

    ButtonLookAndFeel* buttonLookAndFeel;
    VolumeLookAndFeel *volumeLookAndFeel;
    PanLookAndFeel* panLookAndFeel;

    int paddingPixels = 10;
    float controlsSize = 25;
}; 

class TrackControlsView::VolumeLookAndFeel : public juce::LookAndFeel_V4
{
public:
    enum ColourIds
    {
        gradientColourId = 0x20000f13
    };

    enum DefaultColours
    {
	    defaultBackgroundColour = 0xffffffff,
    	defaultThumbColour = 0xff4443eb,
		defaultGradientColour = 0xff06d2ff
    };

    int innerPaddingPixels = 2;
    int outerPaddingPixels = 3;

    VolumeLookAndFeel();
	void drawLinearSliderThumb(juce::Graphics&, int x, int y, int width, int height, float sliderPos,
		float minSliderPos, float maxSliderPos, const juce::Slider::SliderStyle, juce::Slider&) override;
	void drawLinearSliderBackground(juce::Graphics&, int x, int y, int width, int height, float sliderPos,
		float minSliderPos, float maxSliderPos, const juce::Slider::SliderStyle, juce::Slider&) override;
	void drawLinearSlider(juce::Graphics&, int x, int y, int width, int height, float sliderPos, float minSliderPos,
		float maxSliderPos, const juce::Slider::SliderStyle, juce::Slider&) override;
    juce::Rectangle<float> getAdjustedThumbBounds(int x, int y, int width, int height, float sliderPos,
        float minSliderPos, float maxSliderPos);
};

class TrackControlsView::PanLookAndFeel : public juce::LookAndFeel_V4
{
public:
	enum DefaultColours
    {
        defaultBackgroundColour = 0xffffffff,
        defaultThumbColour = 0xff06d2ff,
    };

    int trackThickness = 6;
    int thumbThickness = 10;
    int fontSize = 15;

    PanLookAndFeel();

	void drawLinearSliderThumb(juce::Graphics&, int x, int y, int width, int height, float sliderPos,
		float minSliderPos, float maxSliderPos, const juce::Slider::SliderStyle, juce::Slider&) override;
	void drawLinearSliderBackground(juce::Graphics&, int x, int y, int width, int height, float sliderPos,
		float minSliderPos, float maxSliderPos, const juce::Slider::SliderStyle, juce::Slider&) override;
	void drawLinearSlider(juce::Graphics&, int x, int y, int width, int height, float sliderPos, float minSliderPos,
		float maxSliderPos, const juce::Slider::SliderStyle, juce::Slider&) override;

};
