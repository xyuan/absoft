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


static const char USMID[] = "@(#) libu/util/posix/utilintrin.c	92.0	10/08/98 14:57:41";


int __leadz1(unsigned char x)
{
   int r,t;
   if (x == 0) return (8);
   r = 0;
   for (t=4; t > 0; t >>= 1) {
      if ((x >> t) == 0) {
         r += t;
      } else {
         x >>= t;
      }
   }
   return (r);
}

int __leadz2(unsigned short x)
{
   int r,t;
   if (x == 0) return (16);
   r = 0;
   for (t=8; t > 0; t >>= 1) {
      if ((x >> t) == 0) {
         r += t;
      } else {
         x >>= t;
      }
   }
   return (r);
}

int __leadz4(unsigned int x)
{
   int r,t;
   if (x == 0) return (32);
   r = 0;
   for (t=16; t > 0; t >>= 1) {
      if ((x >> t) == 0) {
         r += t;
      } else {
         x >>= t;
      }
   }
   return (r);
}

int __leadz8(unsigned long long x)
{
   int r,t;
   if (x == 0) return (64);
   r = 0;
   for (t=32; t > 0; t >>= 1) {
      if ((x >> t) == 0) {
         r += t;
      } else {
         x >>= t;
      }
   }
   return (r);
}

