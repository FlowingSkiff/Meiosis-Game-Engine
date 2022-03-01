
set(util_resources
    Random.cpp
)

add_library(util ${util_resources})

target_link_libraries(util 
PUBLIC
    project_settings
    project_warings
)

target_include_directories(util
PUBLIC
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/include/Genesis
    $ENV{MINGW_INCLUDE}
)