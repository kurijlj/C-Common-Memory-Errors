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
  "has already been freed. In particular, we'll look at the\n"                 \
  "following cases:\n"                                                         \
  "  1. Trying to free a string literal\n"                                     \
  "  2. Trying to free invalid memory reference (i.e. ordinary variable)\n"    \
  "  3. Trying to free a block of memory inside the already freed block\n"     \
  "  4. Trying to free the memory that is not dynamically allocated\n"         \
  "     (i.e. stack memory)\n"                                                 \
  "\n"                                                                         \
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

static char *even_or_blank(int i, char **err);
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

/* --------------------------------------------------------------------------
 * Function: even_or_blank
 * --------------------------------------------------------------------------
 *
 * Description: Return a string representation of an even number or an empty
 *              string for an odd number. If the number is too large (>= 100),
 *              return an NULL reference, and set the error message.
 * Parameters:
 *      i: Integer number to check
 *
 * Returns: String representation of the number or an empty string
 *
 * Note: The function returns a reference to allocated memory when the input
 *       number is even, and a reference to a read-only memory location when the
 *       number is odd, or the number is too large. This is a common source of
 *       memory errors in C. To prevent this, the returned reference should be
 *       consistent, either by allocating memory for all cases, or by returning
 *       a reference to a read-only memory location for all cases.
 *
 * -------------------------------------------------------------------------- */
static char *even_or_blank(int i, char **err) {
  char buf[4] = ""; // big enough for 2 digits + null terminator

  *err = NULL;
  if (i >= 100) {
    /* return "Sorry, this number is too large."; */
    *err = "Sorry, this number is too large.";
    return NULL;
  }

  if (i % 2 == 0) {
    snprintf(buf, sizeof(buf), "%d", i);
    return strdup(buf);
  } else {
    /* return ""; */
    return strdup("");
  }
}

/* --------------------------------------------------------------------------
 * Function: print_evens
 * --------------------------------------------------------------------------
 *
 * Description: Print even numbers up to a given number. If the number is too
 *              large, print an error message. The function uses the
 *              `even_or_blank` function to determine if a number is even or
 *              too large. The function is responsible for freeing the memory
 *              allocated by the `even_or_blank` function.
 *
 * Parameters:
 *      highest: Highest number to print
 *
 * Returns: None
 *
 * -------------------------------------------------------------------------- */
static void print_evens(int highest) {
  char *text = NULL;
  char *err = NULL;
  int i = 0;

  for (i = 0; i <= highest; i++) {
    text = even_or_blank(i, &err);
    if (text) {
      if (strlen(text) > 0) {
        printf("%s\n", text);
      }
      /* Trying to free a string literal -------------------------------------

         The function even_or_blank() returns a reference to allocated memory
         when the input number is odd, and a reference to a read-only memory
         location when the number is even, or the number is too large. Trying
         to free a read-only memory location will result in a error and a
         program crash.

         If we run original part of this code with a memory profiler (i.e.
         DrMemory) we will see an error message like this:

         ```
         Error #1: INVALID HEAP ARGUMENT to free ...
         ```

         with a stack trace that points to the line where the free() function
         is called.

         To fix this issue, we need to allocate memory for the returned string
         when the number is even, or the number is too large. We can then free
         the allocated memory after we are done with it.
      */
      free(text);
      text = NULL;
    } else if (err) {
      printf("Error: %s\n", err);
    }
  }
}

/* --------------------------------------------------------------------------
 * Function: get_odds
 * --------------------------------------------------------------------------
 *
 * Description: Return an array of odd numbers up to a given number. The
 *              function returns pointer to allocated memory that stores the
 *              odd numbers. It is up to the caller to free the memory when
 *              done with it.
 *
 * Parameters:
 *      highest: Highest number to print
 *     num_odds: Pointer to store the number of odd numbers
 *
 * Returns: Array of odd numbers
 *
 * -------------------------------------------------------------------------- */
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

/* --------------------------------------------------------------------------
 * Function: show_odds
 * --------------------------------------------------------------------------
 *
 * Description: Print odd numbers up to a given number. The function uses the
 *              `get_odds` function to get the odd numbers. The function is
 *              responsible for freeing the memory allocated by the
 *              `get_odds` function.
 *
 * Parameters:
 *      highest: Highest number to print
 *
 * Returns: None
 *
 * -------------------------------------------------------------------------- */
