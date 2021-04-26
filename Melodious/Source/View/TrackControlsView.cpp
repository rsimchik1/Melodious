#include "TrackControlsView.h"

TrackControlsView::TrackControlsView()
{
    setColour(backgroundColourId, juce::Colour(defaultBackgroundColour));
    setColour(borderColourId, juce::Colour(defaultBorderColour));

    font = juce::Font(juce::Typeface::createSystemTypefaceFor(
        BinaryData::AlataRegular_ttf,
        BinaryData::AlataRegular_ttfSize));
    font.setHeight(controlsSize);
	
    volumeLookAndFeel = new VolumeLookAndFeel();
    volumeSlider.setRange(-96, 10);
    volumeSlider.setValue(0);
    volumeSlider.setLookAndFeel(volumeLookAndFeel);
    volumeSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    volumeSlider.addListener(this);
    volumeSlider.setPopupDisplayEnabled(true, true, this);
    volumeSlider.setNumDecimalPlacesToDisplay(0);
    volumeSlider.snapValue(0.0, juce::Slider::DragMode::absoluteDrag);
    addAndMakeVisible(volumeSlider);

    panLookAndFeel = new PanLookAndFeel();
    panSlider.setRange(-1, 1);
    panSlider.setValue(0);
    panSlider.setLookAndFeel(panLookAndFeel);
    panSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    panSlider.addListener(this);
    panSlider.snapValue(0.0, juce::Slider::DragMode::absoluteDrag);
    addAndMakeVisible(panSlider);

    title.setFont(font);
    title.setText(getName(), juce::NotificationType::dontSendNotification);
    title.setEditable(false, true, true);
    title.addListener(this);
    addAndMakeVisible(title);

    buttonLookAndFeel = new ButtonLookAndFeel();
    buttonLookAndFeel->setColour(juce::ComboBox::outlineColourId, findColour(borderColourId));
    buttonLookAndFeel->setColour(juce::TextButton::buttonColourId, findColour(backgroundColourId).darker());
    buttonLookAndFeel->setColour(juce::TextButton::textColourOffId, juce::Colours::white);

    muteButton.setButtonText("M");
    muteButton.setLookAndFeel(buttonLookAndFeel);
    muteButton.setClickingTogglesState(true);
    addAndMakeVisible(muteButton);

    soloButton.setButtonText("S");
    soloButton.setLookAndFeel(buttonLookAndFeel);
    soloButton.setClickingTogglesState(true);
    addAndMakeVisible(soloButton);

    monitorButton.setButtonText("<");
    monitorButton.setLookAndFeel(buttonLookAndFeel);
    monitorButton.setClickingTogglesState(true);
    addAndMakeVisible(monitorButton);

    recordButton.setButtonText("O");
    recordButton.setLookAndFeel(buttonLookAndFeel);
    recordButton.setClickingTogglesState(true);
    addAndMakeVisible(recordButton);
}

TrackControlsView::~TrackControlsView()
{
    volumeSlider.setLookAndFeel(nullptr);
    delete volumeLookAndFeel;
    volumeLookAndFeel = nullptr;

    panSlider.setLookAndFeel(nullptr);
    delete panLookAndFeel;
    panLookAndFeel = nullptr;

    muteButton.setLookAndFeel(nullptr);
    soloButton.setLookAndFeel(nullptr);
    monitorButton.setLookAndFeel(nullptr);
    recordButton.setLookAndFeel(nullptr);
    delete buttonLookAndFeel;
    buttonLookAndFeel = nullptr;
}

void TrackControlsView::paint(juce::Graphics& g)
{
    g.fillAll (findColour(backgroundColourId));
    
    g.setColour(findColour(borderColourId));
    g.drawHorizontalLine(getHeight() - 1, 0, getWidth());
}

