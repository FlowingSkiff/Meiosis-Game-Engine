cmake_minimum_required(VERSION 3.0.0)
project(meiosis VERSION 0.1.0)

add_library(project_settings INTERFACE)
add_library(project_warings INTERFACE)

include(cmake/CompilerWarnings.cmake)
set_project_warnings(project_warings)
include(cmake/StandardProjectSettings.cmake)
set_project_settings(project_settings)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/$<CONFIG>-lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/$<CONFIG>-lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/$<CONFIG>-bin)

include(cmake/Conan.cmake)
conan_install()

if (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    target_compile_definitions(project_settings INTERFACE ME_DEBUG)
endif()

include(cmake/StaticAnalyzers.cmake)
#enable_cppcheck("")

include(CTest)
enable_testing()

add_subdirectory(lib)
add_subdirectory(thirdparty)
set(third_party_include ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty)
add_subdirectory(src)



set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
