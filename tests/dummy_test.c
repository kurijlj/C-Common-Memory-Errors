/* ==========================================================================
 *  Copyright (C) <yyyy> Ljubomir Kurij <ljubomir_kurij@protonmail.com>
 *
 * This file is part of <PROGRAM_NAME>.
 *
 * <PROGRAM_NAME> is free software: you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or (at your
 * option) any later version.
 *
 * <PROGRAM_NAME> is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General
 * Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with Focus Precision Analyze. If not, see <https://www.gnu.org/licenses/>.
 * ========================================================================== */

/* ==========================================================================
 *
 * yyyy-mm-dd Ljubomir Kurij <ljubomir_kurij@protonmail.com>
 *
 * * <testfilename>.c: created.
 *
 * ========================================================================== */

/* ==========================================================================
 *
 * References (this section should be deleted in the release version)
 *
 * * For how to write unit tests using `munit' test framework consult
 *   documentation and examples at
 *   <https://nemequ.github.io/munit/#documentation>
 *
 * ========================================================================== */

/* ==========================================================================
 * Headers include section
 * ========================================================================== */

/* Related header */

/* System headers */

/* Standard Library headers */

/* Testing framework header */
#include <munit.h>

void main(void) {
  int a = 10;
  int b = 10;
  munit_assert_int(a, ==, b);
}