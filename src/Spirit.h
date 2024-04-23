#pragma once
#include <string>
#include "../imgui Support/imgui.h"
//#include <winnt.h>

class Spirit
{
private:
	std::string spiritName;
	//PWSTR imageAddress;
	ImVec2 size;

public:
	Spirit(){}; // creating a new spirit
	Spirit(std::string spirit_data){}; // reading a string as a spirit
	//void change(PWSTR address_after_change);
	void change(ImVec2 size_after_change){};
	std::string toString() {
		std::string dataEncr;

		return dataEncr;
	};
	std::string name() { return spiritName; };
};