void TrackControlsView::resized()
{
    auto paddedBounds = getLocalBounds();
    paddedBounds.removeFromRight(paddingPixels);
    paddedBounds.removeFromLeft(paddingPixels);
    paddedBounds.removeFromTop(paddingPixels);
    paddedBounds.removeFromBottom(paddingPixels);

    auto volumeBounds = paddedBounds;
    volumeBounds.removeFromLeft(controlsSize);
    volumeBounds.removeFromRight(paddingPixels*2 + controlsSize*2);
    volumeBounds.removeFromTop(paddedBounds.getHeight() / 2 - controlsSize / 2);
    volumeBounds.removeFromBottom(paddedBounds.getHeight() / 2 - controlsSize / 2);
    volumeSlider.setBounds(volumeBounds);

    auto panBounds = volumeBounds;
    panBounds.setY(paddedBounds.getY() + paddedBounds.getHeight() - controlsSize);
    panSlider.setBounds(panBounds);

    auto titleBounds = paddedBounds;
    titleBounds.removeFromBottom(paddedBounds.getHeight() - controlsSize);
    titleBounds.removeFromRight(controlsSize);
    font.setHeight(titleBounds.getHeight());
    title.setFont(font);
    title.setBounds(titleBounds);

    juce::Rectangle<int> soloButtonBounds;
    soloButtonBounds.setWidth(controlsSize);
    soloButtonBounds.setHeight(controlsSize);
    soloButtonBounds.setX(getWidth() - paddingPixels - controlsSize);
    soloButtonBounds.setY(volumeBounds.getY());
    soloButton.setBounds(soloButtonBounds);

    auto muteButtonBounds = soloButtonBounds;
    muteButtonBounds.translate(-controlsSize, 0);
    muteButton.setBounds(muteButtonBounds);

    auto recordButtonBounds = muteButtonBounds;
    recordButtonBounds.setY(panBounds.getY());
    recordButton.setBounds(recordButtonBounds);

    auto monitorButtonBounds = soloButtonBounds;
    monitorButtonBounds.setY(panBounds.getY());
    monitorButton.setBounds(monitorButtonBounds);
}

void TrackControlsView::setName(const juce::String& newName)
{
    juce::Component::setName(newName);
    title.setText(newName, juce::NotificationType::dontSendNotification);
}

void TrackControlsView::labelTextChanged(juce::Label* labelThatHasChanged)
{
    juce::Component::setName(labelThatHasChanged->getText());
}

void TrackControlsView::sliderValueChanged(juce::Slider* slider)
{
    notifyObservers();
}

float TrackControlsView::getVolume()
{
    return juce::Decibels::decibelsToGain(volumeSlider.getValue(), -96.0);
}

float TrackControlsView::getPan()
{
    return panSlider.getValue();
}

// Custom volume slider
TrackControlsView::VolumeLookAndFeel::VolumeLookAndFeel()
{
    setColour(juce::Slider::backgroundColourId, juce::Colour(defaultBackgroundColour));
    setColour(juce::Slider::thumbColourId, juce::Colour(defaultThumbColour));
    setColour(gradientColourId, juce::Colour(defaultGradientColour));
}

void TrackControlsView::VolumeLookAndFeel::drawLinearSliderThumb(juce::Graphics& g, int x, int y, int width, int height,
	float sliderPos, float minSliderPos, float maxSliderPos, const juce::Slider::SliderStyle, juce::Slider&)
{
    auto thumbBounds = getAdjustedThumbBounds(x, y, width, height, sliderPos, minSliderPos, maxSliderPos);

    g.setColour(findColour(juce::Slider::thumbColourId));
    g.fillEllipse(thumbBounds);
}

void TrackControlsView::VolumeLookAndFeel::drawLinearSliderBackground(juce::Graphics& g, int x, int y, int width,
	int height, float sliderPos, float minSliderPos, float maxSliderPos, const juce::Slider::SliderStyle, juce::Slider&)
{
    g.setColour(findColour(juce::Slider::backgroundColourId));
    g.fillRoundedRectangle(x, y, width, height, height/2);

    auto thumbBounds = getAdjustedThumbBounds(x, y, width, height, sliderPos, minSliderPos, maxSliderPos);
    auto sliderGradient = juce::ColourGradient(findColour(juce::Slider::backgroundColourId),
        x, y, findColour(gradientColourId), thumbBounds.getX(), height, false);
    g.setGradientFill(sliderGradient);
    g.fillRoundedRectangle(minSliderPos + innerPaddingPixels, thumbBounds.getY(),
        thumbBounds.getX(), thumbBounds.getHeight(), thumbBounds.getHeight()/2);
}

