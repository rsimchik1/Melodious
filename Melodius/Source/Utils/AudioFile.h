#pragma once
#include "File.h"
#include "../Model/AudioBuffer.h"
#include "JuceHeader.h"

/**
 * Class for reading and writing audio data on disk.
 */
class AudioFile : public File
{
public:
	/**
	 * Create a new AudioFile at the given path.
	 *
	 * @throw FileAccessException If the path does not exist.
	 * @throw FileFormatException If the path is not an audio file.
	 */
	AudioFile(std::string path);

	/**
	 * Destroy this AudioFile.
	 */
	~AudioFile();

	/**
	 * Write a buffer of data to disk. Read/write head will be incremented by
	 * the number of frames written.
	 *
	 * @throw FileAccessException If this file is not currently open.
	 * @param buffer The data to write.
	 */
	void writeBuffer(AudioBuffer buffer);

	/**
	 * Read a number of frames from disk. Read/write head will be incremented by
	 * the number of frames read.
	 *
	 * @throw FileAccessException If this file is not currently open.
	 * @param numFrames The number of frames to read.
	 * @return An AudioBuffer containing the data that was read.
	 */
	AudioBuffer readFrames(int numFrames);

	/**
	 * Set the position of the read/write head to the given frame.
	 *
	 * @param frame The new position of the read/write head.
	 */
	void moveToFrame(uint32_t frame);

	void open() override;
	void close() override;
	bool isOpen() override;
private:
	std::string path;
	juce::File* file;
	juce::AudioFormatWriter* writer;
	juce::AudioFormatReader* reader;
	uint32_t readWriteHead;

	std::atomic<bool> currentlyOpen;
};
