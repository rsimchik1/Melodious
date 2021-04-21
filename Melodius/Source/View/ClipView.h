#pragma once

#include "JuceHeader.h"

class ClipView : public juce::Component, public juce::MouseListener
{
public:
	ClipView();
	~ClipView() override;

	void paint(juce::Graphics& g) override;
	void resized() override;
	void mouseDown(const juce::MouseEvent& event) override;
	void mouseDrag(const juce::MouseEvent& event) override;

	// x position without scroll or zoom modifications
	float getTrueX();
	void setTrueX(float trueX);
private:
	float x;
	int trackIndex;
	
	juce::AudioThumbnail *waveformDisplay;
	juce::ResizableBorderComponent* resizable;
	juce::ComponentBoundsConstrainer* borderConstrainer;
	juce::ComponentDragger draggable;
};
