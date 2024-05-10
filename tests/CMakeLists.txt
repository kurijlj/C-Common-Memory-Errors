# =============================================================================
# Build test targets
# =============================================================================

# Print message to console that we are building the source targets
message(STATUS "Going through ./tests")


# -----------------------------------------------------------------------------
# Target: dummy_test
# -----------------------------------------------------------------------------
#
# Description: A dummy test target that uses the `munit' framework to test
#              the basic functionality of the framework.
#
# -----------------------------------------------------------------------------

# Show message that we are building the `dummy_test' target
message(STATUS "Configuring the `dummy_test' target")

# Set the source files for the `dummy_test' target
add_executable(dummy_test dummy_test.c)

# Link the `dummy_test' target with the `munit' framework
target_link_libraries(dummy_test PRIVATE
    munit
)

# Include the required directories for the `dummy_test' target
target_include_directories(dummy_test PRIVATE
    ${MUNIT_INCLUDE_DIR}
)

# Enable testing for the project
enable_testing()

# Add the `dummy_test' target to the list of tests
add_test(NAME dummy_test COMMAND dummy_test)