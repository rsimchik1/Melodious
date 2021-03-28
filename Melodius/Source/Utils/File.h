#pragma once
#include <atomic>
#include <string>

/**
 * Interface for basic file access.
 */
class File
{
public:
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
};
