#pragma once

#include <map>
#include <sherrors.h>

#include "Page.h"
#include "Tools.h"
//#include "shobjidl_core.h"

class data
{
public:
	data(std::string file_path);		// creating a blank file
	void newFile();
	void openFile();	// reading a file
	void openDemo();	// open the demo file
	//void openFile(std::string path);
	Page getPage(int page_id);	// get the information of a page (decrypt)
	int leaveAt = 0;	// the page that the user left at last time

private:
	std::vector<Page> pages;	// a file includes a collection of pages
	std::string fileName;
	std::string fileData;
	PWSTR pszFileName;
	std::string demoPath;
	PWSTR filePath;
	//std::map<Page> pages;

	// a hash table that stores all pages? or array?

	//void readData(std::string name);
	std::string encryptIntoFile(); // encrypt the current pages into text
	void decryptFile(std::string data_str);
	//from microsoft example code
	HRESULT basicFileOpen(bool findFile); // The tool to open common window
	//HRESULT CDialogEventHandler_CreateInstance(REFIID riid, void** ppv);
};