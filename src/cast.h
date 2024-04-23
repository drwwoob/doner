#pragma once
#include "Tools.h"
#include "data.h"
class cast
{
public:
	static void showCastWindow(bool* p_open, int pageID, Page pageInfo);
	//void showWelcomePage(bool& showing);
	static void showWelcomePage(data* gameData, bool* show_welcome_window, bool* start_visual);
private:

	//data GameStruc;
};

