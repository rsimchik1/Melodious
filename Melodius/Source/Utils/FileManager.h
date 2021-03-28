#pragma once
#include <map>
#include <string>

#include "../Model/File.h"

class FileManager
{
public:
	/**
	 * Return the global FileManager instance.
	 *
	 * @return The global FileManager reference.
	 */
	static FileManager &getInstance();

	/**
	 * Create a new file at the given path.
	 *
	 * @param path The full path of the new file.
	 * @param renameIfTaken If true, file names will be appended when trying to
	 * create two or more files with the same name. If false, the new file will
	 * not be created in that situation.
	 * @return The new file's handle, or -1 if it was not created.
	 */
	int createNewFile(std::string path, bool renameIfTaken = false);

	/**
	 * Add a file that already exists on disk.
	 *
	 * @param path The full path of the existing file.
	 * @return The existing file's handle, or -1 if it was not found.
	 */
	int addExistingFile(std::string path);

	/**
	 * Get the handle of the file at the given path.
	 *
	 * @param path The path of the file to find.
	 * @return The file's handle, or -1 if the file is not owned by this
	 * FileManager.
	 */
	int getFileHandle(std::string path);

	/**
	 * Get the File object associated with the given handle.
	 *
	 * @throw InvalidArgumentException If the handle is not associated with a
	 * file.
	 * @param handle The handle of the File to retrieve.
	 * @return The file object associated with the handle.
	 */
	File* getFile(int handle);

	/**
	 * Delete a file from disk. Also deletes the respective File object and
	 * invalidates its handle.
	 *
	 * @throw InvalidArgumentException If the handle is not associated with a
	 * file.
	 * @param handle The handle of the File to delete.
	 */
	void deleteFile(int handle);

	// Deleted copy constructors to prevent unwanted instances.
	FileManager(FileManager const& toCopy) = delete;
	void operator=(FileManager const& toCopy) = delete;
private:
	std::map<int, File*> files;
		FileManager();
};
