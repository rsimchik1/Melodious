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
	 * Write a block of data to disk. Read/write head will be incremented by
	 * the number of frames in the block. If writing starts past the end of the
	 * file, the preceding empty space will be filled with zeros.
	 *
	 * @throw FileAccessException If this file is not currently open, or if data
	 * cannot be written.
	 * @param block The data to write.
	 */
	void writeBlock(AudioBuffer block);

	/**
	 * Read a block of frames from disk. Read/write head will be incremented by
	 * the number of frames read. If the end of the file is reached, the
	 * AudioBuffer's size will match the number of samples that were read (if
	 * reading starts past the end of the file, an empty AudioBuffer will be
	 * returned).
	 *
	 * @throw FileAccessException If this file is not currently open, or if data
	 * cannot be written.
	 * @return An AudioBuffer containing the data that was read.
	 */
	AudioBuffer readFrames();

	/**
	 * Set the properties of the audio file to be written.
	 *
	 * @param sampleRate The samples per second to be stored in the file.
	 * @param numChannels The number of audio channels in the file.
	 * @param bitDepth The number of bits per sample in the file.
	 */
	void prepareToWrite(int sampleRate, int numChannels, int bitDepth);

	/**
	 * Set the number of samples to read at a time and the sample rate used by
	 * the application (may be different than the file's sample rate).
	 *
	 * @param framesPerBlock Number of frames to be read by readFrames()
	 * @param sampleRate Sample rate expected by the application.
	 * @param numChannels Number of channels expected by the application.
	 */
	void prepareToRead(int framesPerBlock, int sampleRate, int numChannels);

	/**
	 * Set the position of the read/write head to the given frame.
	 *
	 * @param frame The new position of the read/write head.
	 */
	void moveToFrame(uint64_t frame);

	uint64_t getLengthInSamples();

	void open() override;
	void close() override;
	bool isOpen() override;
	void createOnDisk() override;
	void deleteFromDisk() override;
private:
	static const std::vector<std::string> SUPPORTED_EXTENSIONS;

	int fileSampleRate;
	int fileNumChannels;
	int fileBitDepth;

	int readerSampleRate;
	int readerNumChannels;
	int readerBlockSize;
	std::atomic<bool> currentlyOpen;
	std::string extension;
	uint64_t readWriteHead;

	std::unique_ptr<juce::File> file;
	juce::AudioFormatManager formatManager;
	std::unique_ptr<juce::AudioFormatReaderSource> readerSource;
	std::unique_ptr<juce::AudioTransportSource> transportSource;
	std::unique_ptr<juce::AudioFormatWriter> writer;

	void initializeRead();
	void initializeWrite(int sampleRate, int numChannels, int bitDepth);
};
