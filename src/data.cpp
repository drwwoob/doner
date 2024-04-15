#include "data.h"

data::data()
{
	data::pages.emplace_back(0);
}

data::data(std::string file_name) {
	
}


Page data::getPage(int page_id) {
	return data::pages.at(page_id);
}
