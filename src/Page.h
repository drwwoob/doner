#pragma once

#include <string>
#include <vector>
#include "Spirit.h"
#include "Tools.h"

class Page {
public:
	std::vector<Spirit> spirits;
	std::vector<std::string> textboxs;
	// std::vector<std::string> textboxs settings;
	std::string	backgroundName = "last";
	int pageId;
	Page();
	Page(int page_id);
	Page(int page_id, std::string page_data);
	//Page(int page_id, std::vector<std::string> spirits_vec, std::vector<std::string> textboxs_vec);
	//void visualizePage();
	std::string exportInString();	// putting all the information in this page into a string
	/* in the format of
	[backgroundName{spirit1##spirit2##spirit3##}{textbox1##textbox2##}][backgroundName{spirit1##spirit2##spirit3##}{textbox1##textbox2##}]
	*/

	//pageID[backgroundName{spirit1##spirit2##spirit3##}{textbox1##textbox2##}]

private:
	static std::string wordEncrypt(std::string word);
	/*exceptions:
	 *	# -> /#
	 *	/ -> //
	 *	{ -> /{
	 *	} -> /}
	*/
};
//
//class Spirit{
//	
//};
//
//class Textbox{
//	
//};