set(imgui_sources
    imgui_draw.cpp
    imgui_tables.cpp
    imgui_widgets.cpp
    imgui.cpp
    imgui_demo.cpp
    imgui_impl_glfw.cpp
    imgui_impl_opengl3.cpp
)
add_library(imgui ${imgui_sources})

target_include_directories(
    imgui 
        PUBLIC
            ${CMAKE_SOURCE_DIR}/include/imgui
)