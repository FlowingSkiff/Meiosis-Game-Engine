set(imgui_sources 
    ${CMAKE_CURRENT_SOURCE_DIR}/imgui.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/imgui_demo.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/imgui_draw.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/imgui_tables.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/imgui_widgets.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
)
find_package(glfw3 REQUIRED)
add_library(imgui STATIC ${imgui_sources})

target_compile_options(imgui PRIVATE -w)

target_include_directories(imgui PUBLIC BEFORE 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/backends
)

target_link_libraries(imgui
    PRIVATE
        glfw::glfw
)

set_target_properties(imgui
    PROPERTIES
        CXX_CPPCHECK ""
        CXX_CLANG_TIDY ""
)