#include "MainComponent.h"

MainComponent::MainComponent()
    : currentState(TransportController::Stopped),
	transportController(&currentState),
    fileManager(std::make_shared<FileManager>()),
    trackListController(std::make_shared<TrackListController>(&mixer, &arrangementView, fileManager)),
	arrangementView(trackListController)
{
    if (juce::RuntimePermissions::isRequired (juce::RuntimePermissions::recordAudio)
        && ! juce::RuntimePermissions::isGranted (juce::RuntimePermissions::recordAudio))
    {
        juce::RuntimePermissions::request (juce::RuntimePermissions::recordAudio,
                                           [&] (bool granted) { setAudioChannels (granted ? 2 : 0, 2); });
    }
    else
    {
        setAudioChannels (2, 2);
    }

    mixHeaderView.addObserver(std::shared_ptr<TransportController>(&transportController));

    addAndMakeVisible(arrangementView);
    addAndMakeVisible(mixHeaderView);
    addAndMakeVisible(footerView);

    setSize (800, 600);
}

MainComponent::~MainComponent()
{
    shutdownAudio();
}

//==============================================================================
void MainComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    this->sampleRate = sampleRate;
    timeline = Timeline(sampleRate);
    arrangementView.setSampleRate(sampleRate);
    trackListController->setSampleRate(sampleRate);
    mixHeaderView.setTimeline(timeline);
    renderController = std::make_shared<RenderController>(std::shared_ptr<Timeline>(&timeline),
                                                          std::shared_ptr<ChannelMixer>(&mixer),
                                                          fileManager);
    footerView.addObserver(renderController);
}

void MainComponent::getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill)
{
    auto numFrames = bufferToFill.numSamples;
    auto numChannels = bufferToFill.buffer->getNumChannels();
    AudioBuffer buffer(numFrames, numChannels);
    switch(currentState)
    {
        case TransportController::Playing:
			buffer = mixer.processFrames(numFrames, timeline);
            timeline.shiftPlaybackHead(numFrames);
            break;
        case TransportController::StartPlay:
            currentState = TransportController::Playing;
            getNextAudioBlock(bufferToFill);
            break;
        case TransportController::Stopping:
            timeline.movePlaybackHead(0);
            currentState = TransportController::Stopped;
            break;
        case TransportController::Stopped:
            break;
        case TransportController::Pausing:
            currentState = TransportController::Stopped;
            break;
        case TransportController::Rewinding:
        {
            auto offset = numFrames * scrubSpeed;
            if (timeline.getPlaybackHead() < offset)
                offset = timeline.getPlaybackHead();
            timeline.shiftPlaybackHead(-offset);
        }
            break;
        case TransportController::FastForwarding:
            timeline.shiftPlaybackHead(numFrames * scrubSpeed);
            break;
        case TransportController::GoingBack:
        {
            timeline.movePlaybackHead(0);
            currentState = lastState;
            getNextAudioBlock(bufferToFill);
        }
        break;
        case TransportController::StartRecord:
            currentState = TransportController::Playing;    // TODO change this when implementing recording
            getNextAudioBlock(bufferToFill);
            break;
    }
    lastState = currentState;

	for (int sample = 0; sample < numFrames; sample++)
	{
		for (int channel = 0; channel < numChannels; channel++)
		{
            bufferToFill.buffer->setSample(channel, sample,
                buffer.readSampleAt(sample, channel));
		}
	}
    arrangementView.setPlayheadSample(timeline.getPlaybackHead());
}

void MainComponent::releaseResources()
{
}

void MainComponent::paint (juce::Graphics& g)
{
}

void MainComponent::resized()
{
    auto headerBounds = getLocalBounds();
    headerBounds.setHeight(100);
    mixHeaderView.setBounds(headerBounds);

    auto footerBounds = getLocalBounds();
    footerBounds.removeFromTop(getHeight() - 75);
    footerView.setBounds(footerBounds);

    auto arrangementBounds = getLocalBounds();
    arrangementBounds.removeFromTop(headerBounds.getHeight());
    arrangementBounds.removeFromBottom(footerBounds.getHeight());
    arrangementView.setBounds(arrangementBounds);
}
