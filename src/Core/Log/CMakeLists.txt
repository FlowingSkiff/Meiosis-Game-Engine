set (log_sources
        Log.cpp
)

add_library(Log ${log_sources})

target_link_libraries(Log
    PUBLIC
        project_settings
        project_warings
        spdlog
)

target_include_directories(Log
    PUBLIC
        ${CMAKE_SOURCE_DIR}/include
        $ENV{MINGW_INCLUDE}
)

target_compile_definitions(Log
    PUBLIC
        SPDLOG_FMT_EXTERNAL
)