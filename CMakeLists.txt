cmake_minimum_required(VERSION 3.0.0)
project(genesis VERSION 0.1.0)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_library(project_settings INTERFACE)
add_library(project_warings INTERFACE)

include(cmake/CompilerWarnings.cmake)
set_project_warnings(project_warings)
include(cmake/StandardProjectSettings.cmake)
set_project_settings(project_settings)

include(cmake/StaticAnalyzers.cmake)
# enable_cppcheck("")

include(CTest)
enable_testing()

add_subdirectory(src)



set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
