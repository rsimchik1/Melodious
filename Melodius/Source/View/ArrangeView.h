#pragma once

#include "JuceHeader.h"
#include "TrackView.h"

class ArrangeView : public juce::AnimatedAppComponent,
					public juce::MouseListener
{
public:
	static const int BACKGROUND_COLOR = 1;
	static const int BORDER_LIGHT_COLOR = 2;
	static const int BORDER_HEAVY_COLOR = 3;
	static const int PLAYHEAD_COLOR = 4;
	static const int TEXT_COLOR = 5;

	ArrangeView();
	~ArrangeView();
	void update() override;
	void paint(juce::Graphics& g) override;
	void setTime(int32_t sample);
	void setSampleRate(int sampleRate);
	void addTrack(TrackView *toAdd);
	void resized() override;
private:
	float pixelsPerSecond;
	float trackHeight;
	float trackPadding;
	float trackControlsWidth;
	uint32_t playbackHead;
	int sampleRate;
	float scrollX;
	float scrollSensitivity = 20;
	float zoomSensitivity = 10;

	std::vector<TrackView *> trackViews;

	void setTrackBounds(int trackIndex);
	void scrollXOffset(float offset);
	void zoomX(float zoomAmount);
public:
	void mouseWheelMove(const juce::MouseEvent& event, const juce::MouseWheelDetails& wheel) override;
};
