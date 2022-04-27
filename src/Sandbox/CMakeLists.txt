
set(sandbox_sources 
    sandbox.cpp
    ExampleTestLayer.cpp
)

add_executable(sandbox ${sandbox_sources})

target_link_libraries(sandbox
    PUBLIC
        Meiosis::Meiosis
)

add_custom_command(TARGET sandbox POST_BUILD        # Adds a post-build event to MyTest
    COMMAND ${CMAKE_COMMAND} -E copy_if_different  # which executes "cmake - E copy_if_different..."
        $<TARGET_FILE:meiosis>      
        $<TARGET_FILE_DIR:sandbox>)    