void TrackControlsView::VolumeLookAndFeel::drawLinearSlider(juce::Graphics& g, int x, int y, int width, int height,
	float sliderPos, float minSliderPos, float maxSliderPos, const juce::Slider::SliderStyle style, juce::Slider& slider)
{
    y += outerPaddingPixels;
    height -= outerPaddingPixels * 2;
    minSliderPos = x;
    maxSliderPos = width + x;
    drawLinearSliderBackground(g, x, y, width, height, sliderPos, minSliderPos, 
        maxSliderPos, style, slider);
    drawLinearSliderThumb(g, x, y, width, height, sliderPos, minSliderPos, 
        maxSliderPos, style, slider);
}

juce::Rectangle<float> TrackControlsView::VolumeLookAndFeel::getAdjustedThumbBounds(int x, int y, int width,
    int height, float sliderPos, float minSliderPos, float maxSliderPos)
{
    auto radius = height / 2.0f;
    auto adjustedMax = maxSliderPos - (radius * 2.0f);
    auto sliderRange = adjustedMax - minSliderPos;
    auto scaledX = sliderPos * sliderRange / width;
    auto thumbX = innerPaddingPixels + scaledX + 2; //TODO figure out why the above calculation is off by -2
    auto thumbY = y + innerPaddingPixels;
    auto thumbH = radius * 2.0f - innerPaddingPixels * 2.0f;
    auto thumbW = thumbH;

    return juce::Rectangle<float>(thumbX, thumbY, thumbW, thumbH);
}

// Custom pan slider
TrackControlsView::PanLookAndFeel::PanLookAndFeel()
{
    setColour(juce::Slider::backgroundColourId, juce::Colour(defaultBackgroundColour));
    setColour(juce::Slider::thumbColourId, juce::Colour(defaultThumbColour));

    font = juce::Font(juce::Typeface::createSystemTypefaceFor(
        BinaryData::AlataRegular_ttf,
        BinaryData::AlataRegular_ttfSize));
}

void TrackControlsView::PanLookAndFeel::drawLinearSliderThumb(juce::Graphics& g, int x, int y, int width, int height,
	float sliderPos, float minSliderPos, float maxSliderPos, const juce::Slider::SliderStyle style, juce::Slider& slider)
{
    auto rectX = sliderPos - thumbThickness / 2;
    auto rectW = thumbThickness;
    auto rectH = rectW * 1.5;
    auto rectY = y + height / 2 - rectH / 2;

    g.setColour(findColour(juce::Slider::thumbColourId));
    g.fillRoundedRectangle(rectX, rectY, rectW, rectH, thumbThickness);
}

void TrackControlsView::PanLookAndFeel::drawLinearSliderBackground(juce::Graphics& g, int x, int y, int width, int height,
	float sliderPos, float minSliderPos, float maxSliderPos, const juce::Slider::SliderStyle style, juce::Slider& slider)
{
    int centerLine = y + height / 2;
    int rectY = centerLine - trackThickness / 2;
    int rectH = trackThickness;

    g.setColour(findColour(juce::Slider::backgroundColourId));
    g.fillRect(x, rectY, width, rectH);

    auto fontY = centerLine + trackThickness / 2;
    font.setHeight(fontSize);
    g.setFont(font);
    g.drawText("L", x - fontSize/2, fontY, fontSize, fontSize, juce::Justification::left);
    g.drawText("R", x + width - fontSize/2, fontY, fontSize, fontSize, juce::Justification::right);
    g.drawText("|", x + width / 2 - fontSize / 2, fontY, fontSize, fontSize, juce::Justification::centred);
}

void TrackControlsView::PanLookAndFeel::drawLinearSlider(juce::Graphics& g, int x, int y, int width, int height,
	float sliderPos, float minSliderPos, float maxSliderPos, const juce::Slider::SliderStyle style, juce::Slider& slider)
{
    y -= trackThickness;
    drawLinearSliderBackground(g, x, y, width, height, sliderPos, minSliderPos, 
        maxSliderPos, style, slider);
    drawLinearSliderThumb(g, x, y, width, height, sliderPos, minSliderPos, 
        maxSliderPos, style, slider);
}
