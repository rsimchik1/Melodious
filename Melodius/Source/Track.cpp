#include "Track.h"

Track::Track()
{
}

Track::Track(Track* other)
{
}

Track::~Track()
{
}

AudioBuffer Track::processFrames(int numFrames, const Timeline& relativeTime)
{
	return AudioBuffer(numFrames, 2);
}
