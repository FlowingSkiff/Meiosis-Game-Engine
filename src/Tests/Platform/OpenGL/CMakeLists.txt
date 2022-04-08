set(open_gl_test_sources
    ${CMAKE_CURRENT_SOURCE_DIR}/ShaderTest.cpp 
    ${CMAKE_SOURCE_DIR}/src/Meiosis/Platform/OpenGL/OpenGLShader.cpp
    ${CMAKE_SOURCE_DIR}/src/Meiosis/Util/FileUtils.cpp
    ${CMAKE_SOURCE_DIR}/src/Meiosis/Core/Log.cpp
    ${CMAKE_SOURCE_DIR}/src/Meiosis/Renderer/Shader.cpp
    ${CMAKE_SOURCE_DIR}/src/Meiosis/Renderer/Renderer.cpp
    ${CMAKE_SOURCE_DIR}/src/Meiosis/Platform/OpenGL/OpenGLRendererAPI.cpp
    ${CMAKE_SOURCE_DIR}/src/Meiosis/Platform/OpenGL/OpenGLBuffer.cpp
)

target_sources(Test PUBLIC ${open_gl_test_sources})