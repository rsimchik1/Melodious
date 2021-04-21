#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <filesystem>
#include <string>

#include "../Source/Exceptions/FileAccessException.h"
#include "../Source/Exceptions/FileFormatException.h"
#include "../Source/Exceptions/InvalidArgumentException.h"
#include "../Source/Utils/FileManager.h"
#include "../Source/Utils/AudioFile.h"

BOOST_AUTO_TEST_SUITE(FileManagerTest);

const std::filesystem::path	TEST_DIR = std::filesystem::current_path();

	BOOST_AUTO_TEST_CASE(FileManagerCreateAddTest)
	{
		auto path1 = TEST_DIR.string() + "/manageTest1.wav";
		auto fileManager = FileManager();
		BOOST_CHECK_EQUAL(-1, fileManager.getFileHandle(path1));
		BOOST_CHECK_THROW(fileManager.getFile(0), InvalidArgumentException);
		int handle1 = INT_MAX;
		BOOST_CHECK_NO_THROW(handle1 = fileManager.createNewFile(path1));
		BOOST_CHECK_EQUAL(handle1, fileManager.getFileHandle(path1));
		File* file1 = nullptr;
		BOOST_CHECK_NO_THROW(file1 = fileManager.getFile(handle1));
		BOOST_CHECK_NE(nullptr, file1);

		auto path2 = TEST_DIR.string() + "/manageTest2.wav";
		auto extFile = AudioFile(path2);
		extFile.createOnDisk();
		int handle2 = INT_MAX;
		File* file2 = nullptr;

		auto path3 = TEST_DIR.string() + "/manageTest1 (1).wav";
		int handle3 = INT_MAX;
		File* file3 = nullptr;

		BOOST_CHECK_THROW(handle2 = fileManager.createNewFile(path2, false),
			FileAccessException);
		BOOST_CHECK_EQUAL(INT_MAX, handle2);
		BOOST_CHECK_THROW(handle3 = fileManager.createNewFile(path1, false),
			InvalidArgumentException);
		BOOST_CHECK_EQUAL(INT_MAX, handle3);

		BOOST_CHECK_THROW(fileManager.createNewFile(TEST_DIR.string() +
			"/manageTest1.bad"), FileFormatException);
		BOOST_CHECK_THROW(fileManager.addExistingFile("notReal"), FileAccessException);
		BOOST_CHECK_THROW(fileManager.addExistingFile(path1), FileAccessException);

		BOOST_CHECK_NO_THROW(handle2 = fileManager.addExistingFile(path2));
		BOOST_CHECK_EQUAL(handle2, fileManager.getFileHandle(path2));
		BOOST_CHECK_NO_THROW(file2 = fileManager.getFile(handle2));
		BOOST_CHECK_EQUAL(0, file2->getPath().compare(path2));

		BOOST_CHECK_NO_THROW(handle3 = fileManager.createNewFile(path1, true));
		BOOST_CHECK_EQUAL(handle3, fileManager.getFileHandle(path3));
		BOOST_CHECK_NO_THROW(file3 = fileManager.getFile(handle3));
		BOOST_CHECK_EQUAL(0, file3->getPath().compare(path3));

		BOOST_CHECK_THROW(fileManager.invalidateHandle(10), InvalidArgumentException);
		BOOST_CHECK_NO_THROW(fileManager.invalidateHandle(handle2));
		BOOST_CHECK_THROW(fileManager.getFile(handle2), InvalidArgumentException);
		BOOST_CHECK_NO_THROW(fileManager.invalidateHandle(handle2));

		BOOST_CHECK_NO_THROW(fileManager.restoreInvalidHandle(handle2));
		File* valid;
		BOOST_CHECK_NO_THROW(valid = fileManager.getFile(handle2));
		BOOST_CHECK_EQUAL(file2, valid);

		for (auto i = 0; i < 3; i++)
			fileManager.invalidateHandle(i);

		BOOST_CHECK_NO_THROW(delete &fileManager);
	}

BOOST_AUTO_TEST_SUITE_END();
