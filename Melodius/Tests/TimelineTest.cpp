#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "../Source/Model/Timeline.h"
#include "../Source/Exceptions/IndexOutOfBoundsException.h"
#include "../Source/Exceptions/InvalidArgumentException.h"

BOOST_AUTO_TEST_SUITE(TimelineTest);

	BOOST_AUTO_TEST_CASE(TimelineConstructorTest)
	{
		auto timeline = Timeline();
		BOOST_CHECK_EQUAL(timeline.getPlaybackHead(), 0);
		BOOST_CHECK_THROW(Timeline(0), InvalidArgumentException);
		BOOST_CHECK_THROW(Timeline(-44100), InvalidArgumentException);
	}

	BOOST_AUTO_TEST_CASE(TimelineMovementTest)
	{
		auto timeline = Timeline();
		timeline.movePlaybackHead(400);
		BOOST_CHECK_EQUAL(timeline.getPlaybackHead(), 400);
		timeline.shiftPlaybackHead(-50);
		BOOST_CHECK_EQUAL(timeline.getPlaybackHead(), 350);
		BOOST_CHECK_THROW(timeline.shiftPlaybackHead(-351),
			IndexOutOfBoundsException);
		timeline.shiftPlaybackHead(INT32_MAX);
		BOOST_CHECK_THROW(timeline.shiftPlaybackHead(INT32_MAX),
			IndexOutOfBoundsException);
		timeline.shiftPlaybackHead(INT32_MIN + 1);
		timeline.shiftPlaybackHead(-350);
		BOOST_CHECK_EQUAL(timeline.getPlaybackHead(), 0);
		BOOST_CHECK_THROW(timeline.shiftPlaybackHead(INT32_MIN),
			IndexOutOfBoundsException);
	}

	BOOST_AUTO_TEST_CASE(TimelineSamplesPerBeatTest)
	{
		auto srate1 = 44100;
		auto srate2 = 48000;
		
		auto timeline1 = Timeline(srate1);
		auto timeline2 = Timeline(srate2);

		auto tempo1 = 120.0;
		auto tempo2 = 60.0;
		auto tempo3 = 1.0;
		auto tempo4 = 500.0;
		BOOST_CHECK_EQUAL(timeline1.getSamplesPerBeat(120.0), srate1 / 2);
		BOOST_CHECK_EQUAL(timeline2.getSamplesPerBeat(120.0), srate2 / 2);

		BOOST_CHECK_EQUAL(timeline1.getSamplesPerBeat(60.0), srate1);
		BOOST_CHECK_EQUAL(timeline2.getSamplesPerBeat(60.0), srate2);

		BOOST_CHECK_EQUAL(timeline1.getSamplesPerBeat(1.0), srate1 * 60);
		BOOST_CHECK_EQUAL(timeline2.getSamplesPerBeat(1.0), srate2 * 60);

		BOOST_CHECK_EQUAL(timeline1.getSamplesPerBeat(500.0), (srate1 / 500.0) * 60.0);
		BOOST_CHECK_EQUAL(timeline2.getSamplesPerBeat(500.0), (srate2 / 500.0) * 60.0);

		BOOST_CHECK_THROW(timeline1.getSamplesPerBeat(0), InvalidArgumentException);
		BOOST_CHECK_THROW(timeline1.getSamplesPerBeat(-1000), InvalidArgumentException);
		BOOST_CHECK_THROW(timeline1.getSamplesPerBeat(501), InvalidArgumentException);
		BOOST_CHECK_THROW(timeline1.getSamplesPerBeat(1000), InvalidArgumentException);
	}

BOOST_AUTO_TEST_SUITE_END();
