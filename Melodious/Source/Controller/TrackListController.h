#pragma once

#include "Observer.h"
#include "TrackController.h"
#include "../View/TrackControlsListView.h"
#include "../Model/ChannelMixer.h"

class TrackListController : public Observer<TrackControlsListView>
{
public:
	TrackListController(ChannelMixer *mixer);
	void notify(TrackControlsListView *caller) override;
private:
	std::shared_ptr<ChannelMixer> mixer;
	std::vector<std::shared_ptr<TrackController>> trackControllers;
};
