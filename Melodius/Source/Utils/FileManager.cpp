#include "FileManager.h"

#include "../Exceptions/FileAccessException.h"
#include "../Exceptions/InvalidArgumentException.h"

FileManager::~FileManager()
{
	for (auto handle : invalidHandles)
		getFile(handle)->deleteFromDisk();

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
			unsigned int i = 1;
			while (File::pathExists(path + " (" + std::to_string(i) + ")"))
			{
				i++;
			}

			path = path + " (" + std::to_string(i) + ")";
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
		if (files[i]->getPath().compare(path) == 0)
			return i;
	}

	return -1;
}

File* FileManager::getFile(int handle)
{
	if (handle < 0 || handle >= files.size())
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
	if (invalidHandle < 0 || invalidHandle >= files.size())
		throw InvalidArgumentException();

	for (auto i = 0; i < files.size(); i++)
	{
		if (invalidHandles[i] == invalidHandle)
		{
			invalidHandles.erase(invalidHandles.begin() + i);
			i--; // account for shifting elements
		}
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

