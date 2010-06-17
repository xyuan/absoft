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


/* -*-Mode: c++;-*- (Tell emacs to use c++ mode) */
// TODO:
//   *  remove unnecessary includes
//
//
#include <elf.h>                    /* for wn.h */
#include "wn.h"                     /* for WN */
#include "defs.h"		    /* for pu_info.h */ 
#include "config.h"                 /* for LNO_Path, etc. */
#include "pu_info.h"		    /* for PU_Info */ 
#include "anl_driver.h" 
 
// ========= Define the external interface routines =========
// ==========================================================
extern "C" void
Anl_Process_Command_Line (INT phase_argc, char *phase_argv[],
			  INT argc, char *argv[])
{
	printf( "Anl_Process_Command_Line() is not supported!\n" );
} // Anl_Process_Command_Line


extern "C" BOOL
Anl_Needs_Whirl2c()
{
	printf( "Anl_Needs_Whirl2c() is not supported!\n" );
   return false;
} // Prp_Needs_Whirl2c


extern "C" BOOL
Anl_Needs_Whirl2f()
{
	printf( "Anl_Needs_Whirl2f() is not supported!\n" );
   return false;
} // Anl_Needs_Whirl2f


extern "C" void                                  
Anl_Init()
{
	printf( "Anl_Init() is not supported!\n" );
} // Anl_Init


extern "C" WN_MAP
Anl_Init_Map(MEM_POOL *id_map_pool)
{
	printf( "Anl_Init_Map() is not supported!\n" );
  return 0;
} 

extern "C" void 
Anl_Static_Analysis(WN *pu, WN_MAP id_map)
{
	printf( "Anl_Static_Analysis() is not supported!\n" );
} // Anl_Static_Analysis


extern "C" INT64 
Get_Next_Construct_Id()
{
	printf( "Get_Next_Construct_Id() is not supported!\n" );
   return 0;
} // Get_Next_Construct_Id


extern "C" INT64
New_Construct_Id()
{
	printf( "New_Construct_Id() is not supported!\n" );
   return 0;
} // New_Construct_Id


extern "C" const char *
Anl_File_Path()
{
	printf( "Anl_File_Path() is not supported!\n" );
   return NULL;
} // Anl_File_Path


extern "C" void
Anl_Fini()
{
	printf( "Anl_Fini() is not supported!\n" );
} // Anl_Fini


extern "C" void
Anl_Cleanup()
{
	printf( "Anl_Cleanup() is not supported!\n" );
} // Anl_Cleanup

extern void 
Prompf_Emit_Whirl_to_Source(PU_Info* current_pu, WN* func_nd)
{
	printf( "Prompf_Emit_Whirl_to_Source() is not supported!\n" );
}
