#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "../Source/AudioBuffer.h"
#include "../Source/AudioBuffer.cpp"
#include "../Source/AudioFrame.h"
#include "../Source/Exceptions/IndexOutOfBoundsException.h"
#include "../Source/Exceptions/InvalidFrameException.h"
#include "../Source/Exceptions/InvalidSampleException.h"
#include "../Source/Exceptions/InvalidBufferException.h"

BOOST_AUTO_TEST_SUITE(AudioBufferTest);

void populateTestBuffer(AudioBuffer& toPopulate)
{
	const int numFrames = 8;
	float channel1[numFrames] = { 0.0f, 0.3f, 0.5f, 0.4f, 0.1f, -0.3f, -0.5f, -0.7f };
	float channel2[numFrames] = { 0.0f, 0.1f, 0.2f, 0.05f, -0.1f, -0.4f, -0.3f, 0.0f };

	for (auto frame = 0; frame < numFrames; frame++)
	{
		for (auto channel = 0; channel < toPopulate.getNumChannels(); channel++)
		{
			toPopulate.writeSampleAt(frame, channel, channel % 2 == 0 ? 
				channel1[frame] : channel2[frame]);
		}
	}
}

BOOST_AUTO_TEST_CASE(AudioBufferConstructor)
{
	auto buffer = AudioBuffer(8, 2);
	BOOST_CHECK_EQUAL(buffer.getNumFrames(), 8);
	BOOST_CHECK_EQUAL(buffer.getNumChannels(), 2);
	for (auto frame = 0; frame < 8; frame++)
		for (auto channel = 0; channel < buffer.getNumChannels(); channel++)
			BOOST_CHECK_EQUAL(buffer.readSampleAt(frame, channel), 0.0f);

	BOOST_CHECK_THROW(AudioBuffer(0, 2), InvalidBufferException);
	BOOST_CHECK_THROW(AudioBuffer(-100, 2), InvalidBufferException);
	BOOST_CHECK_THROW(AudioBuffer(8, 0), InvalidBufferException);
	BOOST_CHECK_THROW(AudioBuffer(8, -100), InvalidBufferException);
}

BOOST_AUTO_TEST_CASE(AudioBufferCopy)
{
	auto buffer = AudioBuffer(8, 2);
	populateTestBuffer(buffer);
	auto bufferCopy = AudioBuffer(buffer);
	BOOST_CHECK_EQUAL(bufferCopy.getNumFrames(), buffer.getNumFrames());
	BOOST_CHECK_EQUAL(bufferCopy.getNumChannels(), buffer.getNumChannels());
	for (auto frame = 0; frame < 8; frame++)
		for (auto channel = 0; channel < buffer.getNumChannels(); channel++)
			BOOST_CHECK_EQUAL(buffer.readSampleAt(frame, channel), bufferCopy.readSampleAt(frame, channel));
}

BOOST_AUTO_TEST_CASE(AudioBufferReadFrameAt)
{
	auto buffer = AudioBuffer(8, 2);
	populateTestBuffer(buffer);
	auto frame1 = buffer.readFrameAt(0);
	BOOST_CHECK_EQUAL(frame1.readSampleAt(0), 0.0f);
	BOOST_CHECK_EQUAL(frame1.readSampleAt(1), 0.0f);
	auto frame2 = buffer.readFrameAt(7);
	BOOST_CHECK_EQUAL(frame2.readSampleAt(0), -0.7f);
	BOOST_CHECK_EQUAL(frame2.readSampleAt(1), 0.0f);
	auto frame3 = buffer.readFrameAt(4);
	BOOST_CHECK_EQUAL(frame3.readSampleAt(0), 0.1f);
	BOOST_CHECK_EQUAL(frame3.readSampleAt(1), -0.1f);
	BOOST_CHECK_THROW(buffer.readFrameAt(8), IndexOutOfBoundsException);
	BOOST_CHECK_THROW(buffer.readFrameAt(-1), IndexOutOfBoundsException);
	BOOST_CHECK_THROW(buffer.readFrameAt(100), IndexOutOfBoundsException);
	BOOST_CHECK_THROW(buffer.readFrameAt(-100), IndexOutOfBoundsException);
}

BOOST_AUTO_TEST_CASE(AudioBufferWriteFrameAt)
{
	auto buffer = AudioBuffer(8, 2);
	populateTestBuffer(buffer);
	auto goodFrame = AudioFrame(2);
	goodFrame.writeSampleAt(0, 0.5f);
	goodFrame.writeSampleAt(1, -0.5f);
	auto badFrame = AudioFrame(1);
	badFrame.writeSampleAt(0, 0.5f);
	buffer.writeFrameAt(3, goodFrame);
	auto checkFrame = buffer.readFrameAt(3);
	BOOST_CHECK_EQUAL(checkFrame.readSampleAt(0), goodFrame.readSampleAt(0));
	BOOST_CHECK_EQUAL(checkFrame.readSampleAt(1), goodFrame.readSampleAt(1));
	BOOST_CHECK_THROW(buffer.writeFrameAt(3, badFrame), InvalidFrameException);
	BOOST_CHECK_THROW(buffer.writeFrameAt(-1, goodFrame), IndexOutOfBoundsException);
	BOOST_CHECK_THROW(buffer.writeFrameAt(8, goodFrame), IndexOutOfBoundsException);
	BOOST_CHECK_THROW(buffer.writeFrameAt(-100, goodFrame), IndexOutOfBoundsException);
	BOOST_CHECK_THROW(buffer.writeFrameAt(100, goodFrame), IndexOutOfBoundsException);
}

