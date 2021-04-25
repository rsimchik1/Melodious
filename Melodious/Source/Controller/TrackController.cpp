#include "TrackController.h"

TrackController::TrackController(Channel* channel)
	: channel(std::shared_ptr<Channel>(channel))
{}

void TrackController::notify(TrackControlsView* caller)
{
	auto modifiers = channel->getModifiers();
	modifiers->setName(caller->getName().toStdString());
	modifiers->setPan(caller->getPan());
	modifiers->setVolume(caller->getVolume());
}
