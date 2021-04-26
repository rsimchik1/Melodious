#include "TrackListController.h"

#include "../Model/AudioClip.h"
#include "../Model/AudioClipReader.h"
#include "../Model/LeafChannel.h"

#include <filesystem>

FileManager TrackListController::fileManager;

TrackListController::TrackListController(ChannelMixer* mixer, ArrangementView* arrangementView, double sampleRate)
	: mixer(std::shared_ptr<ChannelMixer>(mixer)),
	arrangementView(std::shared_ptr<ArrangementView>(arrangementView)),
	sampleRate(sampleRate)
{
	formatManager.registerBasicFormats();
}

void TrackListController::notify(TrackControlsListView* caller)
{
	auto files = caller->getLoadedFiles();
	
	for (auto file : files)
	{
		auto newChannel = std::unique_ptr<LeafChannel>(mixer->createAudioChannel());
		auto newTrack = std::make_unique<Track<AudioClip>>(new AudioClipReader(&fileManager));

		std::string trackName = "New Track";
		auto newTrackView = arrangementView->createAndAppendTrack();
		auto newControls = newTrackView.controls;

		if (file.existsAsFile())
		{
			double sourceSampleRate = formatManager.createReaderFor(file)->sampleRate;
			const double sampleRateScale = sampleRate / sourceSampleRate;
			auto path = file.getFullPathName().toStdString();
			trackName = std::filesystem::path(path).stem().string();
			auto handle = fileManager.addExistingFile(path);
			auto audioFile = static_cast<AudioFile*>(fileManager.getFile(handle));
			auto newClip = std::make_unique<AudioClip>();
			newClip->setStartEndFrames(0, audioFile->getLengthInSamples() * sampleRateScale);
			newClip->setFileHandle(handle);
			newTrack->insertClip(newClip.release());
			auto *newClipView = arrangementView->createClipOnTrack(arrangementView->getNumTracks() - 1,
																  0, audioFile->getLengthInSamples() * sampleRateScale); 
			newClipView->setStartEndSample(0, audioFile->getLengthInSamples() * sampleRateScale);
			auto* cache = new juce::AudioThumbnailCache(1);
			auto *thumbnail = new juce::AudioThumbnail(512, formatManager, *cache);
			thumbnail->setSource(new juce::FileInputSource(file));
			newClipView->setAudioThumbnail(thumbnail, cache);
		}

		newChannel->setAudioSource(newTrack.release());
		auto newController = std::make_shared<TrackController>(newChannel.release());
		trackControllers.push_back(newController);
		newControls->addObserver(newController);
		newControls->setName(trackName);
	}

	arrangementView->resized();
}

void TrackListController::setSampleRate(double sampleRate)
{
	sampleRate = sampleRate;
}
