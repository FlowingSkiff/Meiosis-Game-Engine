set(core_sources
    ${CMAKE_CURRENT_SOURCE_DIR}/Application.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Log.cpp
)
target_sources(genesis PRIVATE ${core_sources})