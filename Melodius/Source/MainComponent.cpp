#include "MainComponent.h"

#include "LeafChannel.h"
#include "OscClip.h"
#include "OscClipReader.h"

//==============================================================================
MainComponent::MainComponent()
{
    // Make sure you set the size of the component after
    // you add any child components.
    setSize (800, 600);

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

    DBG("Hello, World!");

    mixer.createAudioChannel();
    mixer.createAudioChannel();
    mixer.createAudioChannel();
    mixer.createBusChannel();
    mixer.connectChannels(0, 3);
    mixer.connectChannels(1, 3);
    mixer.connectChannels(2, 3);

    auto reader1 = new OscClipReader();
    auto reader2 = new OscClipReader();
    auto reader3 = new OscClipReader();
    auto track1 = new Track<OscClip>(reader1);
    auto track2 = new Track<OscClip>(reader2);
    auto track3 = new Track<OscClip>(reader3);
    
    const float baseFreq = 260.0;
    auto *clip1 = new OscClip(baseFreq, 0.25);
    auto *clip2 = new OscClip(baseFreq * 3.0/2, 0.25);
    auto *clip3 = new OscClip(baseFreq * 5.0/4, 0.25);
    auto *clip4 = new OscClip(baseFreq * 2, 0.25);
    clip1->setStartEndFrames(0, sampleRate * 2);
    clip2->setStartEndFrames(sampleRate * 1, sampleRate * 8);
    clip3->setStartEndFrames(sampleRate * 2, sampleRate * 10);
    clip4->setStartEndFrames(sampleRate * 2, sampleRate * 12);

    track1->insertClip(clip1);
    track2->insertClip(clip2);
    track3->insertClip(clip3);
    track1->insertClip(clip4);

    dynamic_cast<LeafChannel *>(mixer.getChannelAt(0))->setAudioSource(track1);
    dynamic_cast<LeafChannel *>(mixer.getChannelAt(1))->setAudioSource(track2);
    dynamic_cast<LeafChannel *>(mixer.getChannelAt(2))->setAudioSource(track3);
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
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    // You can add your drawing code here!
}

void MainComponent::resized()
{
    // This is called when the MainContentComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
}
