# =============================================================================
# Build source targets
# =============================================================================

# Print message to console that we are building the source targets
message(STATUS "Going through ./src")


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
