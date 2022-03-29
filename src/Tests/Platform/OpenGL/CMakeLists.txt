
find_package(gtest REQUIRED)

find_package(spdlog REQUIRED)
find_package(fmt REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)
set(open_gl_test_sources
    ShaderTest.cpp 
    ${CMAKE_SOURCE_DIR}/src/Meiosis/Platform/OpenGL/OpenGLShader.cpp
    ${CMAKE_SOURCE_DIR}/src/Meiosis/Util/FileUtils.cpp
    ${CMAKE_SOURCE_DIR}/src/Meiosis/Core/Log.cpp
    ${CMAKE_SOURCE_DIR}/src/Meiosis/Renderer/Shader.cpp
    ${CMAKE_SOURCE_DIR}/src/Meiosis/Platform/OpenGL/OpenGLRendererAPI.cpp
)

add_executable(OpenGLTest ${open_gl_test_sources})
target_link_libraries(OpenGLTest 
    PRIVATE
        GTest::gtest_main
        project_settings
        project_warings
        glm::glm
        spdlog
        glfw3
        glad
        fmt
)
target_include_directories(OpenGLTest 
    PRIVATE
        ${CMAKE_SOURCE_DIR}/include/Meiosis
        ${CMAKE_SOURCE_DIR}/include
        ${third_party_include}
        ${CMAKE_SOURCE_DIR}/thirdparty/imgui
    public:
        ${glm_INCLUDE_DIR}
)

target_compile_definitions(OpenGLTest
    PRIVATE
        SPDLOG_FMT_EXTERNAL
        # ENABLE_LOG
)

include(GoogleTest)
gtest_add_tests(TARGET      OpenGLTest
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