#pragma once
#include "Observer.h"
#include "../View/MixHeaderView.h"

class TransportController : public Observer<MixHeaderView>
{
public:
	enum TransportState
	{
		Stopped,
		StartPlay,
		Playing,
		Pausing,
		Paused,
		Stopping,
		StartRecord,
		Recording,
		Rewinding,
		FastForwarding
	};

	TransportController(TransportState* state);
	void notify(MixHeaderView* caller) override;
private:
	TransportState* stateToModify;
};
