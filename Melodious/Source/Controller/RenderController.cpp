#include "RenderController.h"

RenderController::RenderController(std::shared_ptr<Timeline> timeline,
                                   std::shared_ptr<ChannelMixer> channels,
                                   std::shared_ptr<FileManager> fileManager)
	: timeline(timeline),
	channels(channels),
	fileManager(fileManager)
{
}

void RenderController::notify(FooterView* caller)
{
	caller->showLoadingMessage();
	auto chooser = juce::FileChooser("Choose output file.",
									 juce::File(),
									 "*.wav");
	if (chooser.browseForFileToSave(false))
	{
		auto destination = chooser.getResult();
		if (destination.existsAsFile())
			destination.deleteFile();

		auto handle = fileManager->createNewFile(destination.getFullPathName().toStdString(), true);
		auto outFile = fileManager->getFile(handle);
		renderSamples(static_cast<AudioFile*>(outFile), 0, timeline->getMaxSampleReached());
	}
	caller->hideLoadingMessage();
}

void RenderController::renderSamples(AudioFile* destinationFile,
	uint64_t startSample, uint64_t endSample)
{
	auto playheadStart = timeline->getPlaybackHead();
	const int bufferSize = 4096;
	auto writeBuffer = AudioBuffer(bufferSize, 2);
	timeline->movePlaybackHead(startSample);
	destinationFile->open();
	destinationFile->prepareToWrite(timeline->getSampleRate(), 2, 24);
	while (timeline->getPlaybackHead() < endSample)
	{
		writeBuffer = channels->processFrames(writeBuffer.getNumFrames(), *timeline);
		destinationFile->writeBlock(writeBuffer);
		timeline->shiftPlaybackHead(bufferSize);
	}
	destinationFile->close();
	timeline->movePlaybackHead(playheadStart);
}
