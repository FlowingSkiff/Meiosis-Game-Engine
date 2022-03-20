#include "ExampleTestLayer.hpp"
#include <imgui/imgui.h>

void ExampleLayer::onEvent(Meiosis::Event& e)
{
    ENGINE_INFO("{}", e);
}

void ExampleLayer::onImguiRender()
{
    ImGui::Text("dear imgui says hello. (%s)", IMGUI_VERSION);
}