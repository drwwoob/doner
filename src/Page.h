#pragma once

#include <string>
#include <vector>

#include "Tools.h"

class Page {
public:
	std::vector<std::string> spirits;
	std::vector<std::string> textboxs;
	std::string	backgroundName = "last";
	int pageId;
	//Page();
	Page(int page_id);
	//void visualizePage();
	std::string exportInString();	// putting all the information in this page into a string
	/* in the format of
	[backgroundName, {spirit1, spirit2, spirit3}, {textbox1, textbox2}]
	*/
};
