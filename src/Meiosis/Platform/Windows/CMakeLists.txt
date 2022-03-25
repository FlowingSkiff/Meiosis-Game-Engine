set(windows_sources
    ${CMAKE_CURRENT_SOURCE_DIR}/WindowsWindow.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/WindowsInput.cpp
)

target_sources(meiosis PRIVATE ${windows_sources})