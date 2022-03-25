set(renderer_sources
    ${CMAKE_CURRENT_SOURCE_DIR}/Renderer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Shader.cpp
)

target_sources(meiosis PRIVATE ${renderer_sources})