
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)

add_subdirectory(thirdparty)
add_subdirectory(OGLAbstraction)
add_subdirectory(Application)
add_subdirectory(Util)
add_subdirectory(Core)
add_executable(genesis main.cpp)

target_link_libraries(genesis
    PUBLIC
        project_settings
        project_warings
        application
        imgui
)

target_include_directories(genesis
    PUBLIC
        ${CMAKE_SOURCE_DIR}/include
        $ENV{MINGW_INCLUDE}
)

target_compile_definitions(genesis
    PUBLIC
        SPDLOG_FMT_EXTERNAL
        ENABLE_LOG
)

add_custom_command(
    TARGET ${PROJECT_NAME} PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/src/Genesis/resources/ $<TARGET_FILE_DIR:${PROJECT_NAME}>/resources
)