add_library(glad STATIC glad.c)
target_include_directories(glad PRIVATE ${third_party_include})

set_target_properties(glad
    PROPERTIES
        C_CPPCHECK ""
        C_CLANG_TIDY ""
)