cmake_minimum_required (VERSION 2.8)

# object_file.cpp includes flex generated code which emits warnings. Disable these
# only for this file.
ty_clang_file_disable_warnings("${CMAKE_CURRENT_SOURCE_DIR}/detail/object_file.cpp" "unused-variable")

tycho_add_library(mirror "tycore;tyglass;tyio" "libs")



