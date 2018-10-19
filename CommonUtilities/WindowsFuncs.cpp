#include "stdafx.h"
#include "WindowsFuncs.h"
#include "shlobj.h"
#include "shobjidl.h"
#include <atlbase.h>
#include "Converters.h"
#include <Windows.h>
std::string CU::SaveFile()
{
	struct COMDLG_FILTERSPEC
	{
		LPCWSTR pszName;
		LPCWSTR pszSpec;
	};


	HRESULT hr;
	CComPtr<IFileSaveDialog> pDlg;

	hr = pDlg.CoCreateInstance ( __uuidof(FileSaveDialog) );

	if ( FAILED(hr) )

		pDlg->SetTitle ( L"A Single-Selection Dialog" );
	pDlg->SetDefaultExtension(L"par");
	hr = pDlg->Show ( GetActiveWindow() );
	

	std::string returnString;
	if ( SUCCEEDED(hr) )
	{
		CComPtr<IShellItem> pItem;

		hr = pDlg->GetResult ( &pItem );

		if ( SUCCEEDED(hr) )
		{
			LPWSTR pwsz = NULL;

			hr = pItem->GetDisplayName ( SIGDN_FILESYSPATH, &pwsz );

			if ( SUCCEEDED(hr) )
			{
				std::wstring tempSt = pwsz; 
				returnString = Convert::WStringToString(tempSt);
				CoTaskMemFree ( pwsz );
			}
		}
	}
	return returnString;

}
std::string CU::BrowseFile()
{
	struct COMDLG_FILTERSPEC
	{
	  LPCWSTR pszName;
	  LPCWSTR pszSpec;
	};

	HRESULT hr;
	CComPtr<IFileOpenDialog> pDlg;
	/*COMDLG_FILTERSPEC aFileTypes[] = {
		{ L"Dae files", L"*.dae" }, 
		{ L"All files", L"*.*" }
	};*/

	// Create the file-open dialog COM object.
	hr = pDlg.CoCreateInstance ( __uuidof(FileOpenDialog) );

	if ( FAILED(hr) )
		//return true;

	// Set the dialog's caption text and the available file types.
	// NOTE: Error handling omitted here for clarity.
	//pDlg->SetFileTypes ( _countof(aFileTypes), &aFileTypes[0] );
	pDlg->SetTitle ( L"A Single-Selection Dialog" );
	//return true;

	// Show the dialog.
	hr = pDlg->Show ( NULL );

	std::string returnString;
	// If the user chose a file, show a message box with the
	// full path to the file.
	if ( SUCCEEDED(hr) )
	{
		CComPtr<IShellItem> pItem;

		hr = pDlg->GetResult ( &pItem );

		if ( SUCCEEDED(hr) )
		{
			LPWSTR pwsz = NULL;

			hr = pItem->GetDisplayName ( SIGDN_FILESYSPATH, &pwsz );
			
			if ( SUCCEEDED(hr) )
			{
				std::wstring tempSt = pwsz; 
				returnString = Convert::WStringToString(tempSt);
				CoTaskMemFree ( pwsz );
			}
		}
	}
	return returnString;
}

std::string CU::BrowseFolder()
{
	std::string folderpath = "fail";
    const char* szCaption = NULL;
    HWND hOwner = NULL;
   // The BROWSEINFO struct tells the shell 
   // how it should display the dialog.
   BROWSEINFO bi;
   memset(&bi, 0, sizeof(bi));

   bi.ulFlags   = BIF_USENEWUI;
   bi.hwndOwner = hOwner;
   bi.lpszTitle = szCaption;

   // must call this if using BIF_USENEWUI
   ::OleInitialize(NULL);

   // Show the dialog and get the itemIDList for the 
   // selected folder.
   LPITEMIDLIST pIDL = SHBrowseForFolder(&bi);

   if(pIDL != NULL)
   {
      // Create a buffer to store the path, then 
      // get the path.
      char buffer[_MAX_PATH] = {'\0'};
      if(::SHGetPathFromIDList(pIDL, buffer) != 0)
      {
         // Set the string value.
         folderpath = buffer;
        
      }

      // free the item id list
      CoTaskMemFree(pIDL);
   }

   ::OleUninitialize();
   return folderpath;
}


CU::GrowingArray<std::string> CommonUtilities::GetFilesInFolder( std::string aFolderPath, std::string aFileName )
{
	CU::GrowingArray<std::string> returnArray;
	returnArray.Init(100, 100);

	HANDLE handle;
	WIN32_FIND_DATA info;

	std::string allFiles = aFolderPath + "*."+ aFileName + "*";
	handle = FindFirstFile(allFiles.c_str(), &info);
	if (handle != INVALID_HANDLE_VALUE)
	{

		do
		{
			returnArray.Add(info.cFileName);

		} while (FindNextFile(handle, &info));
		FindClose(handle);
	}
	return returnArray;
}

CU::GrowingArray<std::string> CommonUtilities::GetFoldersInFolder(std::string aFolderPath)
{
	CU::GrowingArray<std::string> returnArray;
	returnArray.Init(100, 100);

	HANDLE handle;
	WIN32_FIND_DATA info;
	std::string allFolders = aFolderPath + "*";
	handle = FindFirstFile(allFolders.c_str(), &info);
	if (handle != INVALID_HANDLE_VALUE)
	{
		if (info.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			do
			{
				returnArray.Add(info.cFileName);

			} while (FindNextFile(handle, &info));
			FindClose(handle);
		}
	}

	return returnArray;

}