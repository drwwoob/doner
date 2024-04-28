#include "cast.h"
//#include "Tools.h"
//#include "data.h"
typedef void (*ImGuiMarkerCallback)(const char* file, int line, const char* section, void* user_data);
extern ImGuiMarkerCallback      GImGuiMarkerCallback;
extern void* GImGuiMarkerCallbackUserData;
ImGuiMarkerCallback             GImGuiMarkerCallback = NULL;
void* GImGuiMarkerCallbackUserData = NULL;
#define IMGUI_MARKER(section)  do { if (GImGuiMarkerCallback != NULL) GImGuiMarkerCallback(__FILE__, __LINE__, section, GImGuiMarkerCallbackUserData); } while (0)


void cast::showCastWindow(bool* p_open, int pageID, Page *pageInfo, ImVec2 window_size) {
	ImGuiWindowFlags window_flags = 0;
	//Page pageInfo = gameData.getPage(pageID);

	//if(!ImGui::Begin("Cast", p_open, window_flags)) {
	//	ImGui::End();
	//	return;
	//}

	ImGui::Begin("Cast", p_open, window_flags);

	const ImGuiViewport* main_viewport = ImGui::GetMainViewport();
	//ImGui::SetNextWindowPos(ImVec2(main_viewport->WorkPos.x + 100, main_viewport->WorkPos.y + 20), ImGuiCond_FirstUseEver);
	ImGui::SetNextWindowSize(ImVec2(200, 20), ImGuiCond_FirstUseEver);
	ImGui::PushItemWidth(ImGui::GetFontSize() * -12);

	ImGui::Text("This is the list of cast on the current page");
	IMGUI_MARKER("Spirit");
	//ImGui::SetNextWindowCollapsed(false);
	if (ImGui::CollapsingHeader("Spirit", ImGuiTreeNodeFlags_DefaultOpen)) {
		for (int id = 0; id < pageInfo->spirits.size(); id++) {
			ImGui::SetNextWindowCollapsed(false);
			IMGUI_MARKER(pageInfo->spirits.at(id).name().c_str());
			if (ImGui::TreeNode(pageInfo->spirits.at(id).name().c_str())) {
				//ImGui::BulletText("(%s)", pageInfo->spirits.at(id).name().c_str());
				/*static char buff[32] = "";
				ImGui::InputText("testxt", buff, 32);*/

				//ImGui::SeparatorText( pageInfo->getRealSpirits(id)->name().c_str());

				auto nameStr = pageInfo->getRealSpirits(id)->getRealNickName();
				auto renameLabel = "rename##" + pageInfo->spirits.at(id).getFileName();
				ImGui::InputText(renameLabel.c_str(), nameStr);
				///*ImGui::InputText("rename", &name_str,
				//ImGuiInputTextFlags_CallbackResize, MyResizeCallback, (void*) &name_str);*/
				//

				// changing size and position
				auto widthLabel = "width##" + pageInfo->spirits.at(id).getFileName();
				ImGui::SliderFloat(widthLabel.c_str(), &pageInfo->getRealSpirits(id)->sizeRatio[0], 0.0f, 1.0f);
				auto heightLabel = "height##" + pageInfo->spirits.at(id).getFileName();
				ImGui::SliderFloat(heightLabel.c_str(), &pageInfo->getRealSpirits(id)->sizeRatio[1], 0.0f, 1.0f);
				auto xLabel = "x-cord##" + pageInfo->spirits.at(id).getFileName();
				ImGui::SliderFloat(xLabel.c_str(), &pageInfo->getRealSpirits(id)->positionRatio[0], 0.0f, 1.0f);
				auto yLabel = "y-cord##" + pageInfo->spirits.at(id).getFileName();
				ImGui::SliderFloat(yLabel.c_str(), &pageInfo->getRealSpirits(id)->positionRatio[1], 0.0f, 1.0f);

				ImGui::TreePop();
			}
		}
	}
	IMGUI_MARKER("Textbox");
	if (ImGui::CollapsingHeader("Textbox", ImGuiTreeNodeFlags_DefaultOpen)) {

		for (auto id = 0; id < pageInfo->textboxs.size(); id++) {

			if(ImGui::TreeNode(pageInfo->textboxs[id].name.c_str())) {

				auto editLabel = "edit##" + pageInfo->textboxs[id].name;
				auto contentStr = pageInfo->textboxs[id].getRealContent();
				//ImGui::BulletText("%s", textbox.content.c_str());
				ImGui::InputTextMultiline(editLabel.c_str(),contentStr);


				auto xLabel = "x-cord##" + pageInfo->textboxs.at(id).name;
				ImGui::SliderFloat(xLabel.c_str(), &pageInfo->getRealTextbox(id)->positionRatio[0], 0.0f, 1.0f);
				auto yLabel = "y-cord##" + pageInfo->textboxs.at(id).name;
				ImGui::SliderFloat(yLabel.c_str(), &pageInfo->getRealTextbox(id)->positionRatio[1], 0.0f, 1.0f);

				ImGui::TreePop();
			}
			//ImGui::BulletText("(%s)", textboxs.c_str());
		}
	}

	IMGUI_MARKER("Background");
	if(ImGui::CollapsingHeader("Background", ImGuiTreeNodeFlags_DefaultOpen)) {
		ImGui::Text("%s", pageInfo->backgroundName.c_str());
	}
	ImGui::End();
}

void cast::showWelcomePage(data* gameData, bool* show_welcome_window, bool* start_visual) {
	ImGui::Begin("Welcome Page");
	if (ImGui::Button("New", ImVec2(-FLT_MIN, 80))) {
		gameData->newFile(start_visual);
		*show_welcome_window = false;
	}
	if(ImGui::Button("Open", ImVec2(-FLT_MIN, 80))) {
		gameData->openFile(start_visual);
		*show_welcome_window = false;
		
	}
	if(ImGui::Button("Demo", ImVec2(-FLT_MIN, 80))) {
		gameData->openDemo(start_visual);
		*show_welcome_window = false;
		
	}
	ImGui::End();
}

void cast::showFileWindow(bool* p_open, int pageID, Page* pageInfo)
{
	ImGui::Begin("FILE");

	ImGui::End();
}



// helper function from imgui_demo
//int cast::MyResizeCallback(ImGuiInputTextCallbackData* data)
//{
//	if (data->EventFlag == ImGuiInputTextFlags_CallbackResize)
//	{
//		ImVector<char>* my_str = (ImVector<char>*)data->UserData;
//		IM_ASSERT(my_str->begin() == data->Buf);
//		my_str->resize(data->BufSize); // NB: On resizing calls, generally data->BufSize == data->BufTextLen + 1
//		data->Buf = my_str->begin();
//	}
//	return 0;
//}