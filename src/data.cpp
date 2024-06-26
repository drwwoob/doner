#include "data.h"

#include <fstream>
#include <windows.h>
#include <shobjidl.h> 

data::data(std::string file_path)
{
	// pop up a window to let the user choose a places to save
	// and let them put in the name for the file
	//QString myDir = QFileDialog::getExistingDirectory();

    // initiate demoPath
    filePathStr = file_path;
    demoPath = file_path.append("demo\\");

    // turn file_path into pwstr
	size_t size = file_path.length();
	wchar_t* buffer = new wchar_t[size + 1];
	MultiByteToWideChar(CP_ACP, 0, file_path.c_str(), size, buffer, size * sizeof(wchar_t));
	buffer[size] = 0;
	filePath = buffer;

	delete buffer;

	// create a blank page
	pages.emplace_back(0);

	// save this file with a blank page into the location the user choose
}

void data::newFile(bool* start_visual)
{
    basicFileOpen(false);
    pages = {Page(0)};
}

void data::openFile(bool* start_visual)
{
    basicFileOpen(true);
    decryptFile(fileData);
}

void data::openDemo(bool* start_visual) {
    std::ifstream demoFile(demoPath + "demo.txt");
    if (!demoFile.is_open()) {
        // error window popup
        //ImGui::Begin("Oops");
        //ImGui::OpenPopup("ladojf");
        //ImGui::End();
    }
    this->fileData = "";
    filePathStr = demoPath;
    fileName = "demo.txt";

    std::string str;
    while (std::getline(demoFile, str))
    //while(demoFile >> str)
    {
        fileData.append(str);
        fileData.append("\n");
    }
    pages.clear();
    decryptFile(fileData);
    
    *start_visual = true;
}

void data::visualizeData(HWND hWnd, HBITMAP background_path, int page_id) {
    pages.at(page_id).visualizePage(hWnd, background_path, filePathStr);
}

void data::visualizeData3(ID3D11Device* g_pd3dDevice, ImVec2 windowSize, std::vector<texture>* textureList, int page_id) {
    if(!pages.empty())
		pages.at(page_id).visualizePage3(g_pd3dDevice, windowSize, filePathStr, textureList);
    else {
	    // some popup
    }
}

void data::setFont(ImFont* font_given)
{
    font = font_given;
    //for (int i = 0; i < pages.size(); i++) {
    //    pages.at(i).setFont(font_given);
    //}
}


Page* data::getPage(int page_id) {
	return &pages.at(page_id);
}

std::string data::encryptIntoFile()
{
	std::string pagesInfo;

    for(auto page : pages) {
        pagesInfo.append(page.exportInString());
    }

    return pagesInfo;
}

void data::decryptFile(std::string data_str)
{
    int pos = 0;
    int start = 0;
    int pageID = 0;
    while(pos < data_str.size()) {
	    if(data_str.at(pos++) == '[') { // whether pos is '[', go to the next letter
            start = pos;
            while(data_str.at(pos) != ']') {
                if(data_str.at(pos) == '/') {
                    pos++;
                }
                pos++;
            }
            pages.emplace_back(pageID, data_str.substr(start, pos));
            auto test = data_str.substr(start, pos);
            pages.back().setFont(font);
            pageID++;
            pos++;
	    }
    }
}

void data::save() {
    std::ofstream file;
    //for testing
    auto path = filePathStr + fileName;
    auto data = encryptIntoFile();
    file.open(path.c_str());
    file << encryptIntoFile().c_str();
    file.close();

    //// Always center this window when appearing
    //ImVec2 center = ImGui::GetMainViewport()->GetCenter();
    //ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));

    //if (ImGui::Button("Save"))
	//ImGui::OpenPopup("save Modal window");


 //   if (ImGui::BeginPopupModal("save Modal window", NULL, ImGuiWindowFlags_AlwaysAutoResize))
 //   {
 //       ImGui::Text("All those beautiful files will be deleted.\nThis operation cannot be undone!");
 //       ImGui::Separator();

 //       //static int unused_i = 0;
 //       //ImGui::Combo("Combo", &unused_i, "Delete\0Delete harder\0");

 //       static bool dont_ask_me_next_time = false;
 //       ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, 0));
 //       ImGui::Checkbox("Don't ask me next time", &dont_ask_me_next_time);
 //       ImGui::PopStyleVar();

 //       if (ImGui::Button("OK", ImVec2(120, 0))) { ImGui::CloseCurrentPopup(); }
 //       ImGui::SetItemDefaultFocus();
 //       ImGui::SameLine();
 //       if (ImGui::Button("Cancel", ImVec2(120, 0))) { ImGui::CloseCurrentPopup(); }
 //       ImGui::EndPopup();
 //   }
 //   ImGui::OpenPopup("Saved");
 //   //ImGui::BeginPopupModal("Saved");
 //   
	//ImGui::Text("File have been saved!");
	//ImGui::Separator();
 //   if (ImGui::Button("Close"))
 //       ImGui::CloseCurrentPopup();

 //       //static int unused_i = 0;
 //       //ImGui::Combo("Combo", &unused_i, "Delete\0Delete harder\0");

	////if (ImGui::Button("OK", ImVec2(120, 0))) { ImGui::CloseCurrentPopup(); }
	////ImGui::SetItemDefaultFocus();
	//ImGui::EndPopup();
}

void data::addPage(int page_id)
{
    pages.emplace(pages.begin() + page_id, page_id);
}

