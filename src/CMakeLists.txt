add_subdirectory(Meiosis)


if (${Meiosis_BUILD_SANDBOX})
    add_subdirectory(Sandbox)
endif()


if (${Meiosis_BUILD_TESTS})
    add_subdirectory(Tests)
endif()