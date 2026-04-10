#include "../GlobalRender.h"
#include "State.h"
#include "Menu.h"

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