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
 * 2024-05-10 Ljubomir Kurij <ljubomir_kurij@protonmail.com>
 *
 * * invalid_reads.c: created.
 *
 * ========================================================================== */


/* ==========================================================================
 * Headers Include Section
 * ========================================================================== */

/* Related header */

/* System headers */

/* Standard Library headers */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* External libraries headers */
#include <argparse.h>


/* ==========================================================================
 * Macros Definitions Section
 * ========================================================================== */

#define APP_NAME "invalid_reads"
#define APP_VERSION "1.0"
#define APP_AUTHOR "Ljubomir Kurij"
#define APP_EMAIL "ljubomir_kurij@protonmail.com"
#define APP_COPYRIGHT_YEAR "2024"
#define APP_COPYRIGHT_HOLDER APP_AUTHOR
#define APP_LICENSE "GPLv3+"
#define APP_LICENSE_URL "http://gnu.org/licenses/gpl.html"
#define APP_DESCRIPTION                                                        \
  "This code explores a common source of errors in C: reading from\n"          \
  "invalid (freed) and unitialized memory. Specifically, we'll\n"              \
  "investigate what happens when you try to read past the end of an\n"         \
  "array, and when you try to read from a pointer that has been\n"             \
  "freed. The goal is to twofold:\n\n"                                         \
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

static int* get_powers_of_7(int n);
static void output_powers(int* powers, int n);
static char* get_alpha_letters(int len);
static void output_flavors(char** flavors);


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
    int* numbers = NULL;
    char* text = NULL;
    char* flavors[] = {
      "Chocolate",
      "Strawberry",
      "Vanilla",
      /* NULL terminator for the array of strings --------------------------

         This is a common mistake in C programs. The array of strings is not
         terminated with a NULL pointer. This is the reason we have a
         `Error #1: UNINITIALIZED READ: ...` error when we run this code with
         DrMemory. Note that the in this case, DrMemory will not report any
         line of code that caused the error.                                */
      NULL
    };

    numbers = get_powers_of_7(7);  /* Allocate memory for 7 integers */
    if (numbers) {
      /* Try to read 10 first elements from the allocated memory ------------

         This is an invalid read because we allocated memory for 7 integers,
         but we're trying to read 10 integers. This will cause the program to
         display the undefined behavior or even crash.

         If we run this code with a memory profiling tool like DrMemory, we'll
         see an error message like this:

         ```
         Error #1: UNADDRESSABLE ACCESS beyond heap bounds: ...
         ```

         with a stack trace that shows the exact line where
         the error occurred.                                                  */
      /* output_powers(numbers, 10); */
      output_powers(numbers, 7);
      free(numbers);  /* Free the allocated memory */
    }

    text = get_alpha_letters(19);
    printf("%s: Alpha characters\n", APP_NAME);
    printf("%s: =================\n", APP_NAME);
    printf("%s: %s\n", APP_NAME, text);
    puts("");
    free(text);

    output_flavors(flavors);

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
 * Function: get_powers_of_7
 * --------------------------------------------------------------------------
 * 
 * Description: Get the first n powers of 7
 * 
 * Parameters:
 *     n: Number of powers to calculate
 * 
 * Returns: Pointer to an array of n integers
 * 
 * -------------------------------------------------------------------------- */
static int* get_powers_of_7(int n) {
  int* ret = NULL;
  int i = 0;

  ret = calloc(n, sizeof(int));
  if (ret) {
    for (i = 0; i < n; i++) {
      ret[i] = (int) round(pow(7.0, 1.0 + (float) i));
    }
  }

  return ret;
}

/* --------------------------------------------------------------------------
 * Function: output_powers
 * --------------------------------------------------------------------------
 * 
 * Description: Output the powers of 7 (print array of n floats to stdout)
 * 
 * Parameters:
 *     powers: Pointer to an array of integers
 *         n: Number of elements in the array
 * 
 * Returns: void
 * 
 * -------------------------------------------------------------------------- */
static void output_powers(int* powers, int n) {
  int i = 0;

  printf("%s: Powers of 7\n", APP_NAME);
  printf("%s: ==========\n", APP_NAME);
  for (i = 0; i < n; i++) {
    printf("%s:\t7^%d = %d\n", APP_NAME, 1 + i, powers[i]);
  }
  puts("");
}

/* --------------------------------------------------------------------------
 * Function: get_alpha_letters
 * --------------------------------------------------------------------------
 * 
 * Description: Get the first len letters of the alphabet
 * 
 * Parameters:
 *     len: Number of letters to generate
 * 
 * Returns: Pointer to a string of len characters
 * 
 * -------------------------------------------------------------------------- */
static char* get_alpha_letters(int len) {
  char* text = NULL;
  int i = 0;

  text = calloc(len + 1, sizeof(char));
  if (text) {
    for (i = 0; i < len; i++) {
      /* NOTE: This is handy for cycling through the range (i % 26) */
      text[i] = 65 + (i % 26);
    }

    /* Free the memory allocated for the string before returning it ---------

       This is a common mistake in C programs. The memory allocated for the
       string is not freed before returning it. This is the reason we have a
       `Error #1: UNINITIALIZED READ: ...` error when we run this code with
       DrMemory. Note that the in this case, DrMemory will not report any
       line of code that caused the error.                                    */
    /* free(text); */
  }

  return text;
}

/* --------------------------------------------------------------------------
 * Function: output_flavors
 * --------------------------------------------------------------------------
 * 
 * Description: Output the flavors (print array of strings to stdout)
 * 
 * Parameters:
 *     flavors: Pointer to an array of strings
 * 
 * Returns: void
 * 
 * -------------------------------------------------------------------------- */
static void output_flavors(char** flavors) {
  printf("%s: Flavors\n", APP_NAME);
  printf("%s: ========\n", APP_NAME);
  while (*flavors) {
    printf("%s:\t%s\n", APP_NAME, *flavors);
    flavors++;
  }
}