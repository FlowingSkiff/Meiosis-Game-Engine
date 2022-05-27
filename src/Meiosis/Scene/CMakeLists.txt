set(scene_sources
    ${CMAKE_CURRENT_SOURCE_DIR}/Components.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Entity.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Scene.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/SceneCamera.cpp
    )

target_sources(meiosis PRIVATE ${scene_sources})