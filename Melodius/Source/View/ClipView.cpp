#include "ClipView.h"

ClipView::ClipView()
{
	waveformDisplay = nullptr;
	borderConstrainer = new juce::ComponentBoundsConstrainer();
	borderConstrainer->setMinimumWidth(2);
	resizable = new juce::ResizableBorderComponent(this, borderConstrainer);
	resizable->setBorderThickness(juce::BorderSize<int>(0, 5, 0, 5));
	addAndMakeVisible(resizable);
}

ClipView::~ClipView()
{
	if (waveformDisplay) delete waveformDisplay;
	waveformDisplay = nullptr;

	delete resizable;
	resizable = nullptr;

	delete borderConstrainer;
	borderConstrainer = nullptr;
}

void ClipView::paint(juce::Graphics& g)
{
	g.setColour(juce::Colours::darkred);
	g.fillRect(getLocalBounds());
	g.setColour(juce::Colours::black);
	g.drawRect(getLocalBounds());
	g.setColour(juce::Colours::black);
	g.drawFittedText("FILE NOT FOUND", getLocalBounds(), juce::Justification::centred, 1, 1);
}

void ClipView::resized()
{
	borderConstrainer->setMaximumHeight(getHeight());
	borderConstrainer->setMinimumHeight(getHeight());
	resizable->setBounds(getLocalBounds());
}

void ClipView::mouseDown(const juce::MouseEvent& event)
{
	draggable.startDraggingComponent(this, event);
}

void ClipView::mouseDrag(const juce::MouseEvent& event)
{
	draggable.dragComponent(this, event, nullptr);
}

float ClipView::getTrueX()
{
	return x;
}

void ClipView::setTrueX(float trueX)
{
	x = trueX;
}
