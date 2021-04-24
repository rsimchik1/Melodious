#pragma once
#include "Observer.h"

#include "../Model/Channel.h"

#include "../View/TrackControlsView.h"

class TrackController : public Observer<TrackControlsView>
{
public:
	TrackController(Channel *channel);
	void notify(TrackControlsView *caller) override;
private:
	std::shared_ptr<Channel> channel;
};
