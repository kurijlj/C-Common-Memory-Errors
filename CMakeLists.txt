# ============================================================================
# A CMake build script for the C CLI application
# ============================================================================

# Define the minimum required version of CMake
cmake_minimum_required (VERSION 3.12...3.40)

# Define the project name and version
project (
    cli_framework
    VERSION 0.1
    DESCRIPTION "A simple C CLI application"
    HOMEPAGE_URL ""
    LANGUAGES C CXX
    )

# Set the C++ standard to C++17 and make it required
set (CMAKE_C_STANDARD 99)
set (CMAKE_C_STANDARD_REQUIRED ON)

# Set the C++ standard to C++17 and make it required
set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

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

# Add the GNU Scientific Library
set (NO_AMPL_BINDINGS ON)  # Disable AMPL bindings
include(FetchContent)
FetchContent_Declare(
    gsl
    GIT_REPOSITORY https://github.com/ampl/gsl.git
    GIT_TAG v2.7.0
)
FetchContent_MakeAvailable(gsl)

# Add the source files directory
add_subdirectory ("${PROJECT_SOURCE_DIR}/src")

# Check if the tests are enabled
if (NOT DEFINED BUILD_TESTS)
    option (BUILD_TESTS "Build the tests" OFF)  # Default to OFF
endif ()

# Add the test files directory if the tests are enabled
if (BUILD_TESTS)
    set (munit_SOURCE_DIR "${PROJECT_SOURCE_DIR}/extern/munit")
    set (munit_sources "${munit_SOURCE_DIR}/munit.c")
	add_library(munit OBJECT ${munit_sources})
    set (MUNIT_INCLUDE_DIR "${munit_SOURCE_DIR}")
    add_subdirectory ("${PROJECT_SOURCE_DIR}/tests")
endif ()