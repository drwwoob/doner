#include "cast.h"
//#include "Tools.h"
//#include "data.h"
typedef void (*ImGuiMarkerCallback)(const char* file, int line, const char* section, void* user_data);
extern ImGuiMarkerCallback      GImGuiMarkerCallback;
extern void* GImGuiMarkerCallbackUserData;
ImGuiMarkerCallback             GImGuiMarkerCallback = NULL;
void* GImGuiMarkerCallbackUserData = NULL;
#define IMGUI_MARKER(section)  do { if (GImGuiMarkerCallback != NULL) GImGuiMarkerCallback(__FILE__, __LINE__, section, GImGuiMarkerCallbackUserData); } while (0)


void cast::showCastWindow(bool* p_open, int pageID, Page pageInfo) {
	ImGuiWindowFlags window_flags = 0;
	//Page pageInfo = gameData.getPage(pageID);

	if(!ImGui::Begin("Cast", p_open, window_flags)) {
		ImGui::End();
		return;
	}

	const ImGuiViewport* main_viewport = ImGui::GetMainViewport();
	//ImGui::SetNextWindowPos(ImVec2(main_viewport->WorkPos.x + 100, main_viewport->WorkPos.y + 20), ImGuiCond_FirstUseEver);
	ImGui::SetNextWindowSize(ImVec2(200, 20), ImGuiCond_FirstUseEver);
	ImGui::PushItemWidth(ImGui::GetFontSize() * -12);

	ImGui::Text("This is the list of cast on the current page");
	IMGUI_MARKER("Spirit");
	//ImGui::SetNextWindowCollapsed(false);
	if (ImGui::CollapsingHeader("Spirit", ImGuiTreeNodeFlags_DefaultOpen)) {
		for (auto spirit : pageInfo.spirits) {
			ImGui::BulletText("(%s)",spirit.name());
		}
	}
	if (ImGui::CollapsingHeader("Textbox", ImGuiTreeNodeFlags_DefaultOpen)) {
		for (auto textboxs : pageInfo.textboxs) {
			ImGui::BulletText("(%s)", textboxs.c_str());
		}
	}
	ImGui::End();
}

void cast::showWelcomePage(data gameData, bool* show_welcome_window) {
	ImGui::Begin("Welcome Page");
	if (ImGui::Button("New", ImVec2(-FLT_MIN, 80))) {
		gameData.newFile();
		*show_welcome_window = false;
	}
	if(ImGui::Button("Open", ImVec2(-FLT_MIN, 80))) {
		gameData.openFile();
		*show_welcome_window = false;
		
	}
	if(ImGui::Button("Demo", ImVec2(-FLT_MIN, 80))) {
		gameData.openFile();
		*show_welcome_window = false;
		
	}
	ImGui::End();
}
