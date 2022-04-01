set(file_util_test_sources
    ${CMAKE_CURRENT_SOURCE_DIR}/FileUtilTest.cpp 
    ${CMAKE_SOURCE_DIR}/src/Meiosis/Util/FileUtils.cpp
)

target_sources(Test PUBLIC ${file_util_test_sources})