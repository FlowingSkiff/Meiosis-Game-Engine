set(imgui_sources
    ${CMAKE_CURRENT_SOURCE_DIR}/ImguiLayer.cpp
)

target_sources(meiosis PRIVATE ${imgui_sources})