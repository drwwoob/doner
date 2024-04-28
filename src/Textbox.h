#pragma once
#include <string>
#include "Tools.h"

class Textbox
{
public:
	std::string name;
	std::string content;
	ImVec2 positionRatio;
	ImFont* font;
	std::string fontPath;
	ImColor color;
	float fontSize;
	Textbox();
	Textbox(std::string data_str[10], ImGuiIO& io) {
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

		// default for now
		font = io.Fonts->AddFontDefault();

		color = ImColor(std::stof(data_str[5]),
			std::stof(data_str[6]),
			std::stof(data_str[7]),
			std::stof(data_str[8]));

		fontSize = std::stof(data_str[9]);


	} // load data as textbox
	//void showTextbox();
	
	std::string* getRealContent() {
		return &content;
	}

	std::string encrypt() {
		std::string WordEncry = Tools::wordEncrypt(name);

		WordEncry += "#";
		WordEncry += Tools::wordEncrypt(content);
		WordEncry += "#";
		WordEncry += std::to_string(positionRatio[0]);
		WordEncry += "#";
		WordEncry += std::to_string(positionRatio[1]);
		WordEncry += "#";
		WordEncry += Tools::wordEncrypt(fontPath);
		WordEncry += "#";
		WordEncry += std::to_string(color.Value.x);
		WordEncry += "#";
		WordEncry += std::to_string(color.Value.y);
		WordEncry += "#";
		WordEncry += std::to_string(color.Value.z);
		WordEncry += "#";
		WordEncry += std::to_string(color.Value.w);
		WordEncry += "#";
		WordEncry += std::to_string(fontSize);
		WordEncry += "##";

		return WordEncry;
	}
	// encrypt in the format
	// name#content#position[0]#position[1]#fontPath#color.r#color.g#color.b#color.a#fontSize##
};

