macro(conan_install)
    find_program(conan conan)
    if(${CMAKE_HOST_SYSTEM_NAME} STREQUAL Darwin)
        set(os Macos)
    else()
        set(os ${CMAKE_HOST_SYSTEM_NAME})
    endif()

    if(${CMAKE_CXX_COMPILER_ID} STREQUAL GNU)
        set(compiler gcc)
    elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL AppleClang)
        set(compiler apple-clang)
    else()
        message(FATAL_ERROR "Unknown compiler: ${CMAKE_CXX_COMPILER_ID}")
    endif()

    list(APPEND CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR}/conan)
    list(APPEND CMAKE_PREFIX_PATH ${CMAKE_BINARY_DIR}/conan)

    set(conanfile ${CMAKE_BINARY_DIR}/conan/conanfile.txt)
    set(conanfile_cmake ${CMAKE_BINARY_DIR}/conan/conanbuildinfo.cmake)

    string(FIND ${CMAKE_CXX_COMPILER_VERSION} "." compiler_first_per)
    string(SUBSTRING ${CMAKE_CXX_COMPILER_VERSION} 0 ${compiler_first_per} major_compiler)

    string(REGEX MATCH "^[0-9]+[.][0-9]+" major_minor_compiler ${CMAKE_CXX_COMPILER_VERSION})
    execute_process(COMMAND ${conan} install ${CMAKE_SOURCE_DIR}/
        -s os=${os}
        -s compiler=${compiler}
        -s compiler.libcxx=libstdc++11
        -s compiler.version=${major_minor_compiler}
        --build=missing
        --no-imports
        -if ${CMAKE_BINARY_DIR}/conan/
        -e CXX=${CMAKE_CXX_COMPILER}
        -e CC=${CMAKE_C_COMPILER}
        COMMAND_ECHO STDOUT
        RESULT_VARIABLE return_code
    )

    if (NOT ${return_code} EQUAL 0)
        message(FATAL_ERROR "conan install command failed.")
    endif()

    set(tmp_import_dir ${CMAKE_SOURCE_DIR}/build/Debug-lib/)
    link_directories(${tmp_import_dir})
    execute_process(COMMAND ${conan} imports ${CMAKE_SOURCE_DIR}/
        -if ${CMAKE_BINARY_DIR}/conan
        -imf ${tmp_import_dir}
        COMMAND_ECHO STDOUT
        RESULT_VARIABLE return_code
    )
    # include(${CMAKE_BINARY_DIR}/conan_paths.cmake)
    if (NOT ${return_code} EQUAL 0)
        message(FATAL_ERROR "conan import command failed.")
    endif()
    # include(${conanfile_cmake})
    # conan_basic_setup()
    # conan_check_compiler()
endmacro()