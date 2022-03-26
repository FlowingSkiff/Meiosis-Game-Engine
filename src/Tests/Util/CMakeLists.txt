
find_package(gtest REQUIRED)


set(file_util_test_sources
    FileUtilTest.cpp 
    ${CMAKE_SOURCE_DIR}/src/Meiosis/Util/FileUtils.cpp
)

add_executable(FileUtilTest ${file_util_test_sources})
target_link_libraries(FileUtilTest 
    PRIVATE
        gtest_main
        project_settings
        project_warings
        
)
target_include_directories(FileUtilTest 
    PUBLIC 
        ${CMAKE_SOURCE_DIR}/include
        ${GTest_INCLUDE_DIRS}
)

include(GoogleTest)
gtest_add_tests(TARGET      FileUtilTest
                TEST_SUFFIX .noArgs
                TEST_LIST   noArgsTests
)
# gtest_add_tests(TARGET      FileUtilTest
#                 EXTRA_ARGS  --someArg someValue
#                 TEST_SUFFIX .withArgs
#                 TEST_LIST   withArgsTests
# )
set_tests_properties(${noArgsTests}   PROPERTIES TIMEOUT 10)
set_tests_properties(${withArgsTests} PROPERTIES TIMEOUT 20)