static void show_odds(int highest) {
  int *odds = NULL;
  int i = 0;
  long int num_odds = 0;

  odds = get_odds(highest, &num_odds);
  if (odds) {
    for (i = 0; i < num_odds; i++) {
      printf("%d\n", odds[i]);
    }
    /* Trynig to free invalid memory reference -------------------------------

       The code here is trying to free something that is not a reference to
       allocated memory. In particular case we are trying to free a variable
       that stores integer value instead of a reference to allocated memory.
       Microsoft's C compiler will raise an warning when trying to free a
       non-pointer variable, even though the `num_odds` variable is casted to
       a pointer type. E.g.:

       ```
       ... warning C4028: formal parameter 2 different from declaration
       ... warning C4312: 'type cast': conversion from 'long' to 'void *' of
           greater size
       ```
    */
    /* free((void *) num_odds); */
    free(odds);
  }
}

/* --------------------------------------------------------------------------
 * Function: splitter
 * --------------------------------------------------------------------------
 *
 * Description: Split a string into two parts: prefix and suffix. The function
 *              modifies the input string by replacing the first dash character
 *              with a null terminator. The function returns the prefix and
 *              suffix parts of the string. The caller is responsible for
 *              freeing the memory allocated by the function.
 *
 * Parameters:
 *      input: Input string to split
 *     prefix: Pointer to store the prefix part of the string
 *     suffix: Pointer to store the suffix part of the string
 *
 * Returns: None
 *
 * -------------------------------------------------------------------------- */
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

/* --------------------------------------------------------------------------
 * Function: print_and_free_ids
 * --------------------------------------------------------------------------
 *
 * Description: Print and free the prefix and suffix parts of the identifiers.
 *              The function prints the prefix and suffix parts of the
 *              identifiers and frees the memory allocated by the `splitter`
 *              function. The function is responsible for freeing the memory
 *              allocated by the `splitter` function (this is a typical example
 *              of a double free error, and a bad programming practice, since
 *              the given function should not be responsible for freeing the
 *              memory for wich it does not know if it is dynamically allocated
 *              or not).
 *
 * Parameters:
 *      alphas: Array of prefix parts of the identifiers
 *       nums: Array of suffix parts of the identifiers
 *   num_ids: Number of identifiers
 *
 * Returns: None
 *
 * -------------------------------------------------------------------------- */
static void print_and_free_ids(char **alphas, char **nums, int num_ids) {
  int i = 0;

  for (i = 0; i < num_ids; i++) {
    printf("%s\t%s\n", alphas[i], nums[i]);
    free(alphas[i]);
    /* Trying to free a block of memory inside the already freed block --------

       The code here is trying to free a block of memory that is already freed.
       This is due `alphas` and `nums` arrays are parts of the same block of
       memory that is allocated by the `splitter()` function. When we free the
       `alphas` array, we are also freeing the `nums` array. If we try to free
       the `nums` array after we have already freed the `alphas` array, this
       will result in a memory error and a program crash. If we run this code
       with a memory profiler (i.e. DrMemory) we will see an error message
       like this:

       ```
       Error #1: INVALID HEAP ARGUMENT to free ...
       ```

       with a stack trace that points to the line where the free() function is
       called.
    */
    /* free(nums[i]); */
  }

  /* Trying to free the memory that is not dynamically allocated --------------

     The code here is trying to free a block of memory that is not dynamically
     allocated. The `alphas` and `nums` are arrays of strings on the stack,
     created by the do_the_splits() function. When we try to free these arrays,
     we will get a memory error and a program crash. If we run this code with a
     memory profiler (i.e. DrMemory) we will see an error message like this:

     ```
     Error #1: INVALID HEAP ARGUMENT to free ...
     ```

     with a stack trace that points to the line where the free() function is
     called.
  */
  /*
  free(alphas);
  free(nums);
  */
}

/* --------------------------------------------------------------------------
 * Function: do_the_splits
 * --------------------------------------------------------------------------
 *
 * Description: Split the identifiers into prefix and suffix parts. The
 *              function splits the identifiers into prefix and suffix parts
 *              and prints them. The function is responsible for freeing the
 *              memory allocated by the `splitter` function.
 *
 * Parameters: None
 *
 * Returns: None
 *
 * -------------------------------------------------------------------------- */
static void do_the_splits() {
  char *ids[] = {"THX-1138", "U-62", "DS-9", "FN-2187", NULL};
  const int num_ids = sizeof(ids) / sizeof(char *) - 1;
  char *alphas[4] = {};
  char *nums[4] = {};
  int i = 0;

  for (i = 0; i < num_ids; i++) {
    splitter(ids[i], &alphas[i], &nums[i]);
  }

  print_and_free_ids(alphas, nums, num_ids);
}