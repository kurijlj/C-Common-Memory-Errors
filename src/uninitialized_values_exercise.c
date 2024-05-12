/* ==========================================================================
 *  Copyright (C) 2024 Ljubomir Kurij <ljubomir_kurij@protonmail.com>
 *
 * This file is part of "C Common Memory Errors".
 *
 * "C Common Memory Errors" is free software: you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or (at your
 * option) any later version.
 *
 * "C Common Memory Errors" is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General
 * Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with Focus Precision Analyze. If not, see <https://www.gnu.org/licenses/>.
 * ========================================================================== */


/* ==========================================================================
 *
 * 2024-05-12 Ljubomir Kurij <ljubomir_kurij@protonmail.com>
 *
 * * uninitalized_values_exercise.c: created.
 *
 * ========================================================================== */


/* ==========================================================================
 * Headers Include Section
 * ========================================================================== */

/* Related header */

/* System headers */

/* Standard Library headers */
#include <stdio.h>
#include <stdlib.h>

/* External libraries headers */
#include <argparse.h>


/* ==========================================================================
 * Macros Definitions Section
 * ========================================================================== */

#define APP_NAME "uninitalized_values_exercise"
#define APP_VERSION "1.0"
#define APP_AUTHOR "Ljubomir Kurij"
#define APP_EMAIL "ljubomir_kurij@protonmail.com"
#define APP_COPYRIGHT_YEAR "2024"
#define APP_COPYRIGHT_HOLDER APP_AUTHOR
#define APP_LICENSE "GPLv3+"
#define APP_LICENSE_URL "http://gnu.org/licenses/gpl.html"
#define APP_DESCRIPTION                                                        \
  "This code explores a common source of errors in C: reading from\n"          \
  "uninitialized memory. Specifically, we'll investigate what happens when\n"  \
  "you try to read from a pointer that points to a string that hasn't been\n"  \
  "assigned a value. The goal is to twofold:\n\n"                              \
  "  1. Observe compiler warnings: We'll compile the code and see what\n"      \
  "     warnings the compiler generates for this practice.\n"                  \
  "  2. Explore memory profiling tool output: We'll use a memory profiling\n"  \
  "     tool like DrMemory to see if it detects any issues."
#ifdef _WIN32
#define APP_USAGE_A APP_NAME ".exe [OPTION]..."
#else
#define APP_USAGE_A APP_NAME " [OPTION]..."
#endif /* End of platform specific macro definition */
#define APP_EPILOGUE "\nReport bugs to <" APP_EMAIL ">."


/* ==========================================================================
 * Global Variables Section
 * ========================================================================== */

static const char *const kUsages[] = {
    APP_USAGE_A,
    NULL,
};


/* ==========================================================================
 * Utility Function Declarations Section
 * ========================================================================== */

int short_usage(struct argparse *self, const struct argparse_option *option);
int version_info(struct argparse *self, const struct argparse_option *option);


/* ==========================================================================
 * User Defined Function Declarations Section
 * ========================================================================== */

static int abs_sum(int a, int b);
static int get_result(int base_num);


/* ==========================================================================
 * Main Function Section
 * ========================================================================== */

int main(int argc, char **argv) {

  int usage = 0;
  int version = 0;

  /* Define command line options */
  struct argparse_option options[] = {
      OPT_GROUP("general options"),
      OPT_HELP(),
      OPT_BOOLEAN('\0', "usage", &usage, "give a short usage message",
                  &short_usage, 0, 0),
      OPT_BOOLEAN('V', "version", &version, "print program version",
                  &version_info, 0, 0),
      OPT_END(),
  };

  /* Parse command line arguments */
  struct argparse argparse;
  argparse_init(&argparse, options, kUsages, 0);
  argparse_describe(&argparse, APP_DESCRIPTION, APP_EPILOGUE);
  argc = argparse_parse(&argparse, argc, argv);

  /* Check if usage or version options were given */
  if (usage != 0 || version != 0) {
    exit(EXIT_SUCCESS);
  }

  /* Main module code */
  int status = EXIT_SUCCESS;

  if (argc == 0) {
    /* No arguments were given */
    int base_num = 0;
    int result = get_result(base_num);
    printf("%s: Result is %d\n", APP_NAME, result);

    printf("%s: Program execution complete!\n", APP_NAME);
  }

  return status;
}


/* ==========================================================================
 * Utility Function Definitions Section
 * ========================================================================== */

/* --------------------------------------------------------------------------
 * Function: short_usage
 * --------------------------------------------------------------------------
 *
 * Description: Print a short usage message
 *
 * Parameters:
 *      self: Pointer to argparse structure
 *    option: Pointer to argparse option structure
 *
 * Returns: Number of characters printed
 *
 * -------------------------------------------------------------------------- */
int short_usage(struct argparse *self, const struct argparse_option *option) {
#ifdef _WIN32
  return fprintf(stdout, "%s %s\n%s%s%s\n", "Usage:", APP_USAGE_A, "Try `",
                 APP_NAME, ".exe -h' for more information.");
#else
  return fprintf(stdout, "%s %s\n%s%s%s\n", "Usage:", APP_USAGE_A, "Try `",
                 APP_NAME, " -h' for more information.");
#endif /* End of platform specific code */
}

/* --------------------------------------------------------------------------
 * Function: version_info
 * --------------------------------------------------------------------------
 *
 * Description: Print program version information
 *
 * Parameters:
 *      self: Pointer to argparse structure
 *    option: Pointer to argparse option structure
 *
 * Returns: Number of characters printed
 *
 * -------------------------------------------------------------------------- */
int version_info(struct argparse *self, const struct argparse_option *option) {
  return fprintf(stdout, "%s %s %s %s %s\n%s %s: %s <%s>\n%s\n%s\n", APP_NAME,
                 APP_VERSION, "Copyright (c)", APP_COPYRIGHT_YEAR, APP_AUTHOR,
                 "License", APP_LICENSE, "GNU GPL version 3 or later",
                 APP_LICENSE_URL,
                 "This is free software: you are free "
                 "to change and redistribute it.",
                 "There is NO WARRANTY, to the extent permitted by law.");
}


/* ==========================================================================
 * User Defined Function Definitions Section
 * ========================================================================== */

/* --------------------------------------------------------------------------
 * Function: abs_sum
 * --------------------------------------------------------------------------
 *
 * Description: Calculate the absolute sum of two integers
 *
 * Parameters:
 *      a: First integer
 *      b: Second integer
 *
 * Returns: Absolute sum of `a` and `b`
 *
 * -------------------------------------------------------------------------- */
static int abs_sum(int a, int b) {
  if (a < 0) {
    a *= -1;
  }

  if (b < 0) {
    b *= -1;
  }

  return a + b;
}

/* --------------------------------------------------------------------------
 * Function: get_result
 * --------------------------------------------------------------------------
 *
 * Description: Get the result of the absolute sum of two integers
 *
 * Parameters:
 *      base_num: Base number
 *
 * Returns: Absolute sum of `base_num` and `user_entered`
 *
 * -------------------------------------------------------------------------- */
static int get_result(int base_num) {
  int user_entered;

  printf("%s: Enter a number: ", APP_NAME);
  scanf("%d", &user_entered);

  return abs_sum(base_num, user_entered);
}