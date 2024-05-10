# ============================================================================
# A CMake build script for the C CLI application
# ============================================================================

# Define the minimum required version of CMake
cmake_minimum_required (VERSION 3.12...3.40)

# Define the project name and version
project (
    c_common_memory_errors
    VERSION 0.1
    DESCRIPTION "This codebase explores a common source of memory errors in C"
    HOMEPAGE_URL "https://github.com/kurijlj/C-Common-Memory-Errors"
    LANGUAGES C
    )

# Set the C++ standard to C++17 and make it required
set (CMAKE_C_STANDARD 11)
set (CMAKE_C_STANDARD_REQUIRED ON)

# Set the build type to Release if not specified
if (NOT CMAKE_BUILD_TYPE)
    set (CMAKE_BUILD_TYPE Release)
endif ()

# Set to build with shared libraries by default
option (BUILD_SHARED_LIBS "Build using shared libraries" ON)

# Set the output directory for the executable
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Add the argparse library
if (NOT DEFINED ARGPARSE_SHARED)
    option(ARGPARSE_SHARED "Build shared library" OFF)  # Default to OFF
endif ()

option(ARGPARSE_STATIC "Build static library" OFF)
add_subdirectory ("${PROJECT_SOURCE_DIR}/extern/argparse")
# Set the include directory for argparse (library CMake variable is not set)
set (ARGPARSE_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/extern/argparse")

# Add the source files directory
add_subdirectory ("${PROJECT_SOURCE_DIR}/src")