add_library(glad STATIC glad.c)
target_include_directories(glad PRIVATE ${third_party_include})