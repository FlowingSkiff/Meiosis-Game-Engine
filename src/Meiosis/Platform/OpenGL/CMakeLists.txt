set(opengl_sources
    ${CMAKE_CURRENT_SOURCE_DIR}/OpenGLGraphicsContext.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/OpenGLRendererAPI.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/OpenGLShader.cpp
)
target_sources(meiosis PRIVATE ${opengl_sources})