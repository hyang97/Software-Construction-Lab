/* -*- buffer-read-only: t -*- vi: set ro: */
/* DO NOT EDIT! GENERATED AUTOMATICALLY! */
#line 1
/* Test of <wctype.h> substitute.
   Copyright (C) 2007-2009 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* Written by Bruno Haible <bruno@clisp.org>, 2007.  */

#include <config.h>

#include <wctype.h>

#include <stdio.h>
#include <stdlib.h>

#define ASSERT(expr) \
  do									     \
    {									     \
      if (!(expr))							     \
        {								     \
          fprintf (stderr, "%s:%d: assertion failed\n", __FILE__, __LINE__); \
          fflush (stderr);						     \
          abort ();							     \
        }								     \
    }									     \
  while (0)

/* Check that the type wint_t is defined.  */
wint_t a = 'x';
/* Check that WEOF is defined.  */
wint_t e = WEOF;

int
main ()
{
  /* Check that the isw* functions exist as functions or as macros.  */
  (void) iswalnum (0);
  (void) iswalpha (0);
#if 0 /* not portable: missing on mingw */
  (void) iswblank (0);
#endif
  (void) iswcntrl (0);
  (void) iswdigit (0);
  (void) iswgraph (0);
  (void) iswlower (0);
  (void) iswprint (0);
  (void) iswpunct (0);
  (void) iswspace (0);
  (void) iswupper (0);
  (void) iswxdigit (0);

  /* Check that the isw* functions map WEOF to 0.  */
  ASSERT (!iswalnum (e));
  ASSERT (!iswalpha (e));
#if 0 /* not portable: missing on mingw */
  ASSERT (!iswblank (e));
#endif
  ASSERT (!iswcntrl (e));
  ASSERT (!iswdigit (e));
  ASSERT (!iswgraph (e));
  ASSERT (!iswlower (e));
  ASSERT (!iswprint (e));
  ASSERT (!iswpunct (e));
  ASSERT (!iswspace (e));
  ASSERT (!iswupper (e));
  ASSERT (!iswxdigit (e));

  /* Check that the tow* functions exist as functions or as macros.  */
  (void) towlower (0);
  (void) towupper (0);

  /* Check that the tow* functions map WEOF to WEOF.  */
  ASSERT (towlower (e) == e);
  ASSERT (towupper (e) == e);

  return 0;
}
