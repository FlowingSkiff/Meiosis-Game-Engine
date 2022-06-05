set(renderer_sources
    ${CMAKE_CURRENT_SOURCE_DIR}/Camera2D.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Material.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Renderer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/RendererBuffer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Shader.cpp
)

target_sources(meiosis PRIVATE ${renderer_sources})