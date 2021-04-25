#pragma once

#include "Observer.h"
#include "../Model/AudioClip.h"
#include "../View/ClipView.h"

class ClipObserver : public Observer<ClipView>
{
public:
	ClipObserver(AudioClip* clip);
	void notify(ClipView* caller) override;
private:
	std::shared_ptr<AudioClip> clip;
};