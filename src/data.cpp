#include "data.h"

data::data()
{
	data::pages.emplace_back(0);
}

data::data(std::string fileName) {
	
}


Page data::getPage(int pageID) {
	return data::pages.at(pageID);
}
