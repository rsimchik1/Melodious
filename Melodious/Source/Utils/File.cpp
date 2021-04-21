#include "File.h"
#include <filesystem>
#include <sys/stat.h>

#include "AudioFile.h"
#include "../Exceptions/InvalidArgumentException.h"

File* File::createFile(std::string path)
{
	auto extension = std::filesystem::path(path).extension();
	if (AudioFile::isExtensionValid(extension.string()))
	{
		return new AudioFile(path);
	}
	throw InvalidArgumentException();
}

bool File::pathExists(std::string path)
{
	struct stat buffer;
	return stat(path.c_str(), &buffer) == 0;
}

std::string File::getPath()
{
	return path;
}

File::File(std::string path)
{
	this->path = path;
}
