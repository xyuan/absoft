C
C
C  Copyright (C) 2000, 2001 Silicon Graphics, Inc.  All Rights Reserved.
C
C  This program is free software; you can redistribute it and/or modify it
C  under the terms of version 2 of the GNU General Public License as
C  published by the Free Software Foundation.
C
C  This program is distributed in the hope that it would be useful, but
C  WITHOUT ANY WARRANTY; without even the implied warranty of
C  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  
C
C  Further, this software is distributed without any warranty that it is
C  free of the rightful claim of any third person regarding infringement 
C  or the like.  Any license provided herein, whether implied or 
C  otherwise, applies only to this software file.  Patent licenses, if 
C  any, provided herein do not apply to combinations of this program with 
C  other software, or any other product whatsoever.  
C
C  You should have received a copy of the GNU General Public License along
C  with this program; if not, write the Free Software Foundation, Inc., 59
C  Temple Place - Suite 330, Boston MA 02111-1307, USA.
C
C  Contact information:  Silicon Graphics, Inc., 1600 Amphitheatre Pky,
C  Mountain View, CA 94043, or:
C
C  http://www.sgi.com
C
C  For further information regarding this notice, see:
C
C  http://oss.sgi.com/projects/GenInfo/NoticeExplan
C
C


      SUBROUTINE ARCDABS (R, X)
      CALL AR_NOINTRIN_ERROR("CDABS")
      END

      SUBROUTINE ARCDSQRT (R, X)
      CALL AR_NOINTRIN_ERROR("CDSQRT")
      END

      SUBROUTINE ARCDLOG (R, X)
      CALL AR_NOINTRIN_ERROR("CDLOG")
      END

      SUBROUTINE ARCDEXP (R, X)
      CALL AR_NOINTRIN_ERROR("CDEXP")
      END

      SUBROUTINE ARPOWCDI (R, C, I)
      CALL AR_NOINTRIN_ERROR("CDTOI")
      END

      SUBROUTINE ARPOWCDCD (R, X, Y)
      CALL AR_NOINTRIN_ERROR("CDTOCD")
      END

c USMID = "\n%Z%%M%     %I%     %G% %U%\n";
c rcsid = "$Id: dummy_dc.f 162 2005-08-09 19:23:30Z aer $";
