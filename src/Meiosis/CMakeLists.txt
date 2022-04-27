
set(meiosis_sources empty.cpp)
add_library(meiosis STATIC ${meiosis_sources})

find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)
find_package(spdlog REQUIRED)
find_package(fmt REQUIRED)
find_package(magic_enum REQUIRED)

add_subdirectory(Core)
add_subdirectory(Events)
add_subdirectory(imgui)
add_subdirectory(Layer)
add_subdirectory(Platform)
add_subdirectory(Renderer)
add_subdirectory(Util)


target_link_libraries(meiosis
    PUBLIC
        project_settings
        project_warings
        imgui
        glfw
        magic_enum::magic_enum
        glad
        fmt::fmt
)

target_include_directories(meiosis
    PRIVATE
        ${CMAKE_SOURCE_DIR}/include/Meiosis
        ${CMAKE_SOURCE_DIR}/include
)

target_include_directories(meiosis
    SYSTEM PRIVATE
        ${third_party_include}
        ${CMAKE_SOURCE_DIR}/thirdparty/imgui
        ${glm_INCLUDE_DIR}
        ${glfw_INCLUDE_DIRS_RELEASE}
        ${magic_enum_INCLUDE_DIRS_RELEASE}
        ${fmt_INCLUDE_DIRS_RELEASE}
        ${spdlog_INCLUDE_DIRS_RELEASE}
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

add_custom_command(
    TARGET ${PROJECT_NAME} PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/src/Meiosis/resources/  ${CMAKE_BINARY_DIR}/$<CONFIG>-bin/resources
)