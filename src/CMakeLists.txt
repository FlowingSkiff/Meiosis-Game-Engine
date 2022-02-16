
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)

add_subdirectory(thirdparty)
add_subdirectory(OGLAbstraction)
add_executable(moving-particles main.cpp)

target_link_libraries(moving-particles
    PUBLIC
        project_settings
        project_warings
        glfw
        spdlog
        fmt
        glm
        glad
        OGLAbstraction
)

target_include_directories(moving-particles
    PUBLIC
        ${CMAKE_SOURCE_DIR}/include
        $ENV{MINGW_INCLUDE}
)

target_compile_definitions(moving-particles
    PUBLIC
        SPDLOG_FMT_EXTERNAL
)