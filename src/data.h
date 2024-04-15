#pragma once

#include <map>

#include "Page.h"
#include "Tools.h"

class data
{
public:
	data();
	data(std::string file_name);
	Page getPage(int page_id);
	int leaveAt = 0;	// the page that the user left at last time

private:
	std::vector<Page> pages;
	std::string fileName;
	//std::map<Page> pages;

	// a hash table that stores all pages? or array?

	void readData(std::string name);
};