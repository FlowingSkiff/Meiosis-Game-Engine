
add_library(application application.cpp)

target_link_libraries(application
    PUBLIC
        project_settings
        project_warings
        glfw
        spdlog
        fmt
        glm
        glad
        OGLAbstraction
        imgui
)

target_include_directories(application
    PUBLIC
        ${CMAKE_SOURCE_DIR}/include
        $ENV{MINGW_INCLUDE}
)

target_compile_definitions(application
    PUBLIC
        SPDLOG_FMT_EXTERNAL
)