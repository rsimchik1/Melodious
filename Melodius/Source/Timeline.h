#pragma once

class Timeline
{
public:
	Timeline(int sampleRate = 44100);
	int getSampleRate() const;
private:
	int sampleRate;
};