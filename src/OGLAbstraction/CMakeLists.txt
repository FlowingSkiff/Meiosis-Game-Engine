
set(ogl_abstraction_sources
    IndexBuffer.cpp
    Renderer.cpp
    Shader.cpp
    Texture.cpp
    VertexArray.cpp
    VertexBuffer.cpp
)

add_library(OGLAbstraction ${ogl_abstraction_sources})

target_link_libraries(OGLAbstraction 
    PUBLIC
        project_settings
        project_warings
        glfw3
        glad
)

target_include_directories(OGLAbstraction
    PUBLIC
        ${CMAKE_SOURCE_DIR}/include
        $ENV{MINGW_INCLUDE}
    PRIVATE
        ${CMAKE_SOURCE_DIR}/include/OGLAbstraction
)