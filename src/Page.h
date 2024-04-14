#pragma once

#include <string>
#include <vector>

#include "Tools.h"

class Page {
public:
	std::vector<std::string> spirits;
	std::vector<std::string> textboxs;
	int pageId;
	//Page(std::string ID);
	Page(int pageId);
};
