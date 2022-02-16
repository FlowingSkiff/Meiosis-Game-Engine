

add_executable(moving-particles main.cpp)

target_link_libraries(moving-particles
    PUBLIC
        project_settings
        project_warings
)
target_include_directories(moving-particles
    PUBLIC
        include
        $ENV{MINGW_INCLUDE}
)