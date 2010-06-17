/*
 *  Copyright (C) 2008 PathScale, LLC.  All Rights Reserved.
 */

/*
 * Copyright 2004, 2005, 2006 PathScale, Inc.  All Rights Reserved.
 */

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

//  Global register allocation
/////////////////////////////////////
//
//  Interface for GRA
//
//  Expprted functons:
//
//      void GRA_Allocate_Global_Registers( BOOL is_region )
//          Allocate registers to the TNs of the current PU (region?).
//
//	void GRA_Initialize(void)
//	    Initialize data on a per PU basis.
//
//	BOOL GRA_Spill_Around_Save_TN_Copies(void)
//	    Return TRUE if spills in prolog/epilog blocks must be placed
//	    after/before save tn copies in order to allow gra to isolate
//	    these instructions (it needs to do this due to basic block
//	    granularity of conflicts).				
//
//      REGISTER_SET GRA_Local_Register_Grant( const BB* bb,
//                                             ISA_REGISTER_CLASS rc )
//          Return the registers granted by GRA for locals in the given <bb>
//          and <rc>.  (Valid only after GRA_Allocate_Global_Registers).
//
//      void GRA_Finalize_Grants(void)
//          All done with the local grant information.  Free it up.
//
/////////////////////////////////////


//  $Revision: 2913 $
//  $Date: 2008-10-03 10:45:29 -0400 (Fri, 03 Oct 2008) $
//  $Author: yin $
//  $Source: be/cg/gra_mon/SCCS/s.gra.h $

#ifndef GRA_INCLUDED
#define GRA_INCLUDED
#ifndef GRA_RCS_ID
#define GRA_RCS_ID
#ifdef _KEEP_RCS_ID
static char *gra_rcs_id = "$Source: be/cg/gra_mon/SCCS/s.gra.h $ $Revision: 2913 $";
#endif
#endif

#include "defs.h"
#include "register.h"
#include "bb.h"

extern void GRA_Allocate_Global_Registers( BOOL is_region );
extern void GRA_Initialize(void);
extern BOOL GRA_Spill_Around_Save_TN_Copies(void);
extern REGISTER_SET GRA_Local_Register_Grant( BB* bb, ISA_REGISTER_CLASS rc );
extern void GRA_Finalize_Grants(void);

// defined in gra.cxx
extern MEM_POOL* const GRA_pool;
extern INT GRA_pu_num;
extern float GRA_call_split_freq;
extern float GRA_spill_count_factor;

// defined in other .cxx files
#define DEFAULT_FORCED_LOCAL_MAX 4
extern INT GRA_local_forced_max;
extern BOOL GRA_avoid_glue_references_for_locals;
extern BOOL GRA_split_entry_exit_blocks;
#ifdef KEY
extern BOOL GRA_pu_has_handler;
#endif

// interface with cgdriver
extern BOOL GRA_split_lranges; 		// controlled by -GRA:split_lranges
extern INT GRA_non_split_tn_id;		// controlled by -GRA:non_split_tn
extern INT GRA_non_preference_tn_id;	// controlled by -GRA:non_preference_tn
extern BOOL GRA_optimize_placement;	// controlled by -GRA:optimize_placement
#ifdef KEY
extern BOOL GRA_optimize_boundary;	// controlled by -GRA:optimize_boundary
extern BOOL GRA_optimize_boundary_set;
extern BOOL GRA_reclaim_register;	// controlled by -GRA:reclaim
extern BOOL GRA_reclaim_register_set;
extern BOOL GRA_prioritize_by_density;	// controlled by -GRA:prioritize_by_density
extern BOOL GRA_prioritize_by_density_set;
#endif

#ifdef TARG_X8664
extern BOOL GRA_grant_special_regs;	// controlled by -GRA:grant_special_regs
extern BOOL GRA_local_forced_max_set;

static inline INT GRA_LOCAL_FORCED_MAX( ISA_REGISTER_CLASS rc )
{
  if( Is_Target_32bit()         &&
      !GRA_local_forced_max_set &&
      rc == ISA_REGISTER_CLASS_integer )
    return 3;
  else
    return GRA_local_forced_max;
}
#else
#define GRA_LOCAL_FORCED_MAX(rc)   GRA_local_forced_max
#endif // TARG_X8664


#endif
