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

    set(conanfile ${CMAKE_SOURCE_DIR}/conanfile.txt)
    set(conanfile_cmake ${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)

    string(FIND ${CMAKE_CXX_COMPILER_VERSION} "." compiler_first_per)
    string(SUBSTRING ${CMAKE_CXX_COMPILER_VERSION} 0 ${compiler_first_per} major_compiler)

    string(REGEX MATCH "^[0-9]+[.][0-9]+" major_minor_compiler ${CMAKE_CXX_COMPILER_VERSION})
    execute_process(COMMAND ${conan} install ${CMAKE_SOURCE_DIR}/
        -s os=${os}
        -s compiler=${compiler}
        -s compiler.libcxx=libstdc++11
        -s compiler.version=${major_minor_compiler}
        COMMAND_ECHO STDOUT
        RESULT_VARIABLE return_code
    )

    if (NOT ${return_code} EQUAL 0)
        message(FATAL_ERROR "conan install command failed.")
    endif()
    # include(${conanfile_cmake})
    # conan_basic_setup()
    # conan_check_compiler()
endmacro()