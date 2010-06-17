
/*

  Copyright 2006 Absoft Corp.  All Rights Reserved.

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

  Contact information:  Absoft corp., 2781 Bond St,
  Rochester Hills, MI 48309, or:

  http://www.absoft.com

*/

#ifndef _PDGCS_READER
#define _PDGCS_READER

#define TARGET_BITS_PER_WORD               32
#define MAX_PATTERN_LINE_LEN 200000

#define MAX_LINE_LEN 200000

#include <stdio.h>
#include <string.h>
#include "i_cvrt.h"

void read_global_line_table();
int processCall();
int setCallName(char *out);


typedef unsigned int Uint;

/******************************/
/**** Global Table defines ****/
/******************************/

  struct global_line_tbl_entry
  {
    Uint           global_line     : 32;
    Uint           file_line       : 32;
    Uint           file_name_idx   : 32;
    Uint           unused	  : 16;
    Uint           file_name_len   : 16;
    Uint	   incld_file_line : 32;
    Uint	   incld_file_col  : 32;
    Uint           path_name_idx   : 32;
    Uint           path_name_len   : 32;
    Uint	   source_lines	  : 32;
    Uint           unused1	  :  8;
    Uint	   cif_file_id	  : 24;
  };
  typedef	struct	global_line_tbl_entry	global_line_tbl_type;


  union	name_pool_entry		{long		name_long;
				 char		name_char;
				};
  typedef	union	name_pool_entry	str_pool_type;


  extern str_pool_type         *str_pool; 
  extern int			str_pool_idx;
  extern int			str_pool_inc;
  extern int			str_pool_init_size;
  extern int			str_pool_limit;
  extern int			str_pool_num_wds;
  extern int			str_pool_size;
  extern int			str_pool_largest_idx;

  extern global_line_tbl_type  *global_line_tbl;
  extern long			global_line_tbl_idx;
  extern int			global_line_tbl_inc;
  extern int			global_line_tbl_init_size;
  extern long			global_line_tbl_limit;
  extern int			global_line_tbl_num_wds;
  extern long			global_line_tbl_size;
  extern long			global_line_tbl_largest_idx; 
  extern long			curr_glb_line;
  
# define TBL_REALLOC_CK(PTR, NUM_ENTRIES)				       \
		PTR##_idx += (NUM_ENTRIES);				       \
		SET_LARGEST_IDX(PTR, PTR##_idx, PTR##_idx);		       \
		if (PTR##_idx >= PTR##_size) {				       \
		   PTR##_size += (PTR##_inc > (NUM_ENTRIES)) ?		       \
						PTR##_inc : (NUM_ENTRIES);     \
 		   if (PTR##_size > PTR##_limit) {                             \
		      char _struct_name[20];                                   \
                      strncpy (_struct_name, #PTR, 20);                        \
                   }                                                           \
		   MEM_REALLOC (PTR, PTR##_type, PTR##_size);		       \
		}

# define SET_LARGEST_IDX(STRUCT, CHECK_IDX, NEW_IDX)			       \
		if (STRUCT##_largest_idx < CHECK_IDX) {			       \
 		   STRUCT##_largest_idx = NEW_IDX;			       \
		}

# define MEM_REALLOC(PTR, TYPE, NEW_SIZE)				       \
	{	void *_optr = PTR;					       \
		PTR = (TYPE *) realloc ((char *) PTR, (NEW_SIZE)*sizeof(TYPE));\
		if (PTR == NULL) {					       \
		   char _struct_name[20];                                      \
                   strncpy (_struct_name, #PTR, 20);                           \
		}							       \
	}

# define WORD_LEN(ID_LEN)               ((ID_LEN) + sizeof(long)) / sizeof(long)

# define TBL_ALLOC(PTR)                                                        \
                MEM_ALLOC (PTR, PTR##_type, PTR##_size);

# define MEM_ALLOC(PTR, TYPE, SIZE)                                            \
                PTR = (TYPE *) malloc ((SIZE)*sizeof(TYPE));                   \
                if (PTR == NULL) {                                             \
                   char _struct_name[20];                                      \
                   strncpy (_struct_name, #PTR, 20);                           \
                }

extern FILE *infile;
extern long lineNo;
extern char inLine[200000];

extern void PDGCS_entry_no_SGI_fe();
extern int START_COL;

#endif
