#include "Tools.h"
#include <iostream>
#include <string>
//#define STB_IMAGE_IMPLEMENTATION

void Tools::pageBar()
{
}

//
//void Tools::setBackground(std::string background_name)
//{
//	if(background_name.empty()) {
//		//ImGui::GetBackgroundDrawList()->
//	}
//	else {
//        TCHAR buffer[MAX_PATH] = { 0 };
//        GetModuleFileName(NULL, buffer, MAX_PATH);
//        std::wstring::size_type pos = std::wstring(buffer).find_last_of(L"\\/");
//		auto wpath = std::wstring(buffer).substr(0, pos);
//        std::string path(wpath.begin(), wpath.end());
//        path.append("\\..\\..\\doner\\projects storage\\demo\\sky.jpg");
//
//        ////struct stat buf;
//        ////stat(path.c_str(), &buf);
//        //ImGui::Begin(path.c_str());/*
//        //ImGui::Text("-----------------------------%d", buf.st_size);
//        //ImGui::Text("-----------%s", buf.st_mode);*/
//        //ImGui::End();
//
//        int my_image_width = 0;
//        int my_image_height = 0;
//        ID3D11ShaderResourceView* my_texture = NULL;
//        //bool ret = Tools::LoadTextureFromFile(background_name.c_str(), &my_texture, &my_image_width, &my_image_height);
//        bool ret = LoadTextureFromFile(path.c_str(), & my_texture, & my_image_width, & my_image_height);
//        IM_ASSERT(ret);
//		//ImGui::GetBackgroundDrawList()->AddImage((void*)my_texture,ImVec2(0, 0), ImVec2(my_image_width, my_image_height), ImVec2(0, 0), ImVec2(1, 1));
//        //ImGui::Image((void*)my_texture, ImVec2(my_image_width, my_image_height));
//        ImGui::Begin("DirectX11 Texture Test");
//        ImGui::Text("pointer = %p", my_texture);
//        ImGui::Text("size = %d x %d", my_image_width, my_image_height);
//        ImGui::Image((void*)my_texture, ImVec2(my_image_width, my_image_height));
//        ImGui::End();
//	}
//}
//
////image loading helper
//#define STB_IMAGE_IMPLEMENTATION
//#include "../other Support/stb_image.h"
//

// ---------------------------- for data.cpp -----------------------
//
//size_t size = file_path.length();
//wchar_t* buffer = new wchar_t[size + 1];
//MultiByteToWideChar(CP_ACP, 0, file_path.c_str(), size, buffer, size * sizeof(wchar_t));
//buffer[size] = 0;
//filePath = buffer;
//
//delete buffer;

// -------------------------- some changing code from doner.cpp-----------
////
//int pageAt = 0;
//TCHAR buffer[MAX_PATH] = { 0 };
////GetModuleFileName(NULL, buffer, MAX_PATH);
//std::wstring::size_type pos = std::wstring(buffer).find_last_of(L"\\/");
//auto wpath = std::wstring(buffer).substr(0, pos);
//std::string Path(wpath.begin(), wpath.end());
//std::string demoLocation = Path.append("\\..\\..\\doner\\projects storage\\demo\\");
//data gameData = data(demoLocation.append("demo.txt"));

//
//
//int my_image_width = 0;
//int my_image_height = 0;
//ID3D11ShaderResourceView* my_texture = NULL;
////bool ret = Tools::LoadTextureFromFile(background_name.c_str(), &my_texture, &my_image_width, &my_image_height);
//// ---------------------need to change------------------------
//bool ret = LoadTextureFromFile(demoLocation.append("sky.jpg").c_str(), &my_texture, &my_image_width, &my_image_height);
//IM_ASSERT(ret);
////ImGui::GetBackgroundDrawList()->AddImage((void*)my_texture,ImVec2(0, 0), ImVec2(my_image_width, my_image_height), ImVec2(0, 0), ImVec2(1, 1));
////ImGui::Image((void*)my_texture, ImVec2(my_image_width, my_image_height));
////}
//
//
//    // --------------------------get data info--------------------------------
//pageAt = gameData.leaveAt;

//// Simple helper function to load an image into a DX11 texture with common settings
//bool Tools::LoadTextureFromFile(const char* filename, ID3D11ShaderResourceView** out_srv, int* out_width, int* out_height)
//{
//    // Load from disk into a raw RGBA buffer
//    int image_width = 0;
//    int image_height = 0;
//    unsigned char* image_data = stbi_load(filename, &image_width, &image_height, NULL, 4);
//    if (image_data == NULL)
//        return false;
//
//    // Create texture
//    D3D11_TEXTURE2D_DESC desc;
//    ZeroMemory(&desc, sizeof(desc));
//    desc.Width = image_width;
//    desc.Height = image_height;
//    desc.MipLevels = 1;
//    desc.ArraySize = 1;
//    desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
//    desc.SampleDesc.Count = 1;
//    desc.Usage = D3D11_USAGE_DEFAULT;
//    desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
//    desc.CPUAccessFlags = 0;
//
//    ID3D11Texture2D* pTexture = NULL;
//    D3D11_SUBRESOURCE_DATA subResource;
//    subResource.pSysMem = image_data;
//    subResource.SysMemPitch = desc.Width * 4;
//    subResource.SysMemSlicePitch = 0;
//    g_pd3dDevice->CreateTexture2D(&desc, &subResource, &pTexture);
//
//    // Create texture view
//    D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
//    ZeroMemory(&srvDesc, sizeof(srvDesc));
//    srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
//    srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
//    srvDesc.Texture2D.MipLevels = desc.MipLevels;
//    srvDesc.Texture2D.MostDetailedMip = 0;
//    g_pd3dDevice->CreateShaderResourceView(pTexture, &srvDesc, out_srv);
//    pTexture->Release();
//
//    *out_width = image_width;
//    *out_height = image_height;
//    stbi_image_free(image_data);
//
//    return true;
//}