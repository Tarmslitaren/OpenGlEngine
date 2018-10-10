#pragma once
#ifndef WINDOWS_FUNCS_HEADER
#define WINDOWS_FUNCS_HEADER

#include <string>

namespace CommonUtilities
{
	struct Flist
	{
		int             num_entries;
		int             max_entries;
		WIN32_FIND_DATA *files;
	};

	std::string SaveFile();
	std::string BrowseFile();
	std::string BrowseFolder();
	CU::GrowingArray<std::string> GetFilesInFolder(std::string aFolderPath, std::string aFileName);
	CU::GrowingArray<std::string> GetFoldersInFolder(std::string aFolderPath);
};
#endif