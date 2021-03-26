#include "ArrangeView.h"

ArrangeView::ArrangeView()
{
    beatSpacing = 35;
    trackSpacing = 115;
    trackPadding = 5;
    sample = 0;
    sampleRate = 1;

    setFramesPerSecond(60);
}

void ArrangeView::update()
{
}

void ArrangeView::paint(juce::Graphics& g)
{
    beatSpacing += 0.05;
    g.fillAll(juce::Colour(0xff030b47));
    
    g.setColour(juce::Colour(0xff737795));
    for (auto x = 0; x < getWidth() / beatSpacing; x++)
        g.drawVerticalLine(x * beatSpacing, 0, getHeight());

    auto numTracks = 3;
    for (auto y = 0; y < numTracks; y++)
        g.drawHorizontalLine((y+1)*trackSpacing, 0, getWidth());

    g.setColour(juce::Colour(0xff2ec8c8));
    g.fillRoundedRectangle(beatSpacing * starts[0], trackPadding, beatSpacing * ends[0] - beatSpacing * starts[0], trackSpacing - trackPadding * 2, 15);
    g.fillRoundedRectangle(beatSpacing * starts[3], trackPadding, beatSpacing * ends[3] - beatSpacing * starts[3], trackSpacing - trackPadding * 2, 15);
    g.setColour(juce::Colour(0xff7e6cef));
    g.fillRoundedRectangle(beatSpacing * starts[1], trackSpacing + trackPadding, beatSpacing * ends[1] - beatSpacing * starts[1], trackSpacing - trackPadding * 2, 15);
    g.setColour(juce::Colour(0xfffc09e4));
    g.fillRoundedRectangle(beatSpacing * starts[2], trackSpacing * 2 + trackPadding, beatSpacing * ends[2] - beatSpacing * starts[2], trackSpacing - trackPadding * 2, 15);

    float playPos = sample * beatSpacing / sampleRate;
    g.setColour(juce::Colours::white);
    g.drawLine(playPos, 0, playPos, getHeight(), 2);
}

void ArrangeView::setTime(int32_t sample)
{
    this->sample = sample;
}

void ArrangeView::setSampleRate(int sampleRate)
{
    this->sampleRate = sampleRate;
}
