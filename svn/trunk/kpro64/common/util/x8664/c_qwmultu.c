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


#include "defs.h"

void c_qwmultu(UINT32 result[8], UINT32 x[4], UINT32 y[4])
{
  DevWarn( "Quad-word to 256-bit multiply not implemented yet.\n");
#ifdef ABSOFT_EXTENSIONS
  /* this algorithm is not right, but should be good for removing loop forever in backend */
  UINT64* tmp;
  
  result[0] = 0;
  result[1] = 0;
  result[2] = 0;
  result[3] = 0;
  result[4] = 0;
  result[5] = 0;
  result[6] = 0;
  result[7] = 0;
  
  tmp = (UINT64*)&result[0];
  *tmp += (UINT64)x[0] * (UINT64)y[0];
  tmp = (UINT64*)&result[1];
  *tmp += (UINT64)x[1] * (UINT64)y[1];
  tmp = (UINT64*)&result[2];
  *tmp += (UINT64)x[2] * (UINT64)y[2];
  tmp = (UINT64*)&result[3];
  *tmp += (UINT64)x[3] * (UINT64)y[3];

#else
  exit(-1);
#endif
}
