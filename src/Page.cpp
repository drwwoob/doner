#include "Page.h"

#define STB_IMAGE_IMPLEMENTATION
#include "data.h"
#include "../other Support/stb_image.h"

Page::Page() {
	
}

Page::Page(int page_id) {
	pageId = page_id;
}

Page::Page(int page_id, std::string page_data)
{
	pageId = page_id;

	// page_data should look like
	// backgroundName{spirit1##spirit2##spirit3##}{textbox1##textbox2##}

	auto pos = page_data.find_first_of('{');
	backgroundName = page_data.substr(0, pos);
	//auto backBrac = page_data.find_first_of('}', frontBrac);

	pos++;
	auto start = pos; // start of spirits
	bool inGroup = true;
	auto end = pos;
	std::string str;

	// get the spirits data string
	while(inGroup) {
		if(page_data.at(pos) == '}') { // find the first "}" without / infront
			inGroup = false;
			end = pos;
		}
		if (page_data.at(pos) == '/') { // to skip what comes after '/'
			pos += 1;
		}
		pos++;
		//str = page_data.substr(start, pos);
	}

	auto spiritsData = page_data.substr(start, end - start);
	auto s_start = 0;
	auto s_end = spiritsData.find("##") + 2;

	int para = 0;
	std::string seperateData[6]; // strings for each parameter


	for (int i = 0; i < spiritsData.size(); i++) {
		switch (spiritsData.at(i)) {
		case ('/'):
			i++;
			seperateData[para] += spiritsData.at(i);
			break;
		case('#'):
			para++;
			break;
		default:
			seperateData[para] += spiritsData.at(i);
			break;
		}
		if (para == 7) {
			spirits.emplace_back(seperateData[0], seperateData[1],
				std::stof(seperateData[2]), std::stof(seperateData[3]),
				std::stof(seperateData[4]), std::stof(seperateData[5]));
			for (int s_i = 0; s_i < 6; s_i++) {
				seperateData[s_i].clear();
			}
			para = 0;
		}
	}


	//inGroup = true;
	auto textData = page_data.substr(end + 2, page_data.size() - 4 - end);
	s_start = end + 2;
	para = 0;
	std::string seperateTextData[10];
	for (int i = 0; i < textData.size(); i++) {
		switch (textData.at(i)) {
		case ('/'):
			i++;
			seperateTextData[para] += textData.at(i);
			break;
		case('#'):
			para++;
			break;
		default:
			seperateTextData[para] += textData.at(i);
			break;
		}
		if (para == 10) {
			textboxs.emplace_back(seperateTextData);
			for(int t_i = 0; t_i < 10; t_i++) {
				seperateTextData[t_i].clear();
			}
			para = 0;
		}
	}
	//	}
	//}
}

void Page::visualizePage(HWND hWnd, HBITMAP g_hBackgroundBitmap, std::string file_path) {
	// ----------------------------- all commented for later show
	//auto backgroundPath = file_path.append(backgroundName);
	////g_hBackgroundBitmap = (HBITMAP)LoadImage(NULL, std::wstring(backgroundPath.begin(), backgroundPath.end()).c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	//g_hBackgroundBitmap = (HBITMAP)LoadImage(NULL, L"C:\\Users\\14631\\OneDrive\\Desktop\\DT\\New Folder\\drwwoob\\doner\\projects storage\\defaultBackrgound.jpg", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	//if (g_hBackgroundBitmap == NULL) {
	//	MessageBox(hWnd, L"Failed to load background image!\n", L"Error", MB_OK | MB_ICONERROR);
	//}
}

void Page::visualizePage2(Gdiplus::Bitmap* background_path, PWSTR path) {

	//size_t size = mbstowcs(nullptr, backgroundName.c_str(), 0);
	//if (size == static_cast<size_t>(-1)) {
	//	// Error handling for conversion failure
	//	
	//}

	//// Allocate memory for wchar_t string
	//wchar_t* wideString = new wchar_t[size + 1]; // +1 for null terminator

	//// Convert std::string to wchar_t string
	//mbstowcs(wideString, backgroundName.c_str(), size + 1);

	//background_path = *wideString;

	//delete[] wideString;

	}


void Page::visualizePage3(ID3D11Device* g_pd3dDevice, ImVec2 window_size, std::string file_path_str, std::vector<texture>* textureList) {
	auto back_path = file_path_str + backgroundName;

	showBackGround(back_path, window_size, g_pd3dDevice, textureList->at(0).t, &textureList->at(0).w, &textureList->at(0).h);
	for (int i = 0; i < spirits.size(); i++) {
		showSpirit(file_path_str, spirits.at(i), window_size, g_pd3dDevice, &textureList->at(i + 1));
	}

	//pmax for ImGui::GetWindowContentRegionMax()

	//ImGui::GetBackgroundDrawList()->AddText(ImVec2(500, 500), ImColor(1,1,1), "HUH?");

	for(auto textbox : textboxs) {
		showTextbox(textbox, window_size);
	}
}

