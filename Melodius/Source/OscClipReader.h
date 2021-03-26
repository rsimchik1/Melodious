#pragma once
#include "ClipReader.h"
#include "OscClip.h"

class OscClipReader : public ClipReader<OscClip>
{
public:
	AudioBuffer processFrames(int numFrames, const Timeline& relativeTime) override;
};
