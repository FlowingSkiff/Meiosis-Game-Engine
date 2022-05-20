
set(meiosis_sources empty.cpp)
add_library(meiosis STATIC ${meiosis_sources})

find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)
find_package(spdlog REQUIRED)
find_package(fmt REQUIRED)
find_package(magic_enum REQUIRED)
find_package(stb REQUIRED)

add_subdirectory(Core)
add_subdirectory(Events)
add_subdirectory(imgui)
add_subdirectory(Layer)
add_subdirectory(Platform)
add_subdirectory(Renderer)
add_subdirectory(Util)

add_library(Meiosis::Meiosis ALIAS meiosis)
set_target_properties(meiosis PROPERTIES
    VERSION "${PROJECT_VERSION}"
    SOVERSION "${PROJECT_VERSION_MAJOR}"
    EXPORT_NAME Meiosis
    OUTPUT_NAME Meiosis
)


target_link_libraries(meiosis
    PUBLIC
        imgui
        glfw
        magic_enum::magic_enum
        glad
        fmt::fmt
        stb::stb
        glm::glm
)


target_include_directories(meiosis
    PUBLIC
        ${CMAKE_SOURCE_DIR}/include/Meiosis
        ${CMAKE_SOURCE_DIR}/include
)

target_include_directories(meiosis
    SYSTEM PUBLIC
        ${third_party_include}
        ${CMAKE_SOURCE_DIR}/thirdparty/imgui
        ${spdlog_INCLUDE_DIR}
)

target_compile_definitions(meiosis
    PUBLIC
        SPDLOG_FMT_EXTERNAL
        ENABLE_LOG
)

COPY_RESOURCES(meiosis ${CMAKE_CURRENT_SOURCE_DIR}/resources)