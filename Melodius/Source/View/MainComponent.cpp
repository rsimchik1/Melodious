#include "MainComponent.h"

#include "../Model/LeafChannel.h"
#include "../Model/OscClip.h"
#include "../Model/OscClipReader.h"


const float starts[4] = { 0, 1, 2, 2.5 };
const float ends[4] = { 2, 8, 10, 12 };
//==============================================================================
MainComponent::MainComponent()
{
    addAndMakeVisible(arrangeView);
    // Make sure you set the size of the component after
    // you add any child components.
    setSize (800, 600);
    arrangeView.setColour(ArrangeView::BACKGROUND_COLOR, juce::Colour(0xff030b47));
    arrangeView.setColour(ArrangeView::BORDER_LIGHT_COLOR, juce::Colour(0xff737795));
    arrangeView.setColour(ArrangeView::BORDER_HEAVY_COLOR, juce::Colours::white);
    arrangeView.setColour(ArrangeView::PLAYHEAD_COLOR, juce::Colours::white);
    arrangeView.setColour(ArrangeView::TEXT_COLOR, juce::Colours::white);

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

    auto trackView1 = new TrackView("Track 1", sampleRate);
    auto trackView2 = new TrackView("Track 2", sampleRate);
    auto trackView3 = new TrackView("Track 3", sampleRate);
    
    const float baseFreq = 260.0;
    auto *clip1 = new OscClip(baseFreq, 0.25);
    auto *clip2 = new OscClip(baseFreq * 3.0/2, 0.25);
    auto *clip3 = new OscClip(baseFreq * 5.0/4, 0.25);
    auto *clip4 = new OscClip(baseFreq * 2, 0.25);
    clip1->setStartEndFrames(sampleRate * starts[0], sampleRate * ends[0]);
    clip2->setStartEndFrames(sampleRate * starts[1], sampleRate * ends[1]);
    clip3->setStartEndFrames(sampleRate * starts[2], sampleRate * ends[2]);
    clip4->setStartEndFrames(sampleRate * starts[3], sampleRate * ends[3]);

    auto* clipView1 = new ClipView(clip1->getStartFrame(), clip1->getEndFrame());
    auto* clipView2 = new ClipView(clip2->getStartFrame(), clip2->getEndFrame());
    auto* clipView3 = new ClipView(clip3->getStartFrame(), clip3->getEndFrame());
    auto* clipView4 = new ClipView(clip4->getStartFrame(), clip4->getEndFrame());

    clipView1->setColor(juce::Colour(0xff2ec8c8));
    clipView2->setColor(juce::Colour(0xff7e6cef));
    clipView3->setColor(juce::Colour(0xfffc09e4));
    clipView4->setColor(juce::Colour(0xff2ec8c8));

    track1->insertClip(clip1);
    trackView1->addClip(clipView1);
    track2->insertClip(clip2);
    trackView2->addClip(clipView2);
    track3->insertClip(clip3);
    trackView3->addClip(clipView3);
    track1->insertClip(clip4);
    trackView1->addClip(clipView4);

    dynamic_cast<LeafChannel *>(mixer.getChannelAt(0))->setAudioSource(track1);
    dynamic_cast<LeafChannel *>(mixer.getChannelAt(1))->setAudioSource(track2);
    dynamic_cast<LeafChannel *>(mixer.getChannelAt(2))->setAudioSource(track3);

    arrangeView.addTrack(trackView1);
    arrangeView.addTrack(trackView2);
    arrangeView.addTrack(trackView3);
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
    arrangeView.setSampleRate(sampleRate);
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
    arrangeView.setTime(timeline.getPlaybackHead());
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
    arrangeView.setBounds(getLocalBounds());
}
