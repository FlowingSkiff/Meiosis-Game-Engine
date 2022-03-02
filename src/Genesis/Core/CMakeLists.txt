set(core_sources
    ${CMAKE_CURRENT_SOURCE_DIR}/Application.cpp
)
target_sources(genesis PRIVATE ${core_sources})
# add_subdirectory(Log)