void Page::showBackGround(std::string file_name, ImVec2 windowSize, ID3D11Device* g_pd3dDevice, ID3D11ShaderResourceView* back_texture, int *back_w, int *back_h) {
	bool ret = LoadTextureFromFile(file_name.c_str(), &back_texture, back_w, back_h, g_pd3dDevice);
	if(!ret) {
		// a popup window saying no background picture found
	}

	ImGui::GetBackgroundDrawList()->AddImage((void*)back_texture, ImVec2(0, 0),
		windowSize, ImVec2(0, 0), ImVec2(1, 1));
}

Spirit* Page::getRealSpirits(int id)
{
	return &spirits.at(id);
}

Textbox* Page::getRealTextbox(int id)
{
	return &textboxs.at(id);
}

void Page::setFont(ImFont* font_given)
{
	for(int i = 0; i < textboxs.size(); i++) {
		textboxs.at(i).changeFont(font_given);
	}
}

void Page::showSpirit(std::string file_path, Spirit spirit, ImVec2 window_size, ID3D11Device* g_pd3dDevice, texture* texture) {
	//int my_image_width = 0;
	//int my_image_height = 0;
	//ID3D11ShaderResourceView* my_texture = NULL;

	auto spiritPathName = file_path + spirit.fileName();

	bool ret = LoadTextureFromFile(spiritPathName.c_str(), &texture->t, &texture->w, &texture->h, g_pd3dDevice);
	if(!ret) {
		// error popup for not finding spirit
	}
	auto imgSize = spirit.getSize(window_size.x, window_size.y);
	auto topLeft = spirit.getPosition(window_size.x, window_size.y);

	// ---------------------to change---------------------
	// im thinking the uv for here can change so that the whole picture does not to be added,
	// but only the part inside the window
	ImGui::GetBackgroundDrawList()->AddImage((void*)texture->t, topLeft,
		ImVec2(topLeft.x + imgSize.x, topLeft.y + imgSize.y),
		ImVec2(0, 0), ImVec2(1, 1));

}

void Page::showTextbox(Textbox textbox, ImVec2 window_size)
{
	ImGui::GetBackgroundDrawList()->AddText(textbox.font, textbox.fontSize,
		ImVec2(textbox.positionRatio.x * window_size.x, textbox.positionRatio.y * window_size.y),
		textbox.color, textbox.content.c_str());
	//ImGui::GetBackgroundDrawList()->AddText(ImVec2(textbox.positionRatio.x * window_size.x, textbox.positionRatio.y * window_size.y),
	//	textbox.color, textbox.content.c_str());
}

std::string Page::exportInString()
{
	std::string encrypt = "[";

	// add background name
	encrypt.append(backgroundName);

	// add spirits
	encrypt.append("{");
	for(auto spirit : spirits) {
		encrypt.append(spirit.toString());
	}
	encrypt.append("}");

	// add textboxs;
	encrypt.append("{");
	for (auto textbox : textboxs) {
		encrypt.append(textbox.encrypt());
		//encrypt.append(textbox);
	}
	encrypt.append("}");
	

	// ending this page
	encrypt.append("]");
	return encrypt;
}

// helper function from imgui_example
bool Page::LoadTextureFromFile(const char* filename, ID3D11ShaderResourceView** out_srv, int* out_width, int* out_height, ID3D11Device* g_pd3dDevice)
{
	 //Load from disk into a raw RGBA buffer
	int image_width = 0;
	int image_height = 0;
	unsigned char* image_data = stbi_load(filename, &image_width, &image_height, NULL, 4);
	if (image_data == NULL)
		return false;

	 //Create texture
	D3D11_TEXTURE2D_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.Width = image_width;
	desc.Height = image_height;
	desc.MipLevels = 1;
	desc.ArraySize = 1;
	desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.SampleDesc.Count = 1;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	desc.CPUAccessFlags = 0;

	ID3D11Texture2D* pTexture = NULL;
	D3D11_SUBRESOURCE_DATA subResource;
	subResource.pSysMem = image_data;
	subResource.SysMemPitch = desc.Width * 4;
	subResource.SysMemSlicePitch = 0;
	g_pd3dDevice->CreateTexture2D(&desc, &subResource, &pTexture);

	 //Create texture view
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
	ZeroMemory(&srvDesc, sizeof(srvDesc));
	srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipLevels = desc.MipLevels;
	srvDesc.Texture2D.MostDetailedMip = 0;
	g_pd3dDevice->CreateShaderResourceView(pTexture, &srvDesc, out_srv);
	pTexture->Release();

	*out_width = image_width;
	*out_height = image_height;
	stbi_image_free(image_data);

	return true;
}


//
//void Page::visualizePage()
//{
//	Tools::setBackground(backgroundName);
//}
//
//std::vector<std::string> Page::exportInString() {
//
//}
