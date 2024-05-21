# =============================================================================
# Build source targets
# =============================================================================

# Print message to console that we are building the source targets
message(STATUS "Going through ./src")


# -----------------------------------------------------------------------------
# Target: invalid_frees
# -----------------------------------------------------------------------------
#
# Description: This code explores a common source of errors in C: freeing
#              memory that has already been freed.
#              ...
#              The goal is to twofold:
#
#              1. Observe compiler warnings: We'll compile the code and see what
#                 warnings the compiler generates for this practice.
#              2. Explore memory profiling tool output: We'll use a memory
#                 profiling tool like DrMemory to see if it detects any issues.
#
# -----------------------------------------------------------------------------

# Show message that we are building the `invalid_frees` target
message(STATUS "Configuring the `invalid_frees` target")

# Set the source files for the `invalid_frees` target
add_executable(invalid_frees invalid_frees.c)

# Link the `invalid_frees` target with the required libraries
target_link_libraries(invalid_frees PRIVATE
    argparse
    ${MATH_LIBRARY}
)

# Include the required directories for the `invalid_frees` target
target_include_directories(invalid_frees PRIVATE
    ${ARGPARSE_INCLUDE_DIR}
)


# -----------------------------------------------------------------------------
# Target: invalid_frees_exercise
# -----------------------------------------------------------------------------
#
# Description: A solution to the exercise regarding invalid reads.
#
# -----------------------------------------------------------------------------

# Show message that we are building the `invalid_frees_exercise` target
message(STATUS "Configuring the `invalid_frees_exercise` target")

# Set the source files for the `invalid_frees_exercise` target
add_executable(invalid_frees_exercise invalid_frees_exercise.c)

# Link the `invalid_frees_exercise` target with the required libraries
target_link_libraries(invalid_frees_exercise PRIVATE
    argparse
)

# Include the required directories for the `invalid_frees_exercise` target
target_include_directories(invalid_frees_exercise PRIVATE
    ${ARGPARSE_INCLUDE_DIR}
)


# -----------------------------------------------------------------------------
# Target: invalid_reads
# -----------------------------------------------------------------------------
#
# Description: This code explores a common source of errors in C: reading from
#              invalid (freed) and unitialized memory. Specifically, we'll
#              investigate what happens when you try to read past the end of an
#              array, and when you try to read from a pointer that has been
#              freed. The goal is to twofold:
#
#              1. Observe compiler warnings: We'll compile the code and see what
#                 warnings the compiler generates for this practice.
#              2. Explore memory profiling tool output: We'll use a memory
#                 profiling tool like DrMemory to see if it detects any issues.
#
# -----------------------------------------------------------------------------

# Show message that we are building the `invalid_reads` target
message(STATUS "Configuring the `invalid_reads` target")

# Set the source files for the `invalid_reads` target
add_executable(invalid_reads invalid_reads.c)

# Link the `invalid_reads` target with the required libraries
if ("${CMAKE_C_COMPILER_ID}" STREQUAL "GNU")
    # If we are using GCC, we need to link the math library explicitly
    message(STATUS "Using GCC, linking the math library explicitly ...")

    find_library(MATH_LIBRARY m)
    if (NOT MATH_LIBRARY)
        message(FATAL_ERROR "Could not find the math library")
    endif()
    target_link_libraries(invalid_reads PRIVATE
        argparse
        ${MATH_LIBRARY}
    )
else()
    target_link_libraries(invalid_reads PRIVATE
        argparse
        ${MATH_LIBRARY}
    )
endif()

# Include the required directories for the `invalid_reads` target
target_include_directories(invalid_reads PRIVATE
    ${ARGPARSE_INCLUDE_DIR}
)


# -----------------------------------------------------------------------------
# Target: invalid_reads_exercise
# -----------------------------------------------------------------------------
#
# Description: A solution to the exercise regarding invalid reads.
#
# -----------------------------------------------------------------------------

# Show message that we are building the `invalid_reads_exercise` target
message(STATUS "Configuring the `invalid_reads_exercise` target")

# Set the source files for the `invalid_reads_exercise` target
add_executable(invalid_reads_exercise invalid_reads_exercise.c)

