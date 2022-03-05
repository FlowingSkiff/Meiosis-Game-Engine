
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

# add_library(OGLAbstraction ${ogl_abstraction_sources})
# 
# target_link_libraries(OGLAbstraction 
#     PUBLIC
#         project_settings
#         project_warings
#         glfw3
#         glad
#         Log
# )
# 
# target_include_directories(OGLAbstraction
#     PUBLIC
#         ${CMAKE_SOURCE_DIR}/include
#         ${CMAKE_SOURCE_DIR}/include/Meiosis
#         $ENV{MINGW_INCLUDE}
# )
# 
# 
# target_compile_definitions(OGLAbstraction
#     PUBLIC
#         SPDLOG_FMT_EXTERNAL
#         ENABLE_LOG
# )