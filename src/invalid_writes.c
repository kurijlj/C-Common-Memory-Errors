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
 * 2024-05-15 Ljubomir Kurij <ljubomir_kurij@protonmail.com>
 *
 * * invalid_writes.c: created.
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

#define APP_NAME "invalid_writes"
#define APP_VERSION "1.0"
#define APP_AUTHOR "Ljubomir Kurij"
#define APP_EMAIL "ljubomir_kurij@protonmail.com"
#define APP_COPYRIGHT_YEAR "2024"
#define APP_COPYRIGHT_HOLDER APP_AUTHOR
#define APP_LICENSE "GPLv3+"
#define APP_LICENSE_URL "http://gnu.org/licenses/gpl.html"
#define APP_DESCRIPTION                                                        \
  "This code explores a common source of errors in C: writting to\n"           \
  "invalid (freed) and unitialized memory. Specifically, we'll investigate\n"  \
  "what happens when you try to write to a memory location that has not\n"     \
  "been allocated or has been deallocated. We'll also try to write past the\n" \
  "end of a buffer and write to a file after it has been closed. The goal\n"   \
  "is to twofold:\n\n"                                                         \
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

static void set_zero(char *dest, int num_bytes);
static void get_message(char *message);
static void write_quote(FILE *f, char *text);

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
    char *buf = NULL;
    /* char message[10] = ""; */
    FILE *outfile = NULL;

    /* Try to write to an invalid memory location ---------------------------

       This is the `invalid write` because we are trying to write to a memory
       location that has not been allocated. The `buf` pointer is initialized
       to `NULL` and then passed to the `set_zero` function.

       If we run this part of the code with a memory profiling tool like
       DrMemory, it will throw following errors:

       ```
       Error #1: UNADDRESSABLE ACCESS: writing ...
       ...
       Error #2: UNINITIALIZED READ: reading ...
       ```

       with a stack trace that shows the exact line of code that caused the
       error.
    */
    buf = (char *)malloc(100);
    set_zero(buf, sizeof(buf));
    free(buf);

    /* Try to write past the end of a buffer --------------------------------

       This is the `invalid write` because we are trying to write past the
       end of the buffer. Our buffer is only 10 bytes long, but we are trying
       to write 26 bytes to it (see the function defintion for the
       `get_message`). This will cause a corruption of the stack and a
       crash.

       If we run this part of the code with a memory profiling tool like
       DrMemory, it will throw following errors:

       ```
       Error #1: UNINITIALIZED READ: reading ... 96 byte(s) within ...
       ...
       Error #2: UNINITIALIZED READ: reading ... 6 byte(s) within ...
       ```

       with a stack trace that points to the end of the `main` function.
    */
    char message[50] = "";
    get_message(message);

    outfile = fopen("outfile.txt", "w");
    if (outfile) {
      /* Try to write to a file after it has been closed --------------------

         This is the `invalid write` because we are trying to write to a file
         after it has been closed (see the function definition for the
         `write_quote`).

         Interestingly, this will not cause a crash or a memory error on the
         Windows platform. The file will be created and the quote will be
         written to it. However, the "Albert Einstein" line will not be
         written to the file. Also DrMemory will not detect any errors.

         However, if we examine the return value of the `fputs` function, we
         will see that it returns `EOF`, which indicates an error. This is
         because the file has been closed and we are trying to write to it
         after it has been closed.
      */
      write_quote(outfile, "If we knew what it was we were doing,"
                           " it would not be called research, would it?");
      int result = fputs("\tAlbert Einstein", outfile);
      printf("%s: %s\n", APP_NAME,
             result == EOF ? "Error writing to file"
                           : "File written successfully");
      fclose(outfile);
    }

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
 * Function: set_zero
 * --------------------------------------------------------------------------
 *
 * Description: Set a block of memory to zero
 *
 * Parameters:
 *      dest: Pointer to the memory block
 * num_bytes: Number of bytes to set to zero
 *
 * Returns: None
 *
 * -------------------------------------------------------------------------- */
static void set_zero(char *dest, int num_bytes) {
  int i = 0;

  for (i = 0; i < num_bytes; i++) {
    dest[i] = 0;
  }
}

/* --------------------------------------------------------------------------
 * Function: get_message
 * --------------------------------------------------------------------------
 *
 * Description: Get a message
 *
 * Parameters:
 *      message: Pointer to the buffer to store the message
 *
 * Returns: None
 *
 * -------------------------------------------------------------------------- */
static void get_message(char *message) {
  char *alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

  strncpy(message, alphabet, strlen(alphabet));
}

/* --------------------------------------------------------------------------
 * Function: write_quote
 * --------------------------------------------------------------------------
 *
 * Description: Write a quote to a file
 *
 * Parameters:
 *      f: Pointer to the file
 *   text: Pointer to the quote
 *
 * Returns: None
 *
 * -------------------------------------------------------------------------- */
static void write_quote(FILE *f, char *text) {
  int len = strlen(text);
  int i = 0;

  /* put out a line of equal signs before the quote */
  for (i = 0; i < len; i++) {
    fputc('=', f);
  }
  fputc('\n', f);

  /* put out the actual quote */
  fputs(text, f);

  /* terminate with another line of equal signs */
  fputc('\n', f);
  for (i = 0; i < len; i++) {
    fputc('=', f);
  }
  fputc('\n', f);

  /* all done! */
  /* fclose(f); */
}