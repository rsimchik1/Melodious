#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "../Source/Model/ChannelMixer.h"
#include "../Source/Exceptions/IndexOutOfBoundsException.h"
#include "../Source/Exceptions/InvalidChannelTreeException.h"

BOOST_AUTO_TEST_SUITE(ChannelMixerTest);

	BOOST_AUTO_TEST_CASE(ChannelMixerConstructorTest)
	{
		const int numFrames = 1024;
		BOOST_TEST_CHECKPOINT("Create mixer.");
		auto testMixer = ChannelMixer();
		BOOST_CHECK_EQUAL(testMixer.getNumChannels(), 0);
		auto outBuffer = testMixer.processFrames(numFrames, Timeline());
		bool allZeros = true;
		BOOST_TEST_CHECKPOINT("Check output buffer.");
		for (auto i = 0; i < numFrames; i++)
			for (auto j = 0; j < outBuffer.getNumChannels(); j++)
				allZeros = allZeros && outBuffer.readSampleAt(i, j) == 0.0f;
		BOOST_CHECK(allZeros);
	}

	BOOST_AUTO_TEST_CASE(ChannelMixerAddRemoveTest)
	{
		auto testMixer = ChannelMixer();

		BOOST_TEST_CHECKPOINT("Test create...Channel() bounds.");
		BOOST_CHECK_THROW(testMixer.createAudioChannel(1), IndexOutOfBoundsException);
		BOOST_CHECK_THROW(testMixer.createBusChannel(1), IndexOutOfBoundsException);

		BOOST_TEST_CHECKPOINT("Create channels.");
		testMixer.createAudioChannel();
		BOOST_CHECK_EQUAL(testMixer.getNumChannels(), 1);
		testMixer.createBusChannel();
		BOOST_CHECK_EQUAL(testMixer.getNumChannels(), 2);
		testMixer.createAudioChannel(1);
		BOOST_CHECK_EQUAL(testMixer.getNumChannels(), 3);

		BOOST_TEST_CHECKPOINT("Move channels.");
		BOOST_CHECK_THROW(testMixer.moveChannelToIndex(-1, 1), IndexOutOfBoundsException);
		BOOST_CHECK_THROW(testMixer.moveChannelToIndex(1, 3), IndexOutOfBoundsException);
		testMixer.moveChannelToIndex(1, 2);
		BOOST_CHECK_EQUAL(testMixer.getNumChannels(), 3);
		
		BOOST_TEST_CHECKPOINT("Delete channels.");
		BOOST_CHECK_THROW(testMixer.deleteChannel(3), IndexOutOfBoundsException);
		BOOST_CHECK_THROW(testMixer.deleteChannel(-1), IndexOutOfBoundsException);
		testMixer.deleteChannel(0);
		BOOST_CHECK_EQUAL(testMixer.getNumChannels(), 2);
	}

	BOOST_AUTO_TEST_CASE(ChannelMixerConnectTest)
	{
		auto testMixer = ChannelMixer();
		testMixer.createAudioChannel();
		testMixer.createAudioChannel();
		testMixer.createAudioChannel();
		testMixer.createBusChannel();
		testMixer.createBusChannel();

		BOOST_TEST_CHECKPOINT("Connecting channels.");
		testMixer.connectChannels(2, 3);
		testMixer.connectChannels(3, 4);
		BOOST_CHECK_THROW(testMixer.connectChannels(4, 3), InvalidChannelTreeException);
		BOOST_CHECK_THROW(testMixer.connectChannels(1, 2), InvalidChannelTreeException);
		testMixer.connectToMasterOutput(2);
		testMixer.connectToMasterOutput(4);

		BOOST_TEST_CHECKPOINT("Checking bounds.");
		BOOST_CHECK_THROW(testMixer.connectChannels(-1, 0), IndexOutOfBoundsException);
		BOOST_CHECK_THROW(testMixer.connectChannels(0, 5), IndexOutOfBoundsException);
		BOOST_CHECK_THROW(testMixer.connectToMasterOutput(-1), IndexOutOfBoundsException);
		BOOST_CHECK_THROW(testMixer.connectToMasterOutput(5), IndexOutOfBoundsException);
	}

BOOST_AUTO_TEST_SUITE_END();