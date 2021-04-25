#include "TrackControlsListView.h"

TrackControlsListView::TrackControlsListView()
{
    this->scrollYMin = 0;
    this->scrollYMax = 0;
    this->scrollYAmount = 0;

    getLookAndFeel().setColour(backgroundColourId, juce::Colour(defaultBackgroundColour));
    getLookAndFeel().setColour(borderColourId, juce::Colour(defaultBorderColour));
    addTrackView.addListener(this);
    addAndMakeVisible(addTrackView);
}

TrackControlsListView::~TrackControlsListView()
{
    for (auto *trackControls : children)
    {
        delete trackControls;
        trackControls = nullptr;
    }
}

void TrackControlsListView::paint(juce::Graphics& g)
{
    g.fillAll(getLookAndFeel().findColour(backgroundColourId));

    g.setColour(getLookAndFeel().findColour(borderColourId));
    g.drawLine(borderThickness / 2, 0, borderThickness / 2,  getHeight(), borderThickness);
}

void TrackControlsListView::resized()
{

    calculateScrollYMax();

    auto trackControlsBounds = getLocalBounds();
    trackControlsBounds.removeFromLeft(borderThickness);
    trackControlsBounds.translate(0, -scrollYAmount);

    for (auto *trackControls : children)
    {
        trackControlsBounds.setHeight(trackControls->getHeight());
        trackControls->setBounds(trackControlsBounds);

        trackControlsBounds.translate(0, trackControls->getHeight());
    }

    trackControlsBounds.setHeight(TrackControlsView::DEFAULT_HEIGHT);
    addTrackView.setBounds(trackControlsBounds);

	//TODO find other way to update parent when this is resized
    if (getParentComponent()) getParentComponent()->resized();
}

void TrackControlsListView::buttonClicked(juce::Button*)
{
    auto chooser = juce::FileChooser("Choose an audio file.",
                                     juce::File(),
                                     "*.wav;*.aif;*.mp3;*.ogg;*.flac");

    if (chooser.browseForMultipleFilesToOpen())
    {
        for (auto f : chooser.getResults())
        {
            loadedFiles.push_back(f);
        }

		notifyObservers();
    }
}

TrackControlsView* TrackControlsListView::appendNewTrackControls()
{
    auto *trackControls = new TrackControlsView();
    trackControls->setName("New Track");
    trackControls->setLookAndFeel(&getLookAndFeel());
    trackControls->setSize(getWidth() - borderThickness, TrackControlsView::DEFAULT_HEIGHT);
    children.push_back(trackControls);
    addAndMakeVisible(trackControls);

    calculateScrollYMax();
    resized();

    return trackControls;
}

TrackControlsView* TrackControlsListView::getTrackAt(int index)
{
    return children[index];
}

std::vector<juce::File> TrackControlsListView::getLoadedFiles()
{
    return loadedFiles;
}

// can't scroll X
void TrackControlsListView::scrollX(float deltaX)
{
    return;
}

void TrackControlsListView::scrollY(float deltaY)
{
    setScrollY(scrollYAmount + deltaY);
}

// can't scroll X
void TrackControlsListView::setScrollX(float x)
{
    return;
}

void TrackControlsListView::setScrollY(float y)
{
    scrollYAmount = y;
    if (scrollYAmount < scrollYMin) scrollYAmount = scrollYMin;
    if (scrollYAmount > scrollYMax) scrollYAmount = scrollYMax;
    resized();
}

float TrackControlsListView::getContentWidth()
{
    return getWidth();
}

float TrackControlsListView::getContentHeight()
{
    auto top = children.size() == 0 ? addTrackView.getY() : getTrackAt(0)->getY();
    return addTrackView.getBottom() - top;
}

void TrackControlsListView::calculateScrollYMax()
{
    scrollYMax = getContentHeight() - getHeight();
}
