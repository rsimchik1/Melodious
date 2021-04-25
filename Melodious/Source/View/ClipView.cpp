#include "ClipView.h"

ClipView::ClipView()
	: waveformCache(nullptr),
	waveformDisplay(nullptr),
	borderConstrainer(new juce::ComponentBoundsConstrainer()),
	resizable(new juce::ResizableBorderComponent(this, borderConstrainer))
{
	borderConstrainer->setMinimumWidth(2);
	resizable->setBorderThickness(juce::BorderSize<int>(0, 5, 0, 5));
	addAndMakeVisible(resizable);
}

ClipView::~ClipView()
{
	if (waveformDisplay) delete waveformDisplay;
	waveformDisplay = nullptr;

	if (waveformCache) delete waveformCache;
	waveformCache = nullptr;

	delete resizable;
	resizable = nullptr;

	delete borderConstrainer;
	borderConstrainer = nullptr;
}

void ClipView::paint(juce::Graphics& g)
{
	if (!waveformDisplay || waveformDisplay->getNumChannels() == 0)
		paintNoFileLoaded(g);
	else
		paintFileLoaded(g);
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

void ClipView::setStartEndSample(uint64_t startSample, uint64_t endSample)
{
	this->startSample = startSample;
	this->endSample = endSample;

	notifyObservers();
}

uint64_t ClipView::getLengthInSamples()
{
	return endSample - startSample;
}

void ClipView::setSampleRate(double sampleRate)
{
	this->sampleRate = sampleRate;
}

void ClipView::setAudioThumbnail(juce::AudioThumbnail* audioThumbnail,
                                 juce::AudioThumbnailCache* thumbnailCache)
{
	this->waveformDisplay = audioThumbnail;
	this->waveformCache = thumbnailCache;
}

float ClipView::getTrueX()
{
	return x;
}

void ClipView::setTrueX(float trueX)
{
	x = trueX;
}

void ClipView::paintNoFileLoaded(juce::Graphics& g)
{
	g.setColour(juce::Colours::grey);
	g.fillRect(getLocalBounds());
	g.setColour(juce::Colours::red);
	g.drawRect(getLocalBounds());
	g.setColour(juce::Colours::red);
	g.drawFittedText("FILE NOT FOUND", getLocalBounds(), juce::Justification::centred, 1, 1);
}

void ClipView::paintFileLoaded(juce::Graphics& g)
{
	g.setColour(juce::Colours::pink);
	g.fillRect(getLocalBounds());
	g.setColour(juce::Colours::darkred);
	g.drawRect(getLocalBounds());
	waveformDisplay->drawChannels(g, getLocalBounds(), startSample / sampleRate,
								  endSample / sampleRate, 1);
}
