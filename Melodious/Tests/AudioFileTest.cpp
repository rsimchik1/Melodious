#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <filesystem>
#include <string>

#include "../Source/Exceptions/FileAccessException.h"
#include "../Source/Exceptions/FileFormatException.h"
#include "../Source/Utils/AudioFile.h"

BOOST_AUTO_TEST_SUITE(AudioFileTest);

const std::string TEST_DIR = std::filesystem::current_path().string() + "/";

BOOST_AUTO_TEST_CASE(AudioFileConstructorTest)
{
	auto audioFile = AudioFile(TEST_DIR + "test1.wav");
	BOOST_CHECK_EQUAL(audioFile.getPath(), TEST_DIR + "test1.wav");

	BOOST_CHECK_THROW(AudioFile(TEST_DIR + "bad.txt"), FileFormatException);
	BOOST_CHECK_THROW(AudioFile(TEST_DIR + "bad"), FileFormatException);
	BOOST_CHECK_THROW(AudioFile(TEST_DIR + ""), FileFormatException);
}

BOOST_AUTO_TEST_CASE(AudioFileCreateDeleteTest)
{
	auto audioFile = AudioFile(TEST_DIR + "test2.wav");
	int sampleRate = 44100, numChannels = 1, bitDepth = 32;
	audioFile.prepareToWrite(sampleRate, numChannels, bitDepth);
	BOOST_CHECK_NO_THROW(audioFile.createOnDisk());
	BOOST_CHECK_EQUAL(true, std::filesystem::exists(TEST_DIR + "test2.wav"));
	BOOST_CHECK_NO_THROW(AudioFile(TEST_DIR + "test2.wav"));
	BOOST_CHECK_NO_THROW(audioFile.deleteFromDisk());
	BOOST_CHECK_EQUAL(false, std::filesystem::exists(TEST_DIR + "test2.wav"));
}

BOOST_AUTO_TEST_CASE(AuidoFileReadWriteTest)
{
	auto audioFile = AudioFile(TEST_DIR + "test3.wav");
	auto inputBuffer = AudioBuffer(8, 1);
	int sampleRate = 44100, numChannels = 1, bitDepth = 32;
	float testData[] = { 0.1, -0.2, 0.3, -0.4, 0.5, -0.6, 0.7, -0.8 };
	for (auto i = 0; i < 8; i++)
		inputBuffer.writeSampleAt(i, 0, testData[i]);
	
	audioFile.createOnDisk();
	audioFile.prepareToWrite(sampleRate, numChannels, bitDepth);

	BOOST_CHECK_EQUAL(audioFile.isOpen(), false);
	BOOST_CHECK_THROW(audioFile.writeBlock(inputBuffer), FileAccessException);
	BOOST_CHECK_NO_THROW(audioFile.open());
	BOOST_CHECK_EQUAL(audioFile.isOpen(), true);
	BOOST_CHECK_NO_THROW(audioFile.writeBlock(inputBuffer));
	BOOST_CHECK_NO_THROW(audioFile.close());
	BOOST_CHECK_EQUAL(audioFile.isOpen(), false);

	AudioBuffer outputBuffer(8,1);

	BOOST_CHECK_NO_THROW(audioFile.moveToFrame(0));
	BOOST_CHECK_NO_THROW(audioFile.prepareToRead(outputBuffer.getNumFrames(),
												 sampleRate, 
												 outputBuffer.getNumChannels()));
	BOOST_CHECK_THROW(outputBuffer = audioFile.readFrames(), FileAccessException);
	audioFile.open();
	BOOST_CHECK_NO_THROW(outputBuffer = audioFile.readFrames());
	BOOST_CHECK_EQUAL(outputBuffer.getNumFrames(), 8);
	BOOST_CHECK_NO_THROW(audioFile.moveToFrame(0));

	BOOST_CHECK_EQUAL(inputBuffer.getNumFrames(), outputBuffer.getNumFrames());
	BOOST_CHECK_EQUAL(inputBuffer.getNumChannels(), outputBuffer.getNumChannels());

	float expectedSum = 0.0, actualSum = 0.0;
	for (auto i = 0; i < 8; i++)
	{
		expectedSum += inputBuffer.readSampleAt(i, 0);
		actualSum += outputBuffer.readSampleAt(i, 0);
	}
	BOOST_CHECK_EQUAL(expectedSum, actualSum);

	auto existingFile = AudioFile(TEST_DIR + "test3.wav");
	BOOST_CHECK_NO_THROW(existingFile.moveToFrame(0));
	BOOST_CHECK_NO_THROW(existingFile.prepareToRead(outputBuffer.getNumFrames(),
												 sampleRate, 
												 outputBuffer.getNumChannels()));
	BOOST_CHECK_THROW(outputBuffer = existingFile.readFrames(), FileAccessException);
	existingFile.open();
	BOOST_CHECK_NO_THROW(outputBuffer = existingFile.readFrames());
	BOOST_CHECK_EQUAL(outputBuffer.getNumFrames(), 8);
	BOOST_CHECK_NO_THROW(existingFile.moveToFrame(0));

	BOOST_CHECK_EQUAL(inputBuffer.getNumFrames(), outputBuffer.getNumFrames());
	BOOST_CHECK_EQUAL(inputBuffer.getNumChannels(), outputBuffer.getNumChannels());

	expectedSum = 0.0, actualSum = 0.0;
	for (auto i = 0; i < 8; i++)
	{
		expectedSum += inputBuffer.readSampleAt(i, 0);
		actualSum += outputBuffer.readSampleAt(i, 0);
	}
	
	audioFile.deleteFromDisk();
}

BOOST_AUTO_TEST_CASE(AudioFileExtensionsTest)
{
	BOOST_CHECK_EQUAL(true, AudioFile::isExtensionValid(".wav"));
	BOOST_CHECK_EQUAL(true, AudioFile::isExtensionValid(".mp3"));
	BOOST_CHECK_EQUAL(true, AudioFile::isExtensionValid(".ogg"));
	BOOST_CHECK_EQUAL(true, AudioFile::isExtensionValid(".flac"));
	BOOST_CHECK_EQUAL(true, AudioFile::isExtensionValid(".aif"));

	BOOST_CHECK_EQUAL(false, AudioFile::isExtensionValid("aif"));
	BOOST_CHECK_EQUAL(false, AudioFile::isExtensionValid(".wma")); // This will fail if we decide to support WMA
	BOOST_CHECK_EQUAL(false, AudioFile::isExtensionValid(".txt"));
	BOOST_CHECK_EQUAL(false, AudioFile::isExtensionValid(""));
}

BOOST_AUTO_TEST_SUITE_END();