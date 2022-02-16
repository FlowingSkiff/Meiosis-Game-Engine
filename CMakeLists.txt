cmake_minimum_required(VERSION 3.0.0)
project(moving-particles VERSION 0.1.0)

add_library(project_settings INTERFACE)
add_library(project_warings INTERFACE)

include(cmake/CompilerWarnings.cmake)
set_project_warnings(project_warings)
include(cmake/StandardProjectSettings.cmake)
set_project_settings(project_settings)

include(cmake/Conan.cmake)
run_conan()

include(cmake/StaticAnalyzers.cmake)
enable_cppcheck("")

include(CTest)
enable_testing()

add_subdirectory(src)



set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
