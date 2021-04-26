#include "TransportController.h"

TransportController::TransportController(TransportState* state)
	: stateToModify(state)
{}

void TransportController::notify(MixHeaderView* caller)
{
	static bool wasPlaying = false;

	auto buttonStates = caller->getButtonStates();
	
	if (buttonStates.playPressed)
	{
		wasPlaying = true;
		*stateToModify = StartPlay;
	}
	else if (buttonStates.pausePressed)
	{
		wasPlaying = false;
		*stateToModify = Pausing;
	}
	else if (buttonStates.stopPressed)
	{
		wasPlaying = false;
		*stateToModify = Stopping;
	}
	else if (buttonStates.backPressed)
		*stateToModify = GoingBack;
	else if (buttonStates.nextPressed)
		*stateToModify = GoingNext;
	else if (buttonStates.recordPressed)
		*stateToModify = StartRecord;

	if (buttonStates.rewindPressed)
		*stateToModify = Rewinding;
	else if (buttonStates.rewindReleased)
		*stateToModify = wasPlaying ? StartPlay : Stopped;
	else if (buttonStates.fastForwardPressed)
		*stateToModify = FastForwarding;
	else if (buttonStates.fastForwardReleased)
		*stateToModify = wasPlaying ? StartPlay : Stopped;
}
