

add_executable(sandbox sandbox.cpp)

target_include_directories(sandbox
    PRIVATE
        ${CMAKE_SOURCE_DIR}/include/Genesis
        ${CMAKE_SOURCE_DIR}/include
)
target_link_libraries(sandbox
    PRIVATE
        genesis
        project_settings
        project_warings
)

target_compile_definitions(sandbox
    PRIVATE
        SPDLOG_FMT_EXTERNAL
        ENABLE_LOG
)


add_custom_command(TARGET sandbox POST_BUILD        # Adds a post-build event to MyTest
    COMMAND ${CMAKE_COMMAND} -E copy_if_different  # which executes "cmake - E copy_if_different..."
        $<TARGET_FILE:genesis>      
        $<TARGET_FILE_DIR:sandbox>)    