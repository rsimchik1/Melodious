#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "../Source/Timeline.h"
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

BOOST_AUTO_TEST_SUITE_END();
