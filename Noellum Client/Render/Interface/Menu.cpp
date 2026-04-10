#include "Menu.h"
#include "State.h"
#include "../GlobalRender.h"
#include "Theme.h"

static int tab = 0;

void Interface::Draw()
{
    ImGui::SetNextWindowSize(ImVec2(460, 370), ImGuiCond_FirstUseEver);
    if (!ImGui::Begin("Client v1.0 Alpha", nullptr, ImGuiWindowFlags_NoCollapse))
    {
        ImGui::End();
        return;
    }

    ImGui::TextColored(ImVec4(0.50f, 0.47f, 0.87f, 1.f), "Rift Client");
    ImGui::SameLine();
    ImGui::TextDisabled("| v1.0 Alpha");
    ImGui::Separator();

    if (ImGui::Button("General", ImVec2(100, 25))) tab = 0; ImGui::SameLine();
    if (ImGui::Button("Visuals", ImVec2(100, 25))) tab = 1; ImGui::SameLine();
    if (ImGui::Button("Internal", ImVec2(100, 25))) tab = 2; ImGui::SameLine();
    if (ImGui::Button("Debug", ImVec2(100, 25))) tab = 3;

    ImGui::Spacing(); ImGui::Separator(); ImGui::Spacing();

    if (tab == 0) DrawTabs();
    else if (tab == 1) DrawVisuals();
    else if (tab == 2) DrawInternal();
	else if (tab == 3) DrawLogger();

    ImGui::End();
}