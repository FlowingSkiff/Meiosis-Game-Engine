
set(sandbox_sources 
    sandbox.cpp
    ExampleTestLayer.cpp
)

add_executable(sandbox ${sandbox_sources})

target_link_libraries(sandbox
    PUBLIC
        Meiosis::Meiosis
)

COPY_RESOURCES(sandbox ${CMAKE_CURRENT_SOURCE_DIR}/resources)