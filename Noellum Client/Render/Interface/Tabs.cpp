#include "../GlobalRender.h"
#include "State.h"
#include "Menu.h"
#include "../../Utils/Logger.hpp"

void Interface::DrawTabs()
{
	ImGui::Separator();
	ImGui::Checkbox("Test1", &State::test1);
	ImGui::Spacing();
}

void Interface::DrawVisuals()
{
	ImGui::Separator();
	ImGui::Checkbox("Test2", &State::test2);
	ImGui::Spacing();
}

void Interface::DrawInternal()
{
	ImGui::Separator();
	ImGui::Checkbox("Test3", &State::test3);
	ImGui::Spacing();
}

void Interface::DrawLogger() {
    if (ImGui::Button("Clear Logs")) {
        std::lock_guard<std::mutex> lock(Utils::Logger::log_mutex);
        Utils::Logger::logs.clear();
    }

    ImGui::Separator();

    // Beri tinggi tertentu, misalnya 200 pixel agar pas di dalam tab
    ImGui::BeginChild("LogRegion", ImVec2(0, 200), true, ImGuiWindowFlags_HorizontalScrollbar);
    {
        std::lock_guard<std::mutex> lock(Utils::Logger::log_mutex);
        for (const auto& entry : Utils::Logger::logs) {
            if (entry.level == "ERR ") ImGui::TextColored(ImVec4(1.0f, 0.4f, 0.4f, 1.0f), "[%s]", entry.level.c_str());
            else if (entry.level == "RESL") ImGui::TextColored(ImVec4(0.4f, 1.0f, 0.4f, 1.0f), "[%s]", entry.level.c_str());
            else ImGui::Text("[%s]", entry.level.c_str());

            ImGui::SameLine();
            ImGui::TextDisabled("[%s]", entry.location.c_str());
            ImGui::SameLine();
            ImGui::TextUnformatted(entry.message.c_str());
        }

        // Auto-scroll tetap jalan
        if (ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
            ImGui::SetScrollHereY(1.0f);
    }
    ImGui::EndChild();
}