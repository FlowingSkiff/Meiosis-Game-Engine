
set(ogl_abstraction_sources
    IndexBuffer.cpp
    Renderer.cpp
    Shader.cpp
    Texture.cpp
    VertexArray.cpp
    VertexBuffer.cpp
    ComputeShader.cpp
)

add_library(OGLAbstraction ${ogl_abstraction_sources})

target_link_libraries(OGLAbstraction 
    PUBLIC
        project_settings
        project_warings
        glfw3
        glad
        Log
)

target_include_directories(OGLAbstraction
    PUBLIC
        ${CMAKE_SOURCE_DIR}/include
        ${CMAKE_SOURCE_DIR}/include/Genesis
        $ENV{MINGW_INCLUDE}
)


target_compile_definitions(OGLAbstraction
    PUBLIC
        SPDLOG_FMT_EXTERNAL
        ENABLE_LOG
)