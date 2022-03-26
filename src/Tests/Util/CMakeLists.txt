find_package(gtest REQUIRED)
add_executable(FileUtilTest FileUtilTest.cpp ${CMAKE_SOURCE_DIR}/src/Meiosis/Util/FileUtils.cpp)
target_link_libraries(FileUtilTest 
    PRIVATE
        ${GTest_LIBRARIES}
)
target_include_directories(FileUtilTest 
    PUBLIC 
        ${CMAKE_SOURCE_DIR}/include
        ${GTest_INCLUDE_DIR}
)