function(
    COPY_RESOURCES
    target
    folder
)
string(REGEX REPLACE "[/\\]+$" "" folder ${folder})
string(REGEX MATCH "[^/\\]+$" folder_name ${folder})
if(${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC)
    add_custom_command(
        TARGET ${target} PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${folder}  ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${CMAKE_BUILD_TYPE}/${folder_name}
    )
else()
    add_custom_command(
        TARGET ${target} PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${folder}  ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${CMAKE_BUILD_TYPE}/${folder_name}
    )
endif()
endfunction()