set(core_sources
    ${CMAKE_CURRENT_SOURCE_DIR}/Application.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Log.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Window.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GraphicsContext.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/EntryPoint.cpp
)
target_sources(meiosis PRIVATE ${core_sources})