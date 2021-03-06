/*

  Copyright (C) 2000, 2001 Silicon Graphics, Inc.  All Rights Reserved.

  This program is free software; you can redistribute it and/or modify it
  under the terms of version 2 of the GNU General Public License as
  published by the Free Software Foundation.

  This program is distributed in the hope that it would be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  

  Further, this software is distributed without any warranty that it is
  free of the rightful claim of any third person regarding infringement 
  or the like.  Any license provided herein, whether implied or 
  otherwise, applies only to this software file.  Patent licenses, if 
  any, provided herein do not apply to combinations of this program with 
  other software, or any other product whatsoever.  

  You should have received a copy of the GNU General Public License along
  with this program; if not, write the Free Software Foundation, Inc., 59
  Temple Place - Suite 330, Boston MA 02111-1307, USA.

  Contact information:  Silicon Graphics, Inc., 1600 Amphitheatre Pky,
  Mountain View, CA 94043, or:

  http://www.sgi.com

  For further information regarding this notice, see:

  http://oss.sgi.com/projects/GenInfo/NoticeExplan

*/


/* ====================================================================
 * ====================================================================
 *
 * Module: cq_pow.c
 *
 * Description:	source code for complex quad power function
 *
 * ====================================================================
 * ====================================================================
 */

#include "quad.h"

  /* complex *32 power function */

/* ====================================================================
 *
 * FunctionName		cq_abs
 *
 * Description		computes quad complex power function of args
 *
 * ====================================================================
 */

extern qcomplex __qcis(long double arg);

qcomplex __cqpow(long double aqreal, long double aqimag, long double bqreal, long double bqimag)
{
  long double logr, logi, x, y;
  qcomplex r, qc;

  logr = __qlog( __qhypot(aqreal, aqimag));
  logi = __qatan2( aqimag, aqreal);

  x = __qexp( logr*bqreal - logi*bqimag);
  y = logr*bqimag + logi*bqreal;

  qc = __qcis(y);
  r.qreal = x*qc.qreal;
  r.qimag = x*qc.qimag;
  return r;
}

void __cq_pow(qcomplex *r, qcomplex *a, qcomplex *b)
{
  *r = __cqpow (a->qreal, a->qimag, b->qreal, b->qimag);
}
