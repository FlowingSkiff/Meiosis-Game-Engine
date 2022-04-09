add_executable(Test main.cpp)

find_package(GTest REQUIRED)
find_package(spdlog REQUIRED)
find_package(fmt REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)
find_package(magic_enum REQUIRED)

add_subdirectory(Platform)
add_subdirectory(Util)

target_link_libraries(Test 
    PRIVATE
        GTest::gtest_main
        project_settings
        project_warings
        glm::glm
        spdlog::spdlog
        glfw::glfw
        magic_enum::magic_enum
        glad
        fmt::fmt
        
)

target_include_directories(Test 
    PRIVATE
        ${CMAKE_SOURCE_DIR}/include/Meiosis
        ${CMAKE_SOURCE_DIR}/include
        ${third_party_include}
        ${CMAKE_SOURCE_DIR}/thirdparty/imgui
)

target_compile_definitions(Test
    PRIVATE
        SPDLOG_FMT_EXTERNAL
)

include(GoogleTest)
gtest_add_tests(TARGET      Test
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