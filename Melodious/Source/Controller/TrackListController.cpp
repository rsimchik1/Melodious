#include "TrackListController.h"

TrackListController::TrackListController(ChannelMixer* mixer)
	: mixer(std::shared_ptr<ChannelMixer>(mixer))
{}

void TrackListController::notify(TrackControlsListView* caller)
{
	;
	auto newController = std::make_shared<TrackController>(mixer->createAudioChannel());
	trackControllers.push_back(newController);
	caller->appendNewTrackControls()->addObserver(newController);
}
