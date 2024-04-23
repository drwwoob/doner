#include "Page.h"

#define STB_IMAGE_IMPLEMENTATION
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

	// get the spirits
	while(inGroup) {
		if (page_data.at(pos) == '/') {
			pos += 1;
		}
		else if(page_data.at(pos) == '}') { // find the first "}" without / infront
			inGroup = false;
			spirits.emplace_back(page_data.substr(start, pos));
		}
		pos++;
	}
	inGroup = true;
	

	//for
	//if (data_str.at(pos) == '/') { // escaping
	//	pos++;
	//	switch (data_str.at(pos)) {

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


void Page::visualizePage3(ID3D11Device* g_pd3dDevice, ImVec2 windowSize, std::string file_path_str) {
	auto back_path = file_path_str + backgroundName;

	showBackGround(back_path, windowSize, g_pd3dDevice);

	////pmax for ImGui::GetWindowContentRegionMax()
}

void Page::showBackGround(std::string file_name, ImVec2 windowSize, ID3D11Device* g_pd3dDevice) {
	int my_image_width = 0;
	int my_image_height = 0;
	ID3D11ShaderResourceView* my_texture = NULL;

	bool ret = LoadTextureFromFile(file_name.c_str(), &my_texture, &my_image_width, &my_image_height, g_pd3dDevice);
	ImGui::GetBackgroundDrawList()->AddImage((void*)my_texture, ImVec2(0, 0),
		windowSize, ImVec2(0, 0), ImVec2(1, 1));


}


std::string Page::exportInString()
{
	std::string encrypt = "[";

	// add background name
	encrypt.append(backgroundName);

	// add spirits
	encrypt.append("{");
	for(auto spirit : spirits) {
		encrypt.append(wordEncrypt(spirit.toString()));
	}
	encrypt.append("}");

	// add textboxs;
	encrypt.append("{");
	for (auto textbox : textboxs) {
		encrypt.append(wordEncrypt(textbox));
	}
	encrypt.append("}");
	

	// ending this page
	encrypt.append("]");
	return encrypt;
}

std::string Page::wordEncrypt(std::string word) {
	std::string EncryptedWord;
	for (const auto letter : word) {
		switch(letter) {
		case '#':
			EncryptedWord.append("/#");
			break;
		case '/':
			EncryptedWord.append("//");
			break;
		case '{':
			EncryptedWord.append("/{");
			break;
		case '}':
			EncryptedWord.append("/}");
			break;
		default:
			EncryptedWord.push_back(letter);
		}

	}
	return EncryptedWord;
}


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
