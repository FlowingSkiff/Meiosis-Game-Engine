set(imgui_sources 
    imgui.cpp
)

set(imgui_include ${CMAKE_CURRENT_SOURCE_DIR})

add_library(imgui STATIC ${imgui_sources})

target_include_directories(imgui PRIVATE ${third_party_include})