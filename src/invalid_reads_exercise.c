
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
 * * invalid_reads_exercise.c: created.
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
  "A solution to the exercise regarding invalid reads."
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

static char *get_sentence(char *text);


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
    char *full_texts[] = {
        "A single sentence",
        "A single sentence with a period.",
        "Strange women lying in ponds distributing swords is no basis for a "  \
        "system of government. Supreme executive power derives from a "        \
        "mandate from the masses, not from some farcical aquatic ceremony.",
        NULL
    };
    char *sentence = NULL;
    int i = 0;

    for (i = 0; full_texts[i] != NULL; i++) {
      sentence = get_sentence(full_texts[i]);
      printf("%s: %s\n", APP_NAME, sentence);
      free(sentence);
    }

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
 * Function: get_sentence
 * --------------------------------------------------------------------------
 *
 * Description: Get the first sentence from a text
 *
 * Parameters:
 *      text: Pointer to a string containing the text
 *
 * Returns: Pointer to a string containing the first sentence
 *
 * -------------------------------------------------------------------------- */
static char *get_sentence(char *text) {
  char *ret = NULL;
  int len = 0;
  int i = 0;

  // find period or end of string
  for (i = 0; text[i] != '\0' && text[i] != '.'; i++) {
    len++;
  }
  if (text[i] == '.') {
    len++;  /* Add one to len to account for the period */
  }

  printf("%s: len: %d\n", APP_NAME, len);

  /* Copy only up to period (if found). Since we are using we don't nedd to
     explicitly add the null terminator at the end of the string, we just
     need to allocate the memory for it.                                      */
  ret = calloc(len + 1, sizeof(char));
  if (ret) {
    for (i = 0; i < len; i++) {
      ret[i] = text[i];
    }
  }

  return ret;
}