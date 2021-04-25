#include "TransportController.h"

TransportController::TransportController(TransportState* state)
	: stateToModify(state)
{}

void TransportController::notify(MixHeaderView* caller)
{
	auto buttonStates = caller->getButtonStates();
	
	if (buttonStates.playPressed)
		*stateToModify = StartPlay;
	else if (buttonStates.pausePressed)
		*stateToModify = Pausing;
	else if (buttonStates.stopPressed)
		*stateToModify = Stopping;
}
