#pragma once

#include <string>
#include <vector>

#include "Tools.h"

class Page {
public:
	std::vector<std::string> spirits;
	std::vector<std::string> textboxs;
	std::string	backgroundName = "1";
	int pageId;
	Page(int page_id);
	//void visualizePage();
	std::vector<std::string> exportInString();	// putting all the information in this page into a vector
	/* in the sequence of
	[backgroundName, spirits.iter, textboxs.iter]
	*/
};
