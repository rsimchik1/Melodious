#include "FileManager.h"

FileManager& FileManager::getInstance()
{
	static FileManager instance;
	return instance;
}

int FileManager::createNewFile(std::string path, bool renameIfTaken)
{
	return 0;
}

int FileManager::addExistingFile(std::string path)
{
	return 0;
}

int FileManager::getFileHandle(std::string path)
{
	return 0;
}

File* FileManager::getFile(int handle)
{
	return nullptr;
}

void FileManager::deleteFile(int handle)
{
}

FileManager::FileManager()
{
}
