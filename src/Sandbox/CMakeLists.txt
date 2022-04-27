
set(sandbox_sources 
    sandbox.cpp
    ExampleTestLayer.cpp
)

add_executable(sandbox ${sandbox_sources})

find_package(glm REQUIRED)
find_package(glfw3 REQUIRED)
find_package(magic_enum REQUIRED)
find_package(spdlog REQUIRED)
target_include_directories(sandbox
    PRIVATE
        ${CMAKE_SOURCE_DIR}/include/Meiosis
        ${CMAKE_SOURCE_DIR}/include
)

target_include_directories(sandbox
    SYSTEM PRIVATE
        ${third_party_include}
        ${glm_INCLUDE_DIR}
        ${glfw_INCLUDE_DIRS_RELEASE}
        ${magic_enum_INCLUDE_DIRS_RELEASE}
        ${fmt_INCLUDE_DIRS_RELEASE}
        ${spdlog_INCLUDE_DIRS_RELEASE}
)

target_link_libraries(sandbox
    PUBLIC
        meiosis
        imgui
        project_settings
        project_warings
        glm::glm
        glfw
        magic_enum::magic_enum
)

target_compile_definitions(sandbox
    PRIVATE
        SPDLOG_FMT_EXTERNAL
        ENABLE_LOG
        #ME_LINK_DLL
)


add_custom_command(TARGET sandbox POST_BUILD        # Adds a post-build event to MyTest
    COMMAND ${CMAKE_COMMAND} -E copy_if_different  # which executes "cmake - E copy_if_different..."
        $<TARGET_FILE:meiosis>      
        $<TARGET_FILE_DIR:sandbox>)    