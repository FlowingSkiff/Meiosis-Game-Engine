
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)

add_subdirectory(thirdparty)
add_subdirectory(OGLAbstraction)
add_subdirectory(Application)
add_subdirectory(Util)
add_executable(moving-particles main.cpp)

target_link_libraries(moving-particles
    PUBLIC
        project_settings
        project_warings
        application
        imgui
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

add_custom_command(
    TARGET ${PROJECT_NAME} PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/src/resources/ $<TARGET_FILE_DIR:${PROJECT_NAME}>/resources
)