#pragma once
#include <string>
#include "Tools.h"

class Textbox
{
public:
	std::string name;
	std::string content;
	ImVec2 positionRatio;
	ImFont font;
	std::string fontPath;
	ImColor color;
	float fontSize;
	Textbox();
	Textbox(std::string data_str[10]) {
		name = data_str[0];
		content = data_str[1];
		positionRatio[0] = std::stof(data_str[2]);
		positionRatio[1] = std::stof(data_str[3]);
		if(data_str[4] == "") {
			fontPath = ""; // into default font Path
		}
		else {
			fontPath = data_str[4];
		}
		//font =  // load font
		//font = NULL; for default

		color = ImColor(std::stof(data_str[5]),
			std::stof(data_str[6]),
			std::stof(data_str[7]),
			std::stof(data_str[8]));

		fontSize = std::stof(data_str[9]);


	} // load data as textbox
	//void showTextbox();
	


	// encrypt in the format
	// name#content#position[0]#position[1]#fontPath#color.r#color.g#color.b#color.a#fontSize##
};

