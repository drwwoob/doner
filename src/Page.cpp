#include "Page.h"

Page::Page() {
	
}

Page::Page(int page_id) {
	pageId = page_id;
}

Page::Page(int page_id, std::string page_data)
{
	pageId = page_id;

	// page_data should look like
	// backgroundName{spirit1##spirit2##spirit3##}{textbox1##textbox2##}

	auto pos = page_data.find_first_of('{');
	backgroundName = page_data.substr(0, pos);
	//auto backBrac = page_data.find_first_of('}', frontBrac);

	pos++;
	auto start = pos; // start of spirits
	bool inGroup = true;

	// get the spirits
	while(inGroup) {
		if (page_data.at(pos) == '/') {
			pos += 1;
		}
		else if(page_data.at(pos) == '}') { // find the first "}" without / infront
			inGroup = false;
			spirits.emplace_back(page_data.substr(start, pos));
		}
		pos++;
	}
	inGroup = true;
	

	//for
	//if (data_str.at(pos) == '/') { // escaping
	//	pos++;
	//	switch (data_str.at(pos)) {

	//	}
	//}
}


std::string Page::exportInString()
{
	std::string encrypt = "[";

	// add background name
	encrypt.append(backgroundName);

	// add spirits
	encrypt.append("{");
	for(auto spirit : spirits) {
		encrypt.append(wordEncrypt(spirit.toString()));
	}
	encrypt.append("}");

	// add textboxs;
	encrypt.append("{");
	for (auto textbox : textboxs) {
		encrypt.append(wordEncrypt(textbox));
	}
	encrypt.append("}");
	

	// ending this page
	encrypt.append("]");
	return encrypt;
}

std::string Page::wordEncrypt(std::string word) {
	std::string EncryptedWord;
	for (const auto letter : word) {
		switch(letter) {
		case '#':
			EncryptedWord.append("/#");
			break;
		case '/':
			EncryptedWord.append("//");
			break;
		case '{':
			EncryptedWord.append("/{");
			break;
		case '}':
			EncryptedWord.append("/}");
			break;
		default:
			EncryptedWord.push_back(letter);
		}

	}
	return EncryptedWord;
}


//
//void Page::visualizePage()
//{
//	Tools::setBackground(backgroundName);
//}
//
//std::vector<std::string> Page::exportInString() {
//
//}
