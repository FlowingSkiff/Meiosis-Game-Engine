
set(ogl_abstraction_sources
    ${CMAKE_CURRENT_SOURCE_DIR}/IndexBuffer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Renderer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Shader.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Texture.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/VertexArray.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/VertexBuffer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ComputeShader.cpp
)

target_sources(meiosis PRIVATE ${ogl_abstraction_sources})