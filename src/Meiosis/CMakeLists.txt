
set(meiosis_sources empty.cpp)
add_library(meiosis STATIC ${meiosis_sources})

find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)

add_subdirectory(thirdparty)
add_subdirectory(Core)


target_link_libraries(meiosis
    PRIVATE
        project_settings
        project_warings
        imgui
        glfw3
        glm
        glad
    PUBLIC
        fmt
)

target_include_directories(meiosis
    PRIVATE
        ${CMAKE_SOURCE_DIR}/include/Meiosis
        ${CMAKE_SOURCE_DIR}/include
        $ENV{MINGW_INCLUDE}
)

target_compile_definitions(meiosis
    PRIVATE
        SPDLOG_FMT_EXTERNAL
        ENABLE_LOG
        #ME_BUILD_DLL
)

add_custom_command(
    TARGET ${PROJECT_NAME} PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/src/Meiosis/resources/ $<TARGET_FILE_DIR:${PROJECT_NAME}>/resources
)