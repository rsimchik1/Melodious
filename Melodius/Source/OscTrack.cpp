#include "OscTrack.h"

#include "juce_core/juce_core.h"

OscTrack::OscTrack(float frequency, float amplitude)
{
	this->frequency = frequency;
	this->amplitude = amplitude;
	this->phase = 0;
}

AudioBuffer OscTrack::processFrames(int numFrames, const Timeline& relativeTime)
{
	auto outBuffer = AudioBuffer(numFrames, 2);
	for (int sample = 0; sample < outBuffer.getNumFrames(); sample++)
	{
		float frequencyOffset = ((relativeTime.getPlaybackHead() + sample) % 
			relativeTime.getSampleRate()) * 0.01;
		for (int channel = 0; channel < outBuffer.getNumChannels(); channel++)
		{
			outBuffer.writeSampleAt(sample, channel, std::sin(phase) * amplitude);
		}
        phase += juce::MathConstants<float>::twoPi * 
			((frequency + frequencyOffset) / relativeTime.getSampleRate());
        if (phase >= juce::MathConstants<float>::twoPi) phase -= juce::MathConstants<float>::twoPi;
	}

	return outBuffer;
}
