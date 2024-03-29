macro(enable_cppcheck CPPCHECK_OPTIONS)
  find_program(CPPCHECK cppcheck)
  if(CPPCHECK)

    if(CMAKE_GENERATOR MATCHES ".*Visual Studio.*")
      set(CPPCHECK_TEMPLATE "vs")
    else()
      set(CPPCHECK_TEMPLATE "gcc")
    endif()

    if("${CPPCHECK_OPTIONS}" STREQUAL "")
      # Enable all warnings that are actionable by the user of this toolset
      # style should enable the other 3, but we'll be explicit just in case
      set(CMAKE_CXX_CPPCHECK
          ${CPPCHECK}
          --template=${CPPCHECK_TEMPLATE}
          --enable=style,performance,warning,portability
          --inline-suppr
          # We cannot act on a bug/missing feature of cppcheck
          --suppress=internalAstError
          # if a file does not have an internalAstError, we get an unmatchedSuppression error
          --suppress=unmatchedSuppression
          --inconclusive)
    else()
      # if the user provides a CPPCHECK_OPTIONS with a template specified, it will override this template
      set(CMAKE_CXX_CPPCHECK ${CPPCHECK} --template=${CPPCHECK_TEMPLATE} ${CPPCHECK_OPTIONS})
    endif()

    if(NOT
       "${CMAKE_CXX_STANDARD}"
       STREQUAL
       "")
      set(CMAKE_CXX_CPPCHECK ${CMAKE_CXX_CPPCHECK} --std=c++${CMAKE_CXX_STANDARD})
    endif()
    if(WARNINGS_AS_ERRORS)
      list(APPEND CMAKE_CXX_CPPCHECK --error-exitcode=2)
    endif()
  else()
    message(${WARNING_MESSAGE} "cppcheck requested but executable not found")
  endif()
endmacro()

# TODO: #1 Clang tidy does not work

macro(enable_clang_tidy)
  find_program(CLANGTIDY clang-tidy)
  if(CLANGTIDY)
    # construct the clang-tidy command line
    
    set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
    set(CMAKE_CXX_USE_RESPONSE_FILE_FOR_INCLUDES Off)
    set(CMAKE_CXX_CLANG_TIDY ${CLANGTIDY} -extra-arg=-Wno-unknown-warning-option)
    set(CMAKE_CXX_CLANG_TIDY ${CMAKE_CXX_CLANG_TIDY} -p ${CMAKE_BINARY_DIR})
    # set standard
    if(NOT
       "${CMAKE_CXX_STANDARD}"
       STREQUAL
       "")
      if("${CMAKE_CXX_CLANG_TIDY_DRIVER_MODE}" STREQUAL "cl")
        set(CMAKE_CXX_CLANG_TIDY ${CMAKE_CXX_CLANG_TIDY} -extra-arg=/std:c++${CMAKE_CXX_STANDARD})
      else()
        set(CMAKE_CXX_CLANG_TIDY ${CMAKE_CXX_CLANG_TIDY} -extra-arg=-std=c++${CMAKE_CXX_STANDARD})
      endif()
    endif()
  else()
    message(${WARNING_MESSAGE} "clang-tidy requested but executable not found")
  endif()
endmacro()