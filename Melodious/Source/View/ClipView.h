#pragma once

#include "JuceHeader.h"
#include "../Controller/Observable.h"

class ClipView : public juce::Component, public juce::MouseListener,
                 public Observable<ClipView>
{
public:
	ClipView();
	~ClipView() override;

	void paint(juce::Graphics& g) override;
	void resized() override;
	void mouseDown(const juce::MouseEvent& event) override;
	void mouseDrag(const juce::MouseEvent& event) override;

	void setStartEndSample(uint64_t startSample, uint64_t endSample);
	uint64_t getLengthInSamples();
	void setSampleRate(double sampleRate);
	void setAudioThumbnail(juce::AudioThumbnail* audioThumbnail, juce::AudioThumbnailCache* thumbnailCache);

	// x position without scroll or zoom modifications
	float getTrueX();
	void setTrueX(float trueX);
private:
	float x;
	double sampleRate;
	uint64_t startSample;
	uint64_t endSample;
	uint64_t displayStartSample;
	uint64_t displayEndSample;
	
	juce::AudioThumbnailCache* waveformCache;
	juce::AudioThumbnail *waveformDisplay;
	juce::ComponentBoundsConstrainer* borderConstrainer;
	juce::ResizableBorderComponent* resizable;
	juce::ComponentDragger draggable;

	void paintNoFileLoaded(juce::Graphics& g);
	void paintFileLoaded(juce::Graphics& g);
};