# Link the `invalid_reads_exercise` target with the required libraries
target_link_libraries(invalid_reads_exercise PRIVATE
    argparse
)

# Include the required directories for the `invalid_reads_exercise` target
target_include_directories(invalid_reads_exercise PRIVATE
    ${ARGPARSE_INCLUDE_DIR}
)


# -----------------------------------------------------------------------------
# Target: invalid_writes
# -----------------------------------------------------------------------------
#
# Description: This code explores a common source of errors in C: writing to
#              invalid (freed) and unitialized memory.
#
#              ...
#
#              The goal is to twofold:
#
#              1. Observe compiler warnings: We'll compile the code and see what
#                 warnings the compiler generates for this practice.
#              2. Explore memory profiling tool output: We'll use a memory
#                 profiling tool like DrMemory to see if it detects any issues.
#
# -----------------------------------------------------------------------------

# Show message that we are building the `invalid_writes` target
message(STATUS "Configuring the `invalid_writes` target")

# Set the source files for the `invalid_writes` target
add_executable(invalid_writes invalid_writes.c)

# Link the `invalid_writes` target with the required libraries
  target_link_libraries(invalid_writes PRIVATE
      argparse
      ${MATH_LIBRARY}
  )

# Include the required directories for the `invalid_writes` target
target_include_directories(invalid_writes PRIVATE
    ${ARGPARSE_INCLUDE_DIR}
)


# -----------------------------------------------------------------------------
# Target: invalid_writes_exercise
# -----------------------------------------------------------------------------
#
# Description: A solution to the exercise regarding invalid writes.
#
# -----------------------------------------------------------------------------

# Show message that we are building the `invalid_writes_exercise` target
message(STATUS "Configuring the `invalid_writes_exercise` target")

# Set the source files for the `invalid_writes_exercise` target
add_executable(invalid_writes_exercise invalid_writes_exercise.c)

# Link the `invalid_writes_exercise` target with the required libraries
target_link_libraries(invalid_writes_exercise PRIVATE
    argparse
)

# Include the required directories for the `invalid_writes_exercise` target
target_include_directories(invalid_writes_exercise PRIVATE
    ${ARGPARSE_INCLUDE_DIR}
)


# -----------------------------------------------------------------------------
# Target: uninitalized_values
# -----------------------------------------------------------------------------
#
# Description: This code explores a common source of errors in C: reading from
#              uninitialized memory. Specifically, we'll investigate what
#              happens when you try to read from a pointer that points to a
#              string that hasn't been assigned a value. The goal is to twofold:
#
#              1. Observe compiler warnings: We'll compile the code and see what
#                 warnings the compiler generates for this practice.
#              2. Explore memory profiling tool output: We'll use a memory
#                 profiling tool like DrMemory to see if it detects any issues.
#
# -----------------------------------------------------------------------------

# Show message that we are building the `uninitlaized_values` target
message(STATUS "Configuring the `uninitialized_values` target")

# Set the source files for the `uninitialized_values` target
add_executable(uninitialized_values uninitialized_values.c)

# Link the `uninitialized_values` target with the required libraries
target_link_libraries(uninitialized_values PRIVATE
    argparse
)

# Include the required directories for the `uninitialized_values` target
target_include_directories(uninitialized_values PRIVATE
    ${ARGPARSE_INCLUDE_DIR}
)


# -----------------------------------------------------------------------------
# Target: uninitalized_values_exercise
# -----------------------------------------------------------------------------
#
# Description: A solution to the exercise regarding uninitialized values.
#
# -----------------------------------------------------------------------------

# Show message that we are building the `uninitlaized_values_exercise` target
message(STATUS "Configuring the `uninitialized_values_exercise` target")

# Set the source files for the `uninitialized_values_exercise` target
add_executable(uninitialized_values_exercise uninitialized_values_exercise.c)

# Link the `uninitialized_values_exercise` target with the required libraries
target_link_libraries(uninitialized_values_exercise PRIVATE
    argparse
)

# Include the required directories for the `uninitialized_values_exercise`
# target
target_include_directories(uninitialized_values_exercise PRIVATE
    ${ARGPARSE_INCLUDE_DIR}
)
