
set(sandbox_sources 
    sandbox.cpp
    ExampleTestLayer.cpp
)

add_executable(sandbox ${sandbox_sources})

target_include_directories(sandbox
    PRIVATE
        ${CMAKE_SOURCE_DIR}/include/Meiosis
        ${CMAKE_SOURCE_DIR}/include
)
target_link_libraries(sandbox
    PRIVATE
        meiosis
        project_settings
        project_warings
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