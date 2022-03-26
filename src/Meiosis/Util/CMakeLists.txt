
set(util_resources
    ${CMAKE_CURRENT_SOURCE_DIR}/Random.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/FileUtils.cpp
)

target_sources(meiosis PRIVATE ${util_resources})