#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include "../Source/Channel.h"
#include "../Source/NodeChannel.h"
#include "../Source/LeafChannel.h"
#include "../Source/Exceptions/InvalidChannelTreeException.h"

BOOST_AUTO_TEST_SUITE(ChannelTest);

BOOST_AUTO_TEST_CASE(ChannelConstructorsTest)
{
	auto validParent = NodeChannel();
	auto invalidParent = LeafChannel();
	BOOST_CHECK(validParent.getParent() == nullptr);
	BOOST_CHECK(invalidParent.getParent() == nullptr);

	auto validChild1 = LeafChannel(&validParent);
	auto validChild2 = NodeChannel(&validParent);
	BOOST_CHECK(validChild1.getParent() == &validParent);
	BOOST_CHECK(validParent.hasChild(&validChild1));
	BOOST_CHECK(validChild2.getParent() == &validParent);
	BOOST_CHECK(validParent.hasChild(&validChild2));

	LeafChannel invalidChild1;
	NodeChannel invalidChild2;
	BOOST_CHECK_THROW(invalidChild1 = LeafChannel(&invalidParent), 
		InvalidChannelTreeException);
	BOOST_CHECK_THROW(invalidChild2 = NodeChannel(&invalidParent),
		InvalidChannelTreeException);
	BOOST_CHECK(!invalidChild1.hasParent());
	BOOST_CHECK(!validParent.hasChild(&invalidChild1));
	BOOST_CHECK(!invalidChild2.hasParent());
	BOOST_CHECK(!validParent.hasChild(&invalidChild2));
}

BOOST_AUTO_TEST_CASE(ChannelParentChildTest)
{
	// lots of duplication - making sure everything is updated correctly
	auto validParent = NodeChannel();
	auto invalidParent = LeafChannel();
	BOOST_CHECK(validParent.getParent() == nullptr);
	BOOST_CHECK(invalidParent.getParent() == nullptr);

	auto validChild1 = LeafChannel();
	validChild1.setParent(&validParent);
	auto validChild2 = NodeChannel();
	validChild2.setParent(&validParent);
	BOOST_CHECK(validChild1.hasParent());
	BOOST_CHECK(validChild1.getParent() == &validParent);
	BOOST_CHECK(validParent.hasChild(&validChild1));
	BOOST_CHECK(validChild2.hasParent());
	BOOST_CHECK(validChild2.getParent() == &validParent);
	BOOST_CHECK(validParent.hasChild(&validChild2));

	LeafChannel invalidChild1;
	NodeChannel invalidChild2;
	BOOST_CHECK_THROW(invalidChild1.setParent(&invalidParent),
		InvalidChannelTreeException);
	BOOST_CHECK_THROW(invalidChild2.setParent(&invalidParent),
		InvalidChannelTreeException);
	BOOST_CHECK(!invalidChild1.hasParent());
	BOOST_CHECK(invalidChild1.getParent() == nullptr);
	BOOST_CHECK(!validParent.hasChild(&invalidChild1));
	BOOST_CHECK(!invalidChild2.hasParent());
	BOOST_CHECK(invalidChild2.getParent() == nullptr);
	BOOST_CHECK(!validParent.hasChild(&invalidChild2));
	
	BOOST_CHECK_THROW(validParent.setParent(&validParent),
		InvalidChannelTreeException);
	BOOST_CHECK(validParent.getParent() != &validParent);
	BOOST_CHECK(!validParent.hasChild(&validParent));

	validChild1.removeParent();
	BOOST_CHECK(!validChild1.hasParent());
	BOOST_CHECK(validChild1.getParent() == nullptr);
	BOOST_CHECK(!validParent.hasChild(&validChild1));

	auto validParent2 = NodeChannel(&validParent);
	BOOST_CHECK(validParent2.hasParent());
	BOOST_CHECK(validParent2.getParent() == &validParent);
	BOOST_CHECK(validParent.hasChild(&validParent2));
	validChild2.setParent(&validParent2);
	BOOST_CHECK(validChild2.hasParent());
	BOOST_CHECK(validChild2.getParent() == &validParent2);
	BOOST_CHECK(validParent2.hasChild(&validChild2));
	BOOST_CHECK(!validParent.hasChild(&validChild2));
	BOOST_CHECK_THROW(validParent.setParent(&validParent2), 
		InvalidChannelTreeException);
}

BOOST_AUTO_TEST_CASE(ChannelProcessFramesTest)
{
	const int numToProcess = 512;
	auto testTimeline = Timeline();
	auto rootNode = NodeChannel();
	auto bufferOut = rootNode.processFrames(numToProcess, testTimeline);
	
	BOOST_CHECK_EQUAL(bufferOut.getNumFrames(), numToProcess);
	for (auto i = 0; i < numToProcess; i++)
		for (auto j = 0; j < bufferOut.getNumChannels(); j++)
			BOOST_CHECK_EQUAL(bufferOut.readSampleAt(i, j), 0.0f);

	auto interiorNode = NodeChannel(&rootNode);
	auto leafNode = LeafChannel(&interiorNode);
	bufferOut = rootNode.processFrames(numToProcess, testTimeline);

	BOOST_CHECK_EQUAL(bufferOut.getNumFrames(), numToProcess);
	for (auto i = 0; i < numToProcess; i++)
		for (auto j = 0; j < bufferOut.getNumChannels(); j++)
			BOOST_CHECK_EQUAL(bufferOut.readSampleAt(i, j), 0.0f);

	bufferOut = leafNode.processFrames(numToProcess, testTimeline);

	BOOST_CHECK_EQUAL(bufferOut.getNumFrames(), numToProcess);
	for (auto i = 0; i < numToProcess; i++)
		for (auto j = 0; j < bufferOut.getNumChannels(); j++)
			BOOST_CHECK_EQUAL(bufferOut.readSampleAt(i, j), 0.0f);
}

BOOST_AUTO_TEST_SUITE_END();