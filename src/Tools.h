#pragma once
#include "../imgui Support/imconfig.h"
#include "../imgui Support/imgui.h"
#include "../imgui Support/imgui_impl_dx11.h"
#include "../imgui Support/imgui_impl_win32.h"
#include "../imgui Support/imgui_internal.h"
#include "../imgui Support/imstb_rectpack.h"
#include "../imgui Support/imstb_textedit.h"
#include "../imgui Support/imstb_truetype.h"
#include <d3d11.h>
#include <string>
#pragma comment(lib, "d3d11.lib")

//image loading helper


//#include "cast.h"

class Tools
{
public:
	void pageBar();
	static void setBackground(std::string background_name);
	//helper function
};

