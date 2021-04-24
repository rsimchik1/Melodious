#include "MainComponent.h"

#include "../Model/LeafChannel.h"
#include "../Model/OscClip.h"
#include "../Model/OscClipReader.h"


const float starts[4] = { 0, 1, 2, 2.5 };
const float ends[4] = { 2, 8, 10, 12 };
//==============================================================================
MainComponent::MainComponent()
{
    // Make sure you set the size of the component after
    // you add any child components.

    // Some platforms require permissions to open input channels so request that here
    if (juce::RuntimePermissions::isRequired (juce::RuntimePermissions::recordAudio)
        && ! juce::RuntimePermissions::isGranted (juce::RuntimePermissions::recordAudio))
    {
        juce::RuntimePermissions::request (juce::RuntimePermissions::recordAudio,
                                           [&] (bool granted) { setAudioChannels (granted ? 2 : 0, 2); });
    }
    else
    {
        // Specify the number of input and output channels that we want to open
        setAudioChannels (2, 2);
    }

    addAndMakeVisible(arrangementView);
    addAndMakeVisible(mixHeaderView);

    setSize (800, 600);
}

MainComponent::~MainComponent()
{
    // This shuts down the audio device and clears the audio source.
    shutdownAudio();
}

//==============================================================================
void MainComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    // This function will be called when the audio device is started, or when
    // its settings (i.e. sample rate, block size, etc) are changed.

    // You can use this function to initialise any resources you might need,
    // but be careful - it will be called on the audio thread, not the GUI thread.

    // For more details, see the help for AudioProcessor::prepareToPlay()

    this->sampleRate = sampleRate;
    timeline = Timeline(sampleRate);
}

void MainComponent::getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill)
{
    // Your audio-processing code goes here!
    auto buffer = mixer.processFrames(bufferToFill.numSamples, timeline);
	for (int sample = 0; sample < bufferToFill.numSamples; sample++)
	{
		for (int channel = 0; channel < bufferToFill.buffer->getNumChannels(); channel++)
		{
            bufferToFill.buffer->setSample(channel, sample,
                buffer.readSampleAt(sample, channel));
		}
	}
    timeline.shiftPlaybackHead(bufferToFill.numSamples);
}

void MainComponent::releaseResources()
{
    // This will be called when the audio device stops, or when it is being
    // restarted due to a setting change.

    // For more details, see the help for AudioProcessor::releaseResources()
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
}

void MainComponent::resized()
{
    auto headerBounds = getLocalBounds();
    headerBounds.setHeight(100);
    mixHeaderView.setBounds(headerBounds);

    auto arrangementBounds = getLocalBounds();
    arrangementBounds.removeFromTop(headerBounds.getHeight());
    arrangementView.setBounds(arrangementBounds);
}