void data::CopyPage(int page_id, Page page)
{
    for(int i = 0; i < page.textboxs.size(); i++) {
        page.textboxs.at(i).content = "Enter new text";
    }
    pages.insert(pages.begin() + page_id, page);
}

void data::deletePage(int page_id)
{
    pages.erase(pages.begin() + page_id);
}

//
//HRESULT data::basicFileOpen() {
//    IFileDialog* pfd = NULL;
//
//
//}


// from windows example
// https://learn.microsoft.com/en-us/windows/win32/learnwin32/example--the-open-dialog-box
HRESULT data::basicFileOpen(bool findFile) {
    HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED |
        COINIT_DISABLE_OLE1DDE);
    if (SUCCEEDED(hr))
    {
        IFileOpenDialog* pFileOpen;

        // Create the FileOpenDialog object.
        hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL,
            IID_IFileOpenDialog, reinterpret_cast<void**>(&pFileOpen));

        if (SUCCEEDED(hr))
        {
            // Show the Open dialog box.
            hr = pFileOpen->Show(NULL);

            // Get the file name from the dialog box.
            if (SUCCEEDED(hr))
            {
                IShellItem* pItem;
                hr = pFileOpen->GetResult(&pItem);
                if (SUCCEEDED(hr))
                {
                    hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &filePath);

                    // Display the file name to the user.
                    if (SUCCEEDED(hr))
                    {
                        MessageBoxW(NULL, filePath, L"File Path", MB_OK);
                    }
                    pItem->Release();
                }
            }
            pFileOpen->Release();
        }
        // too powerful
        CoUninitialize();
    }
    return hr;
}

//HRESULT basicFileOpen()
//{
//    // CoCreate the File Open Dialog object.
//    IFileDialog* pfd = NULL;
//    HRESULT hr = CoCreateInstance(CLSID_FileOpenDialog,
//        NULL,
//        CLSCTX_INPROC_SERVER,
//        IID_PPV_ARGS(&pfd));
//    if (SUCCEEDED(hr))
//    {
//        // Create an event handling object, and hook it up to the dialog.
//        IFileDialogEvents* pfde = NULL;
//        hr = CDialogEventHandler_CreateInstance(IID_PPV_ARGS(&pfde));
//        if (SUCCEEDED(hr))
//        {
//            // Hook up the event handler.
//            DWORD dwCookie;
//            hr = pfd->Advise(pfde, &dwCookie);
//            if (SUCCEEDED(hr))
//            {
//                // Set the options on the dialog.
//                DWORD dwFlags;
//
//                // Before setting, always get the options first in order 
//                // not to override existing options.
//                hr = pfd->GetOptions(&dwFlags);
//                if (SUCCEEDED(hr))
//                {
//                    // In this case, get shell items only for file system items.
//                    hr = pfd->SetOptions(dwFlags | FOS_FORCEFILESYSTEM);
//                    if (SUCCEEDED(hr))
//                    {
//                        // Set the file types to display only. 
//                        // Notice that this is a 1-based array.
//                        hr = pfd->SetFileTypes(ARRAYSIZE(c_rgSaveTypes), c_rgSaveTypes);
//                        if (SUCCEEDED(hr))
//                        {
//                            // Set the selected file type index to Word Docs for this example.
//                            hr = pfd->SetFileTypeIndex(INDEX_WORDDOC);
//                            if (SUCCEEDED(hr))
//                            {
//                                // Set the default extension to be ".doc" file.
//                                hr = pfd->SetDefaultExtension(L"doc;docx");
//                                if (SUCCEEDED(hr))
//                                {
//                                    // Show the dialog
//                                    hr = pfd->Show(NULL);
//                                    if (SUCCEEDED(hr))
//                                    {
//                                        // Obtain the result once the user clicks 
//                                        // the 'Open' button.
//                                        // The result is an IShellItem object.
//                                        IShellItem* psiResult;
//                                        hr = pfd->GetResult(&psiResult);
//                                        if (SUCCEEDED(hr))
//                                        {
//                                            // We are just going to print out the 
//                                            // name of the file for sample sake.
//                                            PWSTR pszFilePath = NULL;
//                                            hr = psiResult->GetDisplayName(SIGDN_FILESYSPATH,
//                                                &pszFilePath);
//                                            if (SUCCEEDED(hr))
//                                            {
//                                                TaskDialog(NULL,
//                                                    NULL,
//                                                    L"CommonFileDialogApp",
//                                                    pszFilePath,
//                                                    NULL,
//                                                    TDCBF_OK_BUTTON,
//                                                    TD_INFORMATION_ICON,
//                                                    NULL);
//                                                CoTaskMemFree(pszFilePath);
//                                            }
//                                            psiResult->Release();
//                                        }
//                                    }
//                                }
//                            }
//                        }
//                    }
//                }
//                // Unhook the event handler.
//                pfd->Unadvise(dwCookie);
//            }
//            pfde->Release();
//        }
//        pfd->Release();
//    }
//    return hr;
//}
//
//HRESULT CDialogEventHandler_CreateInstance(REFIID riid, void** ppv)
//{
//    *ppv = NULL;
//    CDialogEventHandler* pDialogEventHandler = new (std::nothrow) CDialogEventHandler();
//    HRESULT hr = pDialogEventHandler ? S_OK : E_OUTOFMEMORY;
//    if (SUCCEEDED(hr))
//    {
//        hr = pDialogEventHandler->QueryInterface(riid, ppv);
//        pDialogEventHandler->Release();
//    }
//    return hr;
//}
