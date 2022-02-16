if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    MESSAGE(STATUS "Setting build type to 'Debug' as none was specified.")
    set(CMAKE_BUILD_TYPE
        Debug
        CACHE STRING "Choose the type of build." FORCE
    )

    set_property(
        CACHE CMAKE_BUILD_TYPE
        PROPERTY STRINGS
            "Debug"
            "Release"
            "RelWithDebInfo"
            "MinSizeRel"
    )
endif()

function(set_project_settings project_name)
    if(CMAKE_CXX_COMPILER_ID MATCHES ".*Clang")
      option(ENABLE_BUILD_WITH_TIME_TRACE "Enable -ftime-trace to generate time tracing .json files on clang" OFF)
      if(ENABLE_BUILD_WITH_TIME_TRACE)
        target_compile_options(${project_name} INTERFACE -ftime-trace)
      endif()
    endif()

    target_compile_features(${project_name} INTERFACE cxx_std_17)
endfunction()