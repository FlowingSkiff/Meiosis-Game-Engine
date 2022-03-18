
set(layer_sources
    ${CMAKE_CURRENT_SOURCE_DIR}/Layer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/LayerStack.cpp
)

target_sources(meiosis PRIVATE ${layer_sources})