/*
 * Copyright 2003, 2004, 2005 PathScale, Inc.  All Rights Reserved.
 */

/*

  Copyright (C) 2000, 2001 Silicon Graphics, Inc.  All Rights Reserved.

  This program is free software; you can redistribute it and/or modify it
  under the terms of version 2.1 of the GNU Lesser General Public License 
  as published by the Free Software Foundation.

  This program is distributed in the hope that it would be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  

  Further, this software is distributed without any warranty that it is
  free of the rightful claim of any third person regarding infringement 
  or the like.  Any license provided herein, whether implied or 
  otherwise, applies only to this software file.  Patent licenses, if
  any, provided herein do not apply to combinations of this program with 
  other software, or any other product whatsoever.  

  You should have received a copy of the GNU Lesser General Public 
  License along with this program; if not, write the Free Software 
  Foundation, Inc., 59 Temple Place - Suite 330, Boston MA 02111-1307, 
  USA.

  Contact information:  Silicon Graphics, Inc., 1600 Amphitheatre Pky,
  Mountain View, CA 94043, or:

  http://www.sgi.com

  For further information regarding this notice, see:

  http://oss.sgi.com/projects/GenInfo/NoticeExplan

*/



/* ====================================================================
 * ====================================================================
 *
 * Module: cabs.c
 * $Revision: 2519 $
 * $Date: 2006-12-18 15:41:18 -0500 (Mon, 18 Dec 2006) $
 * $Author: yin $
 * $Source$
 *
 * Revision history:
 *  20-Jun-93 - Original Version
 *
 * Description:	source code for cabs function
 *
 * ====================================================================
 * ====================================================================
 */

static char *rcs_id = "$Source$ $Revision: 2519 $";

#include "libm.h"

extern	double	__hypot(double, double);

struct __cabs_s { double r, i; };

#if defined(mips) && !defined(__GNUC__)
extern double	cabs(struct __cabs_s);

#pragma weak cabs = __cabs
#endif

#ifdef __GNUC__
extern  double  __cabs(struct __cabs_s);
#ifndef __APPLE__
double    cabs() __attribute__ ((weak, alias ("__cabs")));
#endif
#endif

#ifdef _WIN32
#define __cabs cabs
#endif

#ifdef __APPLE__
#define __cabs cabs
#endif

double
__cabs(z)
struct __cabs_s	z;
{
	return __hypot(z.r, z.i);
}

