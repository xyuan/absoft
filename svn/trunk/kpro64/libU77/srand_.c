/*
 * Copyright 2004, 2005 PathScale, Inc.  All Rights Reserved.
 */

/* Copyright (C) 1995 Free Software Foundation, Inc.
This file is part of GNU Fortran libU77 library.

This library is free software; you can redistribute it and/or modify it
under the terms of the GNU Library General Public License as published
by the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

GNU Fortran is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Library General Public License for more details.

You should have received a copy of the GNU Library General Public
License along with GNU Fortran; see the file COPYING.LIB.  If
not, write to the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
Boston, MA 02111-1307, USA.  */

#include "config.h"
#if STDC_HEADERS || defined(KEY) /* Bug 1683 */
#  include <stdlib.h>
#endif
#include "f2c.h"

/* Subroutine */
int
G77_srand_0 (const integer * seed)
{
  srand ((unsigned int) *seed);
  return 0;
}

#ifdef KEY /* Bug 1683 */
int
G77_srand_1 (const long long * seed)
{
  srand ((unsigned int) *seed);
  return 0;
}
#endif /* KEY Bug 1683 */
