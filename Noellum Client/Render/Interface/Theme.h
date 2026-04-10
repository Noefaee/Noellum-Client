#pragma once
#include "../GlobalRender.h"

namespace UI {
    inline void Style() {
        auto& style = ImGui::GetStyle();
        ImVec4* colors = style.Colors;

        // --- Layout ---
        style.WindowRounding = 5.0f;
        style.ChildRounding = 4.0f;
        style.FrameRounding = 3.0f;
        style.PopupRounding = 4.0f;
        style.ScrollbarRounding = 3.0f;
        style.GrabRounding = 3.0f;
        style.TabRounding = 3.0f;

        style.WindowBorderSize = 1.0f;
        style.FrameBorderSize = 0.0f;
        style.PopupBorderSize = 1.0f;

        style.WindowPadding = ImVec2(10, 10);
        style.FramePadding = ImVec2(8, 4);
        style.ItemSpacing = ImVec2(8, 6);
        style.ItemInnerSpacing = ImVec2(6, 4);
        style.IndentSpacing = 16.0f;
        style.ScrollbarSize = 10.0f;
        style.GrabMinSize = 8.0f;

        // --- Base ---
        colors[ImGuiCol_WindowBg] = ImVec4(0.059f, 0.059f, 0.063f, 1.00f); // #0f0f10
        colors[ImGuiCol_ChildBg] = ImVec4(0.071f, 0.071f, 0.078f, 1.00f); // #121213
        colors[ImGuiCol_PopupBg] = ImVec4(0.078f, 0.078f, 0.086f, 1.00f);
        colors[ImGuiCol_Border] = ImVec4(0.165f, 0.165f, 0.173f, 1.00f); // #2a2a2c
        colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);

        // --- Text ---
        colors[ImGuiCol_Text] = ImVec4(0.753f, 0.753f, 0.769f, 1.00f); // #c0c0c4
        colors[ImGuiCol_TextDisabled] = ImVec4(0.333f, 0.333f, 0.345f, 1.00f); // #555558

        // --- Title Bar ---
        colors[ImGuiCol_TitleBg] = ImVec4(0.059f, 0.059f, 0.063f, 1.00f);
        colors[ImGuiCol_TitleBgActive] = ImVec4(0.075f, 0.075f, 0.082f, 1.00f);
        colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.059f, 0.059f, 0.063f, 0.80f);
        colors[ImGuiCol_MenuBarBg] = ImVec4(0.059f, 0.059f, 0.063f, 1.00f);

        // --- Tabs  (nav bar style from screenshot) ---
        colors[ImGuiCol_Tab] = ImVec4(0.059f, 0.059f, 0.063f, 1.00f);
        colors[ImGuiCol_TabHovered] = ImVec4(0.110f, 0.110f, 0.118f, 1.00f);
        colors[ImGuiCol_TabActive] = ImVec4(0.059f, 0.059f, 0.063f, 1.00f); // underline via DockingIndicator
        colors[ImGuiCol_TabUnfocused] = ImVec4(0.059f, 0.059f, 0.063f, 1.00f);
        colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.059f, 0.059f, 0.063f, 1.00f);

        // --- Headers ---
        colors[ImGuiCol_Header] = ImVec4(0.122f, 0.122f, 0.133f, 1.00f);
        colors[ImGuiCol_HeaderHovered] = ImVec4(0.157f, 0.157f, 0.169f, 1.00f);
        colors[ImGuiCol_HeaderActive] = ImVec4(0.184f, 0.184f, 0.200f, 1.00f);

        // --- Frame (inputs, combos, sliders) ---
        colors[ImGuiCol_FrameBg] = ImVec4(0.102f, 0.102f, 0.118f, 1.00f); // #1a1a1e
        colors[ImGuiCol_FrameBgHovered] = ImVec4(0.129f, 0.129f, 0.145f, 1.00f);
        colors[ImGuiCol_FrameBgActive] = ImVec4(0.149f, 0.149f, 0.169f, 1.00f);

        // --- Buttons ---
        colors[ImGuiCol_Button] = ImVec4(0.110f, 0.110f, 0.118f, 1.00f);
        colors[ImGuiCol_ButtonHovered] = ImVec4(0.157f, 0.157f, 0.173f, 1.00f);
        colors[ImGuiCol_ButtonActive] = ImVec4(0.184f, 0.184f, 0.204f, 1.00f);

        // --- Accent / Blue (#4a8fff) ---
        const ImVec4 accent = ImVec4(0.290f, 0.561f, 1.00f, 1.00f);
        const ImVec4 accentHover = ImVec4(0.337f, 0.600f, 1.00f, 1.00f);
        const ImVec4 accentDim = ImVec4(0.290f, 0.561f, 1.00f, 0.35f);

        colors[ImGuiCol_CheckMark] = accent;
        colors[ImGuiCol_SliderGrab] = accent;
        colors[ImGuiCol_SliderGrabActive] = accentHover;
        colors[ImGuiCol_SeparatorActive] = accent;
        colors[ImGuiCol_SeparatorHovered] = accentDim;

        // --- Scrollbar ---
        colors[ImGuiCol_ScrollbarBg] = ImVec4(0.059f, 0.059f, 0.063f, 1.00f);
        colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.200f, 0.200f, 0.212f, 1.00f);
        colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.255f, 0.255f, 0.271f, 1.00f);
        colors[ImGuiCol_ScrollbarGrabActive] = accent;

        // --- Separator ---
        colors[ImGuiCol_Separator] = ImVec4(0.137f, 0.137f, 0.145f, 1.00f); // #232325

        // --- Resize Grip ---
        colors[ImGuiCol_ResizeGrip] = accentDim;
        colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.290f, 0.561f, 1.00f, 0.65f);
        colors[ImGuiCol_ResizeGripActive] = accent;

        // --- Misc ---
        colors[ImGuiCol_PlotLines] = ImVec4(0.290f, 0.561f, 1.00f, 1.00f);
        colors[ImGuiCol_PlotLinesHovered] = accentHover;
        colors[ImGuiCol_PlotHistogram] = accent;
        colors[ImGuiCol_PlotHistogramHovered] = accentHover;
        colors[ImGuiCol_TableHeaderBg] = ImVec4(0.090f, 0.090f, 0.098f, 1.00f);
        colors[ImGuiCol_TableBorderStrong] = ImVec4(0.165f, 0.165f, 0.173f, 1.00f);
        colors[ImGuiCol_TableBorderLight] = ImVec4(0.110f, 0.110f, 0.118f, 1.00f);
        colors[ImGuiCol_TextSelectedBg] = ImVec4(0.290f, 0.561f, 1.00f, 0.25f);
        colors[ImGuiCol_NavHighlight] = accent;
        colors[ImGuiCol_DragDropTarget] = accent;
    }
}