cmake_minimum_required(VERSION 3.0.0)
project(meiosis VERSION 0.1.0)

include(CTest)
enable_testing()
include(cmake/Commands.cmake)
add_subdirectory(thirdparty)
set(third_party_include ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty)
add_subdirectory(src)



set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
