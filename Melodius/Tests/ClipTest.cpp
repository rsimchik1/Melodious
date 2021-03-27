#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "../Source/Exceptions/InvalidArgumentException.h"
#include "../Source/Model/Clip.h"

BOOST_AUTO_TEST_SUITE(ClipTest);

	BOOST_AUTO_TEST_CASE(ClipStartEndTest)
	{
		auto clip = Clip();
		BOOST_CHECK_EQUAL(clip.getStartFrame(), 0);
		BOOST_CHECK_EQUAL(clip.getEndFrame(), 0);

		clip.setStartEndFrames(50, 1000);
		BOOST_CHECK_EQUAL(clip.getStartFrame(), 50);
		BOOST_CHECK_EQUAL(clip.getEndFrame(), 1000);

		BOOST_CHECK_THROW(clip.setStartEndFrames(50, 49), InvalidArgumentException);
	}

BOOST_AUTO_TEST_SUITE_END();
