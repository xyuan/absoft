
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

#ifndef _SETUP_READER_H
#define _SETUP_READER_H

#include "PDGCS_reader.h"

void setup_PDGCS_initialize();
void setup_fei_object_at_offset();
void setup_fei_object();
void setup_PDGCS_comp_unit();
void setup_fei_user_code_start();
void setup_fei_descriptor();
void setup_fei_descriptor_size_at_typ_idx();
void setup_fei_descriptor_variable_size();
void setup_fei_next_func_idx();
void setup_fei_seg();
void setup_fei_proc();
void setup_fei_arith_con();
void setup_cwh_add_to_used_files_table();
void setup_PDGCS_end_comp_unit();
void setup_fei_proc_body();
void setup_fei_stmt();
void setup_fei_object_ref();
void setup_fei_constant();
void setup_fei_pattern_con();
void setup_fei_store();
void setup_fei_function_ref();
void setup_fei_call();
void setup_fei_null_expr();
void setup_fei_IO_list();
void setup_fei_formatted_write();
void setup_fei_push_arith_con();
void setup_fei_iotype();
void setup_fei_start_ioblock();
void setup_fei_end_ioblock();
void setup_fei_label();
void setup_fei_goto();
void setup_fei_label_def_named();
void setup_fei_if();
void setup_fei_else();
void setup_fei_endif();
void setup_fei_static_base();
void setup_fei_static_simple_init();
void setup_fei_static_next_simple_init();
void setup_fei_arg_addr();
void setup_fei_return();
void setup_fei_doloop();
void setup_fei_dowhile();
void setup_fei_enddo();
void setup_fei_doforever();
void setup_fei_array_dimen();
void setup_fei_subscr_triplet();
void setup_fei_subscr_size();
void setup_fei_seq_subscr();
void setup_fei_substr();
void setup_fei_paren();

void setup_fei_backspace();
void setup_fei_close();
void setup_fei_endfile();
void setup_fei_inquire();
void setup_fei_open();
void setup_fei_rewind();
void setup_fei_malloc();
void setup_fei_mfree();
void setup_fei_addr();
void setup_fei_cvtop();
void setup_formatted_read();
void setup_unformatted_read();
void setup_fei_namelist();
void setup_fei_static_substr();
void setup_fei_namelist_write();
void setup_fei_namelist_read();
void setup_fei_static_subscripts();
void setup_fei_namelist_ref();
void setup_fei_label_ref();
void setup_fei_brtrue();
void setup_fei_implied_do();
void setup_fei_unformatted_write();
void setup_fei_concat();
void setup_fei_dope_vector();
void setup_fei_dv_def();
void setup_fei_dv_deref();
void setup_fei_set_dv_hdr_fld();
void setup_fei_get_dv_hdr_fld();
void setup_fei_mask();
void setup_fei_static_simple_reloc_init();
void setup_fei_set_dv_str_mult();
void setup_fei_set_dv_extent();
void setup_fei_set_dv_low_bnd();
void setup_fei_new_select();
void setup_fei_new_index();
void setup_fei_alloc();
void setup_fei_free();
void setup_fei_allocate();
void setup_fei_get_dv_str_mult();
void setup_fei_get_dv_extent();
void setup_fei_get_dv_low_bnd();
void setup_fei_nseq_subscr();
void setup_fei_dv_ptr_asg();
void setup_fei_present();
void setup_fei_smt_actual_to_generic();
void setup_fei_smt_parameter();
void setup_fei_where();
void setup_fei_new_select_case();
void setup_fei_as_ref();
void setup_fei_add_use_path();
void setup_fei_static_member();
void setup_fei_fcd();


void setup_PDGCS_debug_init();
void setup_PDGCS_do_proc();
void setup_PDGCS_end_procs();
void setup_PDGCS_terminate();
void setup_PDGCS_new_proc();

enum pdg_type_enum { AT, CN, SB, AT_TYP };
typedef enum pdg_type_enum pdg_type_enum;


extern void PDGCS_entry_no_SGI_fe();

typedef unsigned long Ulong;
#define NUM_PDG_WDS 4
#define LONG_MAX 2147483647

/******************************/
/**** PDG_TBL declarations ****/
/******************************/

struct  reader_pdg_link_tbl_entry      {Ulong          at_idx;
                                	Ulong          cn_idx;
                                	Ulong          sb_idx;
                                       };


typedef struct  reader_pdg_link_tbl_entry      reader_pdg_link_tbl_type;

reader_pdg_link_tbl_type      *reader_pdg_link_tbl;
long   		        reader_pdg_link_tbl_idx = 0;
int                     reader_pdg_link_tbl_inc = 0;
int                     reader_pdg_link_tbl_init_size = 0;
long                    reader_pdg_link_tbl_limit = 2147483647;
int                     reader_pdg_link_tbl_num_wds = 4;
long                    reader_pdg_link_tbl_size = sizeof(reader_pdg_link_tbl_type);
long                    reader_pdg_link_tbl_largest_idx = 0;

union PDG_TYPE {
  TYPE type;
  INTPTR type_idx;
};

typedef union PDG_TYPE PDG_TYPE;

PDG_TYPE *reader_pdg_type_tbl = NULL;
long  reader_pdg_type_tbl_idx;

#include "setup_reader2.h"

/* MOD LINK TABLE */
                                                                                
# define PDG_AT_IDX(IDX)                reader_pdg_link_tbl[IDX].at_idx
# define PDG_AT_TYP_IDX(IDX)            reader_pdg_type_tbl[IDX].type
# define PDG_AT_TYP_INTERNAL_IDX(IDX)   reader_pdg_type_tbl[IDX].type_idx
# define PDG_CN_IDX(IDX)                reader_pdg_link_tbl[IDX].cn_idx
# define PDG_SB_IDX(IDX)                reader_pdg_link_tbl[IDX].sb_idx
                                                                                
char LHS[2000000];
char RHS[2000000];

int setLongLongFlagsVar(char *label, long long *out);
int setIntFlagsVar(char *label, INT32 *out);
int setStrVar(char *label, char *out);
int setLongVar(char *label, long *out);
int setLongLongVar(char *label, long long *out);
int setIntVar(char *label, int *out);
int setEnumVar(char *label, int *out);
int ignoreVar(char *label);

void trim(char s[]);
void getLHS(char *src, char *dest);
void printError(char *text);
void addPdgLink(pdg_type_enum type, long idx, long contents);
void addPdgTypeLink(pdg_type_enum type, long idx, TYPE contents);
void addPdgTypeInternalLink(pdg_type_enum type, long idx, long contents);

void initPdgTbl();
#endif
