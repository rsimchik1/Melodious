#pragma once

#include <JuceHeader.h>

#include "../Model/ChannelMixer.h"
#include "ArrangementView.h"
#include "FooterView.h"
#include "MixHeaderView.h"
#include "../Controller/RenderController.h"
#include "../Controller/TransportController.h"

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent  : public juce::AudioAppComponent
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent() override;

    //==============================================================================
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

    //==============================================================================
    void paint (juce::Graphics& g) override;
    void resized() override;

private:
    //==============================================================================
    // Your private member variables go here...

    unsigned int sampleRate;
    ChannelMixer mixer;
    Timeline timeline;

    TransportController::TransportState currentState;
    TransportController::TransportState lastState;
    TransportController transportController;
    std::shared_ptr<FileManager> fileManager;
    std::shared_ptr<TrackListController> trackListController;
    ArrangementView arrangementView;
    MixHeaderView mixHeaderView;
    FooterView footerView;
    std::shared_ptr<RenderController> renderController;
    int scrubSpeed = 4;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
};
