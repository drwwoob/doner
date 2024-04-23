#pragma once

#include <string>
#include <vector>
#include "Spirit.h"
#include "Tools.h"
#include <windows.h>
#include <gdiplus.h>
#pragma comment (lib,"Gdiplus.lib")

#include <codecvt>
#include <locale>

class Page {
public:
	std::vector<Spirit> spirits;
	std::vector<std::string> textboxs;
	// std::vector<std::string> textboxs settings;
	std::string	backgroundName;
	int pageId;
	Page();
	Page(int page_id);
	Page(int page_id, std::string page_data);
	//Page(int page_id, std::vector<std::string> spirits_vec, std::vector<std::string> textboxs_vec);
	void visualizePage(HWND hWnd, HBITMAP g_hBackgroundBitmap, std::string file_path);
	void visualizePage2(Gdiplus::Bitmap* background_path, PWSTR path);
	void visualizePage3(ID3D11Device* g_pd3dDevice, ImVec2 windowSize, std::string file_path_str);
	std::string exportInString();	// putting all the information in this page into a string
	static void showBackGround(std::string file_name, ImVec2 windowSize, ID3D11Device* g_pd3dDevice);
	/* in the format of
	[backgroundName{spirit1##spirit2##spirit3##}{textbox1##textbox2##}][backgroundName{spirit1##spirit2##spirit3##}{textbox1##textbox2##}]
	*/

	//pageID[backgroundName{spirit1##spirit2##spirit3##}{textbox1##textbox2##}]

private:
	static bool LoadTextureFromFile(const char* filename, ID3D11ShaderResourceView** out_srv, int* out_width, int* out_height, ID3D11Device* g_pd3dDevice);
	static std::string wordEncrypt(std::string word);
	/*exceptions:
	 *	# -> /#
	 *	/ -> //
	 *	{ -> /{
	 *	} -> /}
	*/
};
//
//class Spirit{
//	
//};
//
//class Textbox{
//	
//};