BOOST_AUTO_TEST_CASE(AudioBufferReadSampleAt)
{
	auto buffer = AudioBuffer(8, 2);
	populateTestBuffer(buffer);
	BOOST_CHECK_EQUAL(buffer.readSampleAt(0, 0), 0.0f);
	BOOST_CHECK_EQUAL(buffer.readSampleAt(0, 1), 0.0f);
	BOOST_CHECK_EQUAL(buffer.readSampleAt(7, 0), -0.7f);
	BOOST_CHECK_EQUAL(buffer.readSampleAt(7, 1), 0.0f);
	BOOST_CHECK_EQUAL(buffer.readSampleAt(4, 0), 0.1f);
	BOOST_CHECK_EQUAL(buffer.readSampleAt(4, 1), -0.1f);
	BOOST_CHECK_THROW(buffer.readSampleAt(8, 0), IndexOutOfBoundsException);
	BOOST_CHECK_THROW(buffer.readSampleAt(-1, 0), IndexOutOfBoundsException);
	BOOST_CHECK_THROW(buffer.readSampleAt(100, 0), IndexOutOfBoundsException);
	BOOST_CHECK_THROW(buffer.readSampleAt(-100, 0), IndexOutOfBoundsException);
	BOOST_CHECK_THROW(buffer.readSampleAt(4, 2), IndexOutOfBoundsException);
	BOOST_CHECK_THROW(buffer.readSampleAt(4, -1), IndexOutOfBoundsException);
	BOOST_CHECK_THROW(buffer.readSampleAt(4, 100), IndexOutOfBoundsException);
	BOOST_CHECK_THROW(buffer.readSampleAt(4, -100), IndexOutOfBoundsException);
}

BOOST_AUTO_TEST_CASE(AudioBufferWriteSampleAt)
{
	auto buffer = AudioBuffer(8, 2);
	populateTestBuffer(buffer);
	buffer.writeSampleAt(3, 0, 0.5f);
	buffer.writeSampleAt(3, 1, -0.5f);
	BOOST_CHECK_EQUAL(buffer.readSampleAt(3, 0), 0.5f);
	BOOST_CHECK_EQUAL(buffer.readSampleAt(3, 0), 0.5f);
	BOOST_CHECK_THROW(buffer.writeSampleAt(3, 0, 1.001f), InvalidSampleException);
	BOOST_CHECK_THROW(buffer.writeSampleAt(3, 0, -1.001f), InvalidSampleException);
	BOOST_CHECK_THROW(buffer.writeSampleAt(3, 0, 100.0f), InvalidSampleException);
	BOOST_CHECK_THROW(buffer.writeSampleAt(3, 0, -100.0f), InvalidSampleException);
	BOOST_CHECK_THROW(buffer.writeSampleAt(-1, 0, 0.5f), IndexOutOfBoundsException);
	BOOST_CHECK_THROW(buffer.writeSampleAt(8, 0, 0.5f), IndexOutOfBoundsException);
	BOOST_CHECK_THROW(buffer.writeSampleAt(-100, 0, 0.5f), IndexOutOfBoundsException);
	BOOST_CHECK_THROW(buffer.writeSampleAt(100, 0, 0.5f), IndexOutOfBoundsException);
	BOOST_CHECK_THROW(buffer.writeSampleAt(3, -1, 0.5f), IndexOutOfBoundsException);
	BOOST_CHECK_THROW(buffer.writeSampleAt(3, 2, 0.5f), IndexOutOfBoundsException);
	BOOST_CHECK_THROW(buffer.writeSampleAt(3, -100, 0.5f), IndexOutOfBoundsException);
	BOOST_CHECK_THROW(buffer.writeSampleAt(3, 100, 0.5f), IndexOutOfBoundsException);
}

BOOST_AUTO_TEST_CASE(AudioBufferGetNumFrames)
{
	auto buffer1 = AudioBuffer(4, 2);
	auto buffer2 = AudioBuffer(6, 1);
	auto buffer3 = AudioBuffer(10, 3);
	BOOST_CHECK_EQUAL(buffer1.getNumFrames(), 4);
	BOOST_CHECK_EQUAL(buffer2.getNumFrames(), 6);
	BOOST_CHECK_EQUAL(buffer3.getNumFrames(), 10);
	BOOST_CHECK_EQUAL(buffer3.getNumFrames(), buffer2.getNumFrames() 
		+ buffer1.getNumFrames());
}

BOOST_AUTO_TEST_CASE(AudioBufferGetNumChannels)
{
	auto buffer1 = AudioBuffer(4, 2);
	auto buffer2 = AudioBuffer(6, 1);
	auto buffer3 = AudioBuffer(10, 3);
	BOOST_CHECK_EQUAL(buffer1.getNumChannels(), 2);
	BOOST_CHECK_EQUAL(buffer2.getNumChannels(), 1);
	BOOST_CHECK_EQUAL(buffer3.getNumChannels(), 3);
	BOOST_CHECK_EQUAL(buffer3.getNumChannels(), buffer2.getNumChannels()
		+ buffer1.getNumChannels());
}

BOOST_AUTO_TEST_SUITE_END();