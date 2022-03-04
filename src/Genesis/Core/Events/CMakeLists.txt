set(event_sources
    ${CMAKE_CURRENT_SOURCE_DIR}/KeyEvent.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/MouseEvent.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ApplicationEvent.cpp
)

target_sources(genesis PRIVATE ${event_sources})