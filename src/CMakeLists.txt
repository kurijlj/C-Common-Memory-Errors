# =============================================================================
# Build source targets
# =============================================================================

# Print message to console that we are building the source targets
message(STATUS "Going through ./src")

# -----------------------------------------------------------------------------
# Target: dummy
# -----------------------------------------------------------------------------
#
# Description: A dummy target that does nothing. This is useful for testing
#              the build tool. And also for buidling the tests.
#
# -----------------------------------------------------------------------------

# Show message that we are building the `dummy' target
message(STATUS "Configuring the `dummy' target")

# Add a dummy target
add_custom_target(dummy
    COMMAND ${CMAKE_COMMAND} -E echo "Dummy target"
)


# -----------------------------------------------------------------------------
# Target: app
# -----------------------------------------------------------------------------
#
# Description: The main application target. This is the target that is built
#              from the framework source code.
#
# -----------------------------------------------------------------------------

# Show message that we are building the `app' target
message(STATUS "Configuring the `app' target")

# Set the source files for the `app' target
add_executable(app app.c)

# Link the `app` target with the required libraries
target_link_libraries(app PRIVATE
    argparse
    gsl
)

# Include the required directories for the `app' target
target_include_directories(app PRIVATE
    ${ARGPARSE_INCLUDE_DIR}
    ${GSL_INCLUDE_DIR}
)
