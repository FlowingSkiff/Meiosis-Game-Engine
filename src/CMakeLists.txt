
add_subdirectory(thirdparty)

find_package(glfw3 CONFIG)

add_executable(moving-particles main.cpp)

target_link_libraries(moving-particles
    PUBLIC
        project_settings
        project_warings
        glad
        glfw
)
target_include_directories(moving-particles
    PUBLIC
        ${CMAKE_SOURCE_DIR}/include
        $ENV{MINGW_INCLUDE}
)