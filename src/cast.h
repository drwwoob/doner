#pragma once
#include "Tools.h"
#include "data.h"
class cast
{
public:
	static void showCastWindow(bool* p_open, int pageID, Page *pageInfo, ImVec2 window_size);
	//void showWelcomePage(bool& showing);
	static void showWelcomePage(data* gameData, bool* show_welcome_window, bool* start_visual, bool* page_setting);
	static void showFileWindow(bool* p_open, int pageID, Page* pageInfo);
	static void showPageWindow(bool* p_open, int* pageID, data* game_data);

private:
	//static int MyResizeCallback(ImGuiInputTextCallbackData* data);
	//data GameStruc;
};

