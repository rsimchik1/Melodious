#pragma once
#include <string>

/**
 * Interface for basic file access.
 */
class File
{
public:
	/**
	 * Instantiate the File subclass that's appropriate for the given file
	 * extension.
	 *
	 * @throw FileAccessException If the path cannot be accessed.
	 * @throw FileFormatException If the file extension is not supported.
	 * @param path The path of the new file.
	 * @return The newly created File.
	 */
	static File* createFile(std::string path);
	
	/**
	 * Find out whether the given path/file exists.
	 *
	 * @param path The path to search.
	 * @return true if the path exists, false otherwise.
	 */
	static bool pathExists(std::string path);

	File(std::string path);

	/**
	 * Get the path of this file.
	 *
	 * @return The path of this file.
	 */
	std::string getPath();
	
	/**
	 * Open this file for reading and writing.
	 *
	 * @throw FileAccessException If the file is already open.
	 */
	virtual void open() = 0;

	/**
	 * Close this file, allowing other processes to access it.
	 */
	virtual void close() = 0;

	/**
	 * Check whether this file is currently open.
	 *
	 * @return true if the file is open, false otherwise.
	 */
	virtual bool isOpen() = 0;

	/**
	 * Create this file's path on disk.
	 *
	 * @throw FileAccessException If this path already exists or cannot be
	 * created.
	 */
	virtual void createOnDisk() = 0;

	/**
	 * Delete this file's path on disk.
	 *
	 * @throw FileAccessException If this path does not exist or cannot be
	 * deleted.
	 */
	virtual void deleteFromDisk() = 0;
private:
	std::string path;
};
