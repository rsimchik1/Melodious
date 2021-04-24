#include "FileManager.h"

#include <filesystem>

#include "../Exceptions/FileAccessException.h"
#include "../Exceptions/InvalidArgumentException.h"

FileManager::~FileManager()
{
	for (auto handle : invalidHandles)
		files[handle]->deleteFromDisk();

	for (auto *file : files)
		delete file;
}

bool FileManager::hasFile(std::string path)
{
	return getFileHandle(path) >= 0;
}

int FileManager::createNewFile(std::string path, bool renameIfTaken)
{
	File* newFile = nullptr;
	
	if (hasFile(path) && !renameIfTaken)
		throw InvalidArgumentException();
	
	if (File::pathExists(path))
	{
		if (renameIfTaken)
		{
			auto tempPath = std::filesystem::path(path);
			auto extension = tempPath.extension();
			tempPath.replace_extension();
			std::string newPath;
			unsigned int i = 1;
			while (File::pathExists(newPath = tempPath.generic_string() +
									" (" + std::to_string(i) + ")" + 
									extension.generic_string()))
			{
				i++;
			}

			path = newPath;
		}
		else throw FileAccessException();
	}

	try
	{
		newFile = File::createFile(path);
		newFile->createOnDisk();
		files.push_back(newFile);
		return files.size() - 1; // newly created index == file handle
	}
	catch (std::exception& e)
	{
		if (newFile) delete newFile;
		throw e;
	}
}

int FileManager::addExistingFile(std::string path)
{
	if (hasFile(path))
		throw InvalidArgumentException();

	if (!File::pathExists(path))
		throw FileAccessException();

	try
	{
		auto existingFile = File::createFile(path);
		files.push_back(existingFile);
		return files.size() - 1;
	}
	catch (std::exception& e) { throw e; }
}

int FileManager::getFileHandle(std::string path)
{
	for (auto i = 0; i < files.size(); i++)
	{
		auto path1 = std::filesystem::path(files[i]->getPath()).lexically_normal();
		auto path2 = std::filesystem::path(path).lexically_normal();
		if (path1.compare(path2) == 0)
			return i;
	}

	return -1;
}

File* FileManager::getFile(int handle)
{
	if (!isHandleValid(handle) || handle < 0 || handle >= files.size())
		throw InvalidArgumentException();

	return files[handle];
}

void FileManager::invalidateHandle(int handle)
{
	if (handle < 0 || handle >= files.size())
		throw InvalidArgumentException();
	
	if (isHandleValid(handle))
		invalidHandles.push_back(handle);
}

void FileManager::restoreInvalidHandle(int invalidHandle)
{
	if (isHandleValid(invalidHandle))
		throw InvalidArgumentException();

	auto i = invalidHandles.begin();
	while (i != invalidHandles.end())
	{
		if (*i == invalidHandle)
			i = invalidHandles.erase(i);
		else
			i++;
	}
}

bool FileManager::isHandleValid(int handle)
{
	if (handle < 0 || handle >= files.size())
		return false;

	for (auto invalidHandle : invalidHandles)
		if (invalidHandle == handle)
			return false;

	return true;
}

