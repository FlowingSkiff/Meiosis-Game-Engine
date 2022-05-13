add_executable(Test main.cpp)

find_package(GTest REQUIRED)
find_package(spdlog REQUIRED)
find_package(fmt REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)
find_package(magic_enum REQUIRED)
find_package(stb REQUIRED)

add_subdirectory(Platform)
add_subdirectory(Util)

target_link_libraries(Test 
    PRIVATE
        GTest::gtest_main
        glm::glm
        glfw
        magic_enum::magic_enum
        glad
        fmt::fmt
        stb::stb
        
)

target_include_directories(Test 
    PRIVATE
        ${CMAKE_SOURCE_DIR}/include/Meiosis
        ${CMAKE_SOURCE_DIR}/include
)

target_include_directories(Test
    SYSTEM PRIVATE
        ${third_party_include}
        ${CMAKE_SOURCE_DIR}/thirdparty/imgui
        ${glm_INCLUDE_DIR}
        ${glfw_INCLUDE_DIRS_RELEASE}
        ${magic_enum_INCLUDE_DIRS_RELEASE}
        ${fmt_INCLUDE_DIRS_RELEASE}
        ${spdlog_INCLUDE_DIRS_RELEASE}
        ${gtest_INCLUDE_DIRS_RELEASE}
        ${stb_INCLUDE_DIR}
)

target_compile_definitions(Test
    PRIVATE
        SPDLOG_FMT_EXTERNAL
)

include(GoogleTest)
gtest_discover_tests(Test)