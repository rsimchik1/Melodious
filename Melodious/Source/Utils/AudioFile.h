#pragma once

#include "File.h"
#include "../Model/AudioBuffer.h"
#include "../JuceLibraryCode/JuceHeader.h"

/**
 * Class for reading and writing audio data on disk.
 */
class AudioFile : public File
{
public:
	/**
	 * Determine whether the given extension is valid for a supported audio file
	 * format.
	 *
	 * @param extension The extension to check. (e.g. ".mp3")
	 * @return true if the extension is valid, false otherwise.
	 */
	static bool isExtensionValid(const std::string &extension);

	/**
	 * Create a new AudioFile at the given path.
	 *
	 * @throw FileFormatException If the path is not an audio file.
	 * @param absolutePath The absolute path to this file.
	 */
	AudioFile(std::string absolutePath);

	/**
	 * Destroy this AudioFile.
	 */
	~AudioFile();

	/**
	 * Write a buffer of data to disk. Read/write head will be incremented by
	 * the number of frames written. If writing starts past the end of the file,
	 * the preceding empty space will be filled with zeros.
	 *
	 * @throw FileAccessException If this file is not currently open.
	 * @param buffer The data to write.
	 */
	void writeBuffer(AudioBuffer buffer);

	/**
	 * Read a number of frames from disk. Read/write head will be incremented by
	 * the number of frames read. If the end of the file is reached, the
	 * AudioBuffer's size will match the number of samples that were read (if
	 * reading starts past the end of the file, an empty AudioBuffer will be
	 * returned).
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
	void createOnDisk() override;
	void deleteFromDisk() override;
private:
	static const std::vector<std::string> SUPPORTED_EXTENSIONS;
	static const int WRITE_BUFFER_SIZE = 4096;

	std::string extension;
	uint32_t readWriteHead;

	std::unique_ptr<juce::File> file;
	juce::AudioFormatManager* formatManager;
	juce::AudioFormat* format;
	std::unique_ptr<juce::AudioFormatWriter> writer;
	std::unique_ptr<juce::FileOutputStream> writeStream;
	std::unique_ptr<juce::AudioFormatReader> reader;
	std::unique_ptr<juce::FileInputStream> readStream;

	std::atomic<bool> currentlyOpen;

	void initializeRead();
	void initializeWrite(int sampleRate, int numChannels, int bitDepth);
};
