#pragma once

#include "JuceHeader.h"
#include "Observer.h"
#include "../Model/ChannelMixer.h"
#include "../Model/Timeline.h"
#include "../Utils/AudioFile.h"
#include "../Utils/FileManager.h"
#include "../View/FooterView.h"

class RenderController : public Observer<FooterView>
{
public:
	RenderController(std::shared_ptr<Timeline> timeline, std::shared_ptr<ChannelMixer> channels,
					 std::shared_ptr<FileManager> fileManager);
	void notify(FooterView* caller) override;
private:
	std::shared_ptr<Timeline> timeline;
	std::shared_ptr<ChannelMixer> channels;
	std::shared_ptr<FileManager> fileManager;
	void renderSamples(AudioFile* destinationFile, uint64_t startSample, uint64_t endSample);
};
