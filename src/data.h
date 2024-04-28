#pragma once

#include <map>
#include <sherrors.h>

#include "Page.h"
#include "Tools.h"
//#include "shobjidl_core.h"

class data
{
public:
	data();
	data(std::string file_path, ImGuiIO& io);		// creating a blank file
	void newFile(bool* start_visual);
	void openFile(bool* start_visual);	// reading a file
	void openDemo(bool* start_visual);	// open the demo file
	//void openFile(std::string path);
	Page* getPage(int page_id);	// get the information of a page (decrypt)
	int leaveAt = 0;	// the page that the user left at last time
	void visualizeData(HWND hWnd, HBITMAP background_path, int page_id = 0);
	void visualizeData3(ID3D11Device* g_pd3dDevice, ImVec2 windowSize,std::vector<texture>* textureList, int page_id = 0);
	void visualizeData2();
	inline std::string filedata() { return fileData; };
	void save();

private:
	ImGuiIO& ioLocal;
	std::vector<Page> pages;	// a file includes a collection of pages
	std::string fileName;
	std::string fileData;
	PWSTR pszFileName;
	std::string demoPath;
	PWSTR filePath;
	std::string filePathStr;
	//std::map<Page> pages;

	// a hash table that stores all pages? or array?

	//void readData(std::string name);
	std::string encryptIntoFile(); // encrypt the current pages into text
	void decryptFile(std::string data_str);
	//from microsoft example code
	HRESULT basicFileOpen(bool findFile); // The tool to open common window
	//HRESULT CDialogEventHandler_CreateInstance(REFIID riid, void** ppv);
};