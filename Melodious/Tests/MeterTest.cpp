#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "../Source/Exceptions/InvalidArgumentException.h"
#include "../Source/Model/Meter.h"

BOOST_AUTO_TEST_SUITE(MeterTest);

	BOOST_AUTO_TEST_CASE(MeterConstructorTest)
	{
		auto meter = Meter(3, 4);
		BOOST_CHECK_EQUAL(meter.getBeatsPerMeasure(), 3);
		BOOST_CHECK_EQUAL(meter.getBeatNoteType(), 4);

		meter = Meter(64, NoteType::SIXTY_FOURTH);
		BOOST_CHECK_EQUAL(meter.getBeatsPerMeasure(), 64);
		BOOST_CHECK_EQUAL(meter.getBeatNoteType(), 64);

		meter = Meter(1, 1);
		BOOST_CHECK_EQUAL(meter.getBeatsPerMeasure(), 1);
		BOOST_CHECK_EQUAL(meter.getBeatNoteType(), 1);
			
		BOOST_CHECK_THROW(Meter(0, 4), InvalidArgumentException);
		BOOST_CHECK_THROW(Meter(-1, 4), InvalidArgumentException);
		BOOST_CHECK_THROW(Meter(65, 4), InvalidArgumentException);

		BOOST_CHECK_THROW(Meter(4, 0), InvalidArgumentException);
		BOOST_CHECK_THROW(Meter(4, -1), InvalidArgumentException);
		BOOST_CHECK_THROW(Meter(4, 128), InvalidArgumentException);
		BOOST_CHECK_THROW(Meter(4, 3), InvalidArgumentException);
	}

BOOST_AUTO_TEST_SUITE_END();
