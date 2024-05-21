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
 * 2024-05-21 Ljubomir Kurij <ljubomir_kurij@protonmail.com>
 *
 * * invalid_frees.c: created.
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
#include <string.h>

/* External libraries headers */
#include <argparse.h>

/* ==========================================================================
 * Macros Definitions Section
 * ========================================================================== */

#define APP_NAME "invalid_frees"
#define APP_VERSION "1.0"
#define APP_AUTHOR "Ljubomir Kurij"
#define APP_EMAIL "ljubomir_kurij@protonmail.com"
#define APP_COPYRIGHT_YEAR "2024"
#define APP_COPYRIGHT_HOLDER APP_AUTHOR
#define APP_LICENSE "GPLv3+"
#define APP_LICENSE_URL "http://gnu.org/licenses/gpl.html"
#define APP_DESCRIPTION                                                        \
  "This code explores a common source of errors in C: freeing memory that\n"   \
  "has already been freed.\n"                                                  \
  "...\n"                                                                      \
  "The goal is to twofold:\n\n"                                                \
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

static char *even_or_blank(int i);
static void print_evens(int highest);
static int *get_odds(int highest, long int *num_odds);
static void show_odds(int highest);
static void splitter(char *input, char **prefix, char **suffix);
static void print_and_free_ids(char **alphas, char **nums, int num_ids);
static void do_the_splits();

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
    print_evens(110);
    show_odds(13);
    do_the_splits();

    /* End of main module code. Print exit message -------------------------- */
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

static char *even_or_blank(int i) {
  char buf[4] = ""; // big enough for 2 digits + null terminator

  if (i >= 100) {
    return "Sorry, this number is too large.";
  }

  if (i % 2 == 0) {
    snprintf(buf, sizeof(buf), "%d", i);
    return strdup(buf);
  } else {
    return "";  /* Blank or empty string!? */
  }
}

static void print_evens(int highest) {
  char *text = NULL;
  int i = 0;

  for (i = 0; i <= highest; i++) {
    text = even_or_blank(i);
    if (text) {
      if (strlen(text) > 0) {
        printf("%s\n", text);
      }
      /* Trying to free a string literal -------------------------------------

         The function even_or_blank() returns a string literal when the input
         number is odd. The string literal is a constant string that is stored
         on the stack and is in the read-only memory. Attempting to free a
         string literal results in a crash.

         If we run this part of the code with a memory profiler (i.e., DrMemory)
         we will see an error message like this:

         ```
         Error #1: INVALID HEAP ARGUMENT to free ...
         ```

         with a stack trace that points to the line where the free() function
         is called.
      */
      /* free(text); */
    }
  }
}

static int *get_odds(int highest, long int *num_odds) {
  int *odds = NULL;
  long int i = 0;

  *num_odds = (highest + 1) / 2;
  if (*num_odds <= 0) {
    return NULL;
  }

  odds = calloc(*num_odds, sizeof(int));
  if (odds) {
    for (i = 0; i < *num_odds; i++) {
      odds[i] = i * 2 + 1;
    }
  }

  return odds;
}

static void show_odds(int highest) {
  int *odds = NULL;
  int i = 0;
  long int num_odds = 0;

  odds = get_odds(highest, &num_odds);
  if (odds) {
    for (i = 0; i < num_odds; i++) {
      printf("%d\n", odds[i]);
    }
    free(odds);
  }
}

static void splitter(char *input, char **prefix, char **suffix) {
  char *copied = NULL;

  copied = strdup(input);
  if (copied) {
    *prefix = copied;
    while (*copied) {
      if (*copied == '-') {
        *copied = '\0';
        *suffix = copied + 1;
        break;
      }
      copied++;
    }
  }
}

static void print_and_free_ids(char **alphas, char **nums, int num_ids) {
  int i = 0;

  for (i = 0; i < num_ids; i++) {
    printf("ID %d: %s-%s\n", i, alphas[i], nums[i]);
    free(alphas[i]);
    free(nums[i]);
  }

  free(alphas);
  free(nums);
}

static void do_the_splits() {
  char *ids[] = {
    "THX-1138",
    "U-62",
    "DS-9",
    "FN-2187",
    NULL
  };
  const int num_ids = sizeof(ids) / sizeof(char *) - 1;
  char *alphas[4] = {};
  char *nums[4] = {};
  int i = 0;

  for (i = 0; i < num_ids; i++) {
    splitter(ids[i], &alphas[i], &nums[i]);
  }

  print_and_free_ids(alphas, nums, num_ids);
}