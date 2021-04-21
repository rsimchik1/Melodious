#pragma once
#include <vector>
#include <string>

#include "File.h"

class FileManager
{
public:
	/**
	 * Delete this file manager and all File pointers associated with it. Also
	 * deletes all invalidated files from disk.
	 */
	~FileManager();
	
	/**
	 * Find out whether this FileManager is managing the file at the given path.
	 *
	 * @param path The path to search for.
	 * @return true if the file is found, false otherwise.
	 */
	bool hasFile(std::string path);

	/**
	 * Create a new file at the given path.
	 *
	 * @throw FileAccessException If the path cannot be accessed, or if the file
	 * exists and renameIfTaken is false.
	 * @throw FileFormatException If the file extension is not supported.
	 * @throw InvalidArgumentException If a file with the given path exists in
	 * this FileManager and renameIfTaken is false.
	 * @param path The full path of the new file.
	 * @param renameIfTaken If true, the path will be appended to make it unique
	 * if the given path already exists.
	 * @return The new file's handle, or -1 if it was not created.
	 */
	int createNewFile(std::string path, bool renameIfTaken = false);

	/**
	 * Add a file that already exists on disk.
	 *
	 * @throw FileAccessException If the path cannot be accessed, or if the file
	 * does not exist.
	 * @throw InvalidArgumentException If a file with the given path exists in
	 * this FileManager.
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
	 * "Soft delete" a file by marking its handle as invalid. Invalidated files
	 * will be properly deleted and removed from disk when the FileManager is
	 * deleted. (Files are not deleted during runtime to maintain undo/redo
	 * possibilities). If a handle is already invalidated, nothing changes.
	 *
	 * @throw InvalidArgumentException If the handle is not associated with a
	 * file.
	 * @param handle The handle to invalidate.
	 */
	void invalidateHandle(int handle);

	/**
	 * Restore a "soft deleted" file by marking its handle as valid. These files
	 * will no longer be removed from disk when this FileManager is deleted. If
	 * a handle is already valid, nothing changes.
	 *
	 * @throw InvalidArgumentException If the handle is not associated with a
	 * file.
	 * @param invalidHandle The handle to re-validate.
	 */
	void restoreInvalidHandle(int invalidHandle);
private:
	std::vector<File *> files;
	std::vector<int> invalidHandles;

	bool isHandleValid(int handle);
};
