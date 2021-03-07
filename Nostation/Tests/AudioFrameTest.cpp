#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "../Source/AudioFrame.h"
#include "../Source/AudioFrame.cpp"
#include "../Source/Exceptions/IndexOutOfBoundsException.h"

BOOST_AUTO_TEST_SUITE(AudioFrameTest);

	BOOST_AUTO_TEST_CASE(AudioFrameConstructor)
	{
		auto frame = AudioFrame(2);
		BOOST_CHECK_EQUAL(frame.getNumChannels(), 2);
		BOOST_CHECK_EQUAL(frame.readSampleAt(0), 0.0f);
		BOOST_CHECK_EQUAL(frame.readSampleAt(1), 0.0f);
	}

	BOOST_AUTO_TEST_CASE(AudioFrameWriteSampleAt)
	{
		auto frame = AudioFrame(2);
		BOOST_CHECK_NO_THROW(frame.writeSampleAt(0, 0.5f));
		BOOST_CHECK_EQUAL(frame.readSampleAt(0), 0.5f);
		BOOST_CHECK_NO_THROW(frame.writeSampleAt(0, -0.5f));
		BOOST_CHECK_EQUAL(frame.readSampleAt(1), -0.5f);
		BOOST_CHECK_EQUAL(frame.readSampleAt(0), 0.5f);
		BOOST_CHECK_NO_THROW(frame.writeSampleAt(0, 1.0f));
		BOOST_CHECK_EQUAL(frame.readSampleAt(0), 1.0f);

		BOOST_CHECK_THROW(frame.writeSampleAt(2, 0.0f),
			IndexOutOfBoundsException);
		BOOST_CHECK_THROW(frame.writeSampleAt(100, 0.0f),
			IndexOutOfBoundsException);
		BOOST_CHECK_THROW(frame.writeSampleAt(-1, 0.0f),
			IndexOutOfBoundsException);
		BOOST_CHECK_THROW(frame.writeSampleAt(-100, 0.0f),
			IndexOutOfBoundsException);
		BOOST_CHECK_THROW(frame.writeSampleAt(0, 1.001f),
			IndexOutOfBoundsException);
		BOOST_CHECK_THROW(frame.writeSampleAt(0, -1.001f),
			IndexOutOfBoundsException);
		BOOST_CHECK_THROW(frame.writeSampleAt(0, 100.0f),
			IndexOutOfBoundsException);
		BOOST_CHECK_THROW(frame.writeSampleAt(0, -100.0f),
			IndexOutOfBoundsException);
	}

	BOOST_AUTO_TEST_CASE(AudioFrameReadSampleAt)
	{
		auto frame = AudioFrame(2);
		BOOST_CHECK_EQUAL(frame.readSampleAt(0), 0.0f);
		frame.writeSampleAt(0, 0.5f);
		BOOST_CHECK_EQUAL(frame.readSampleAt(0), 0.5f);
		BOOST_CHECK_THROW(frame.readSampleAt(-1), IndexOutOfBoundsException);
		BOOST_CHECK_THROW(frame.readSampleAt(2), IndexOutOfBoundsException);
		BOOST_CHECK_THROW(frame.readSampleAt(-100), IndexOutOfBoundsException);
		BOOST_CHECK_THROW(frame.readSampleAt(100), IndexOutOfBoundsException);
	}

	BOOST_AUTO_TEST_CASE(AudioFrameGetNumChannels)
	{
		auto frame1 = AudioFrame(1);
		auto frame2 = AudioFrame(2);
		auto frame3 = AudioFrame(3);
		BOOST_CHECK_EQUAL(frame1.getNumChannels(), 1);
		BOOST_CHECK_EQUAL(frame2.getNumChannels(), 2);
		BOOST_CHECK_EQUAL(frame3.getNumChannels(), 3);
		BOOST_CHECK_EQUAL(frame1.getNumChannels() + frame2.getNumChannels(),
			frame3.getNumChannels());
	}

BOOST_AUTO_TEST_SUITE_END();