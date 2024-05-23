
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
 * 2024-05-23 Ljubomir Kurij <ljubomir_kurij@protonmail.com>
 *
 * * invalid_frees_exercise.c: created.
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

#define APP_NAME "invalid_frees_exercise"
#define APP_VERSION "1.0"
#define APP_AUTHOR "Ljubomir Kurij"
#define APP_EMAIL "ljubomir_kurij@protonmail.com"
#define APP_COPYRIGHT_YEAR "2024"
#define APP_COPYRIGHT_HOLDER APP_AUTHOR
#define APP_LICENSE "GPLv3+"
#define APP_LICENSE_URL "http://gnu.org/licenses/gpl.html"
#define APP_DESCRIPTION "A solution to the exercise regarding invalid frees."
#ifdef _WIN32
#define APP_USAGE_A APP_NAME ".exe [OPTION]..."
#else
#define APP_USAGE_A APP_NAME " [OPTION]..."
#endif /* End of platform specific macro definition */
#define APP_EPILOGUE "\nReport bugs to <" APP_EMAIL ">."

#define MY_DEBUG 0

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

static void my_free(void *ptr);
static char *fix_amp(char *src);
static char *get_user_text();

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
    char *s = get_user_text();
    char *fixed = fix_amp(s);
    free(s);
    s = fixed;
    fixed = fix_amp(s);
    free(s);
    s = NULL;

    printf("Encoded: %s\n", fixed);

    /* Free the last pointer */
    free(fixed);
    fixed = NULL;

    /* Execution of the main code section is complete. Print the exit message */
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
 * Function: fix_amp
 * --------------------------------------------------------------------------
 *
 * Description: Fix ampersands in a string by double-encoding them.
 *
 * Parameters:
 *     src: Pointer to the source string
 *
 * Returns: Pointer to the fixed string
 *
 * -------------------------------------------------------------------------- */
static char *fix_amp(char *src) {
  char *fixed = NULL;
  int i = 0;
  int new_len = 0;

  for (i = 0; src[i] != '\0'; i++) {
    if (src[i] == '&') {
      new_len += 5;
    } else {
      new_len++;
    }
  }

  fixed = calloc(new_len + 1, sizeof(char));
  if (fixed) {
    int j = 0;
    for (i = 0; src[i] != '\0'; i++) {
      if (src[i] == '&') {
        memcpy(fixed + j, "&amp;", 5);
        j += 5;
      } else {
        fixed[j] = src[i];
        j++;
      }
    }
    fixed[j] = '\0';
  }

  return fixed;
}

/* --------------------------------------------------------------------------
 * Function: get_user_text
 * --------------------------------------------------------------------------
 *
 * Description: Get text input from the user.
 *
 * Returns: Pointer to the user input text
 *
 * -------------------------------------------------------------------------- */
static char *get_user_text() {
  char buf[1024] = "";
  char *input_txt = "Enter text to double-encode: ";
  char *text_input = NULL;

  printf("%s", input_txt);
  fgets(buf, sizeof(buf), stdin);
  text_input = strdup(buf);

  return text_input;
}