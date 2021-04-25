#include "ClipController.h"

ClipObserver::ClipObserver(AudioClip* clip)
	: clip(std::shared_ptr<AudioClip>(clip))
{}

void ClipObserver::notify(ClipView* caller)
{
}
