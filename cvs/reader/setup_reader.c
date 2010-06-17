
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

#include "setup_reader.h"
#include <math.h>

static TYPE null_type;


#include "setup_reader2.cpp"

void setup_PDGCS_initialize()
{
  LANG language = Unknown_Lang;
  INT32 init_flags = 0;
  char cmp_name[8] = "";
  char cmp_rel[8] = "";
  char code_file_name[1024] = "";
  char list_file_name[1024] = "";
  INT32 trunc_bits = 0;
  INT32 debug_opts = 0;
  char src_path_name[1024] = "";
  char cif_file_name[1024] = "";
  char debug_file_name[1024] = "";
  char src_fname[1024] = "";
  char cwd[1024] = "";
  INT32 n_pes = 0;
  INT32 meta_test = 0;

  setStrVar("compiler name", cmp_name);
  setEnumVar("language", (int*)&language);
  setIntFlagsVar("flags", &init_flags);
  ignoreVar("command name");
  setStrVar("release level", cmp_rel);
  setStrVar("code file name", code_file_name);
  trim(code_file_name);
  setStrVar("list file name", list_file_name);
  setIntVar("trunc bits", &trunc_bits);
  setIntVar("CCG flags", &debug_opts);
  setStrVar("src_path_name", src_path_name);
  trim(src_path_name);
  setStrVar("cif_file_name", cif_file_name);
/*  ACC C lib doesn't accept NULL for %s in printf
  setStrVar("debug_file_name", debug_file_name); */
  ignoreVar("debug_file_name");
  ignoreVar("debug file ptr");
  ignoreVar("cif file ptr");
  setStrVar("GL_FILE_NAME", src_fname);
  trim(src_fname);
  setStrVar("path name", cwd);
  trim(cwd);
  setIntVar("N$PE", &n_pes);
  setIntVar("meta test", &meta_test);

  TBL_ALLOC(global_line_tbl);
  TBL_ALLOC(str_pool);


   PDGCS_initialize(language,
                    init_flags,
                    cmp_name,
                    cmp_rel,
                    code_file_name,
                    list_file_name,
                    trunc_bits,
                    debug_opts,
                    src_path_name, /*get_src_path_name(),*/
                    cif_file_name,
                    debug_file_name,
                    NULL, /*debug_file,*/
                    NULL, /*cif_file,*/
                    src_fname, /*GL_FILE_NAME_PTR(1),*/
                    cwd,
                    n_pes,
                    meta_test);


}

void setup_fei_descriptor()
{
  static short s_first = 1;
  TYPE ret;
  
  INTPTR ID;
  INT32 flags;
  TABLE_TYPE table_type;
  INT32 table_idx;
  BASIC_TYPE basic_type;
  INT32 aux_info;
  INT32 alignment;

  setLongVar("AT TYP ID", &ID);
  setIntFlagsVar("flags", &flags);
  setEnumVar("table type", (int*)&table_type);
  setIntVar("bit size", &table_idx);
  setEnumVar("basic type", (int*)&basic_type);
  setIntVar("aux info", &aux_info);
  setIntVar("alignment", &alignment);

  ret = fei_descriptor                    ( flags,
                                            table_type,
                                            table_idx,
                                            basic_type,
                                            aux_info,
                                            alignment);

  if (s_first) {
  	s_first = 0;
  	null_type = ret;
  }

  addPdgTypeLink(AT_TYP, ID, ret);
}

void setup_fei_descriptor_size_cn_idx()
{
  TYPE ret;
  
  INTPTR ID;
  INT32 flags;
  TABLE_TYPE table_type;
  INTPTR table_idx;
  BASIC_TYPE basic_type;
  INT32 aux_info;
  INT32 alignment;

  setLongVar("AT TYP ID", &ID);
  setIntFlagsVar("flags", &flags);
  setEnumVar("table type", (int*)&table_type);
  setLongVar("PDG_CN_IDX", &table_idx);
  setEnumVar("basic type", (int*)&basic_type);
  setIntVar("aux info", &aux_info);
  setIntVar("alignment", &alignment);

  ret = fei_descriptor                    ( flags,
                                            table_type,
                                            PDG_CN_IDX(table_idx),
                                            basic_type,
                                            aux_info,
                                            alignment);

  addPdgTypeLink(AT_TYP, ID, ret);
}

void setup_fei_descriptor_size_at_typ_idx()
{
  TYPE ret;
  
  INTPTR ID;
  INT32 flags;
  TABLE_TYPE table_type;
  INTPTR table_idx;
  INTPTR table_idx2;
  BASIC_TYPE basic_type;
  INT32 aux_info;
  INT32 alignment;

  setLongVar("AT TYP ID", &ID);
  setIntFlagsVar("flags", &flags);
  setEnumVar("table type", (int*)&table_type);
  setLongVar("PDG_AT_TYP_INTERNAL_IDX", &table_idx);
  setEnumVar("basic type", (int*)&basic_type);
  setIntVar("aux info", &aux_info);
  setIntVar("alignment", &alignment);

  ret = fei_descriptor                    ( flags,
                                            table_type,
                                            PDG_AT_TYP_INTERNAL_IDX(table_idx),
                                            basic_type,
                                            aux_info,
                                            alignment);

  addPdgTypeLink(AT_TYP, ID, ret);
}

void setup_fei_descriptor_size_at_idx()
{
  TYPE ret;
  
  INTPTR ID;
  INT32 flags;
  TABLE_TYPE table_type;
  INTPTR table_idx;
  INTPTR table_idx2;
  BASIC_TYPE basic_type;
  INT32 aux_info;
  INT32 alignment;

  setLongVar("AT TYP ID", &ID);
  setIntFlagsVar("flags", &flags);
  setEnumVar("table type", (int*)&table_type);
  setLongVar("PDG_AT_IDX", &table_idx);
  setEnumVar("basic type", (int*)&basic_type);
  setIntVar("aux info", &aux_info);
  setIntVar("alignment", &alignment);

  ret = fei_descriptor                    ( flags,
                                            table_type,
                                            PDG_AT_IDX(table_idx),
                                            basic_type,
                                            aux_info,
                                            alignment);

  addPdgTypeLink(AT_TYP, ID, ret);
}

void setup_fei_next_func_idx()
{
  INTPTR ret;

  INTPTR ID;
  INT32 pgm_unit;
  INT32 proc;
  INT32 alt_entry;
  
  setLongVar("AT ID", &ID);
  setIntVar("ATP_PGM_UNIT", &pgm_unit);
  setIntVar("ATP_PROC", &proc);
  setIntVar("ATP_ALT_ENTRY", &alt_entry);

  ret = fei_next_func_idx                  ( pgm_unit,
                                            proc,
                                            alt_entry );

  addPdgLink(AT, ID, ret);
}

void setup_fei_seg()
{
  INTPTR ret;

  INTPTR ID;
  char name_string[1024] = "";
  INT32 seg_type;
  INT32 owner;
  INT32 flag_bits;
  INT64 block_length;
  
  setLongVar("SB ID", &ID);
  setStrVar("name_ptr", name_string);
  trim(name_string);
  setIntVar("segment type", &seg_type);
  setIntVar("parent_idx", &owner);
  setIntFlagsVar("flags", &flag_bits);
  setLongLongVar("blk length", &block_length);

  ret = fei_seg             	          ( name_string,
                                 	    seg_type,
                                 	    owner,
                                 	    0, /*INT32 parent,*/
                                 	    0, /*INT32 aux_index,*/
                                 	    flag_bits,
                                 	    0, /*INT32 nest_level,*/
                                 	    block_length );
  addPdgLink(SB, ID, ret);
}

void setup_fei_proc()
{
  INTPTR ret;

  INTPTR ID;
  char name_string[1024] = "";
  INT32 lineno;
  INT32 sym_class;
  INT32 Class;
  INT32 num_dum_args;
  INT32 parent_stx;
  INT32 first_st_idx;
  INT32 aux_idx;
  INTPTR type;
  INT32 st_idx;   
  INT64 flags;

  setLongVar("AT ID", &ID);
  setStrVar("name_ptr", name_string);
  trim(name_string);
  setIntVar("AT_DEF_LINE", &lineno);
  setEnumVar("pgm unit", &sym_class);
  setEnumVar("proc", &Class);
  setIntVar("num_dargs", &num_dum_args);
  setIntVar("parent_idx", &parent_stx);
  setIntVar("pdg darg list", &first_st_idx);
  setIntVar("alt link idx", &aux_idx);
  setLongVar("type", &type);
  setIntVar("PDG_AT_IDX", &st_idx);
  setLongLongFlagsVar("flags", &flags);
  
  ret = fei_proc            	          ( name_string,
                                 	    lineno,
                                 	    sym_class,
                                 	    Class,
                                 	    num_dum_args,
                                 	    parent_stx,
                                 	    PDG_AT_IDX(first_st_idx),
                                 	    PDG_AT_IDX(aux_idx),
                                 	    PDG_AT_TYP_IDX(type),
                                 	    PDG_AT_IDX(st_idx),
                                 	    flags );
  addPdgLink(AT, ID, ret);

}

void setup_fei_arith_con()
{
  long ret;
  
  INTPTR ID;
  INTPTR type;
  INT64 start;

  setLongVar("CN ID", &ID);
  setLongVar("type", &type);
  setLongLongVar("value", &start);

  ret =  fei_arith_con                    ( PDG_AT_TYP_IDX(type),
                                            (long*)&start );

  addPdgLink(CN, ID, ret);
}

void setup_cwh_add_to_used_files_table()
{
  static char name[1024];
  INT32  copy_name;
  INT32  found, idx;

  setStrVar("path", name);
  trim(name);
  setIntVar("one", &copy_name);

  cwh_add_to_used_files_table  (name, copy_name );
}


void setup_fei_object()
{

  long ret;
  
  INTPTR ID;
  char  name_string[1024];
  INTPTR  type;
  INT64 flag_bits;
  INT32 sym_class;
  INTPTR storage_idx;
  INT32 derive_st_idx;
  INTPTR ptr_st_idx;
  INT64 offset;
  INT32 arg_intent;
  INT64 size;
  INT32 type_aux;
  INT32 alignment;
  INT32 distr_idx;
  INTPTR node_1;
  INT32 node_2;
  INT32 line_num;
  
  setLongVar("AT ID", &ID);
  setStrVar("AT_OBJ_NAME", name_string);
  trim(name_string);
  setLongVar("type", &type);
  setLongLongFlagsVar("flags", &flag_bits);
  setEnumVar("symbol class", &sym_class);
  setLongVar("PDG_SB_IDX", &storage_idx);
  setIntVar("dv_alias", &derive_st_idx);
  setLongVar("ptr_idx", &ptr_st_idx);
  setLongLongVar("offset", &offset);
  setIntVar("intent", &arg_intent);
  setLongLongVar("bit_len", &size);
  setIntVar("pointee align", &type_aux);
  setIntVar("storage align", &alignment);
  setIntVar("unused", &distr_idx);
  setLongVar("io descriptor", &node_1);
  setIntVar("unused", &node_2);
  setIntVar("AT_DEF_LINE", &line_num);
  
  ret = fei_object          	  ( name_string,
                                 	    PDG_AT_TYP_IDX(type),
                                 	    flag_bits,
                                 	    sym_class,
                                 	    PDG_SB_IDX(storage_idx),
                                 	    derive_st_idx,
                                 	    (ptr_st_idx) ?
					       PDG_AT_IDX(ptr_st_idx) : 0,
                                 	    offset,
                                 	    arg_intent,
                                 	    size,
                                 	    type_aux,
                                 	    alignment,
                                 	    distr_idx,
                                 	    (node_1) ? PDG_CN_IDX(node_1) : 0,
                                 	    node_2,
                                 	    line_num );
  addPdgLink(AT, ID, ret);
}

void setup_fei_object_at_offset()
{

  long ret;
  
  INTPTR ID;
  char  name_string[1024];
  INTPTR  type;
  INT64 flag_bits;
  INT32 sym_class;
  INTPTR storage_idx;
  INT32 derive_st_idx;
  INTPTR ptr_st_idx;
  INT64 offset;
  INT32 arg_intent;
  INT64 size;
  INT32 type_aux;
  INT32 alignment;
  INT32 distr_idx;
  INTPTR node_1;
  INT32 node_2;
  INT32 line_num;
  
  setLongVar("AT ID", &ID);
  setStrVar("AT_OBJ_NAME", name_string);
  trim(name_string);
  setLongVar("type", &type);
  setLongLongFlagsVar("flags", &flag_bits);
  setEnumVar("symbol class", &sym_class);
  setLongVar("PDG_SB_IDX", &storage_idx);
  setIntVar("dv_alias", &derive_st_idx);
  setLongVar("ptr_idx", &ptr_st_idx);
  setLongLongVar("offset", &offset);
  setIntVar("intent", &arg_intent);
  setLongLongVar("bit_len", &size);
  setIntVar("pointee align", &type_aux);
  setIntVar("storage align", &alignment);
  setIntVar("unused", &distr_idx);
  setLongVar("io descriptor", &node_1);
  setIntVar("unused", &node_2);
  setIntVar("AT_DEF_LINE", &line_num);
  
  ret = fei_object          	  ( name_string,
                                 	    PDG_AT_TYP_IDX(type),
                                 	    flag_bits,
                                 	    sym_class,
                                 	    PDG_SB_IDX(storage_idx),
                                 	    derive_st_idx,
                                 	    (ptr_st_idx) ?
					       PDG_AT_IDX(ptr_st_idx) : 0,
                                 	    PDG_AT_IDX(offset),
                                 	    arg_intent,
                                 	    size,
                                 	    type_aux,
                                 	    alignment,
                                 	    distr_idx,
                                 	    (node_1) ? PDG_CN_IDX(node_1) : 0,
                                 	    node_2,
                                 	    line_num );
  addPdgLink(AT, ID, ret);
}

void setup_PDGCS_comp_unit()
{
  char comp_unit_name[1024];
  INT32 module_node;

  setStrVar("name_ptr", comp_unit_name);
  trim(comp_unit_name);
  ignoreVar("unused");

  PDGCS_comp_unit        	  ( comp_unit_name,
                                    0 );
}

void setup_fei_proc_body()
{
  INT32 lineno;

  setIntVar("SH_GLB_LINE", &lineno);

  fei_proc_body(lineno);
}

void setup_fei_stmt()
{
  INT32 lineno;
  INT32 flags;

  setIntVar("SH_GLB_LINE", &lineno);
  setIntFlagsVar("flags", &flags);

  fei_stmt(lineno, flags);
}


void  setup_fei_object_ref()
{
  char obj_name[1024] = "";
  INTPTR sym_idx;
  INT32 whole_subscript;
  INT32 whole_substring;
  unsigned int data_init = 0;

  setStrVar("AT_OBJ_NAME", obj_name);
  trim(obj_name);
  setLongVar("PDG_AT_IDX", &sym_idx);
  setIntVar("whole_subscript", &whole_subscript);
  setIntVar("whole_substring", &whole_substring);
  setIntVar("data_init", &data_init);
  
  fei_object_ref               (  PDG_AT_IDX(sym_idx),
                                  whole_subscript,
                                  whole_substring,
                                  data_init );
}

void setup_fei_constant()
{
  long ret;

  
  INTPTR ID;
  INTPTR type;
  INT32 typ_type;
  INT32 Class;
  INT64 start;
  char start_str[20000] = "";
  char *start_str_huge = NULL;
  INT64 bitsize;
  int replace_count;
  

  setLongVar("CN ID", &ID);
  setLongVar("type", &type);
  setIntVar("TYP_TYPE", &typ_type);
  setEnumVar("const class", &Class);
  setLongLongVar("bit length", &bitsize);
  
  if (Class == Pattern_Const && typ_type == 8) { /* Character*/

    if(bitsize > 8000) {
      start_str_huge = (char*)malloc((bitsize/8) +5);
      setStrVar("const", start_str_huge);
    } else 
      setStrVar("const", start_str);
	
  } else {
  
    if(bitsize > 8000) {
      start_str_huge = (char*)malloc((bitsize/8) +5);
      setTypelessPatternConstMultiLineVar("const", start_str_huge, bitsize);
    } else
      setTypelessPatternConstVar("const", start_str);
  }

#if 0
  if(Class == Pattern_Const && typ_type == 7) { /* Typless */
    setTypelessPatternConstVar("const", start_str);
    start_is_str = 1;
  } else if (Class == Pattern_Const && typ_type == 8) { /* Character*/
    setStrVar("const", start_str);
    start_is_str = 1;
  } else
    setLongLongVar("const", &start);
#endif


  ret = fei_constant ( PDG_AT_TYP_IDX(type),
                       Class,
                       /*(start_is_str) ? start_str : (char*)&start,*/
                       (start_str_huge) ? start_str_huge : start_str,
                       bitsize );
  addPdgLink(CN, ID, ret);
  if(start_str_huge)
    free(start_str_huge);
}

void setup_fei_pattern_con()
{
  INTPTR ret;
  INTPTR ID;
  INTPTR  type;
  INT32 typ_type;
  char start_str[20000];
  char *start_str_huge = NULL;
  INT64 bitsize;
  
  setLongVar("CN ID", &ID);
  setLongVar("PDG_AT_TYP_IDX", &type);
  setIntVar("TYP_TYPE", &typ_type);
  setLongLongVar("bit length", &bitsize);

  if (typ_type == 8) { /* Character*/
    setStrVar("const", start_str);
  } else {
    if(bitsize > 8000) {
      start_str_huge = (char*)malloc((bitsize/8) +5);
      setTypelessPatternConstMultiLineVar("const", start_str_huge, bitsize);
    } else
      setTypelessPatternConstVar("const", start_str);
  }

  ret = fei_pattern_con             ( PDG_AT_TYP_IDX(type),
                                       (start_str_huge) ? start_str_huge : start_str,
                                       bitsize );
  addPdgLink(CN, ID, ret);
  if(start_str_huge)
    free(start_str_huge);
}

void setup_fei_store()
{
  TYPE  type;

  // always void
  type = null_type;

  fei_store(type);

}


void  setup_fei_function_ref()
{
  INTPTR fnc_idx;

  ignoreVar("AT_OBJ_NAME");
  setLongVar("PDG_AT_IDX", &fnc_idx);
  
  fei_function_ref             ( PDG_AT_IDX(fnc_idx) );
}

void setup_fei_call()
{
  INT32 num_args;
  INTPTR  type;
  INT32 call_type;
  INT32 alt_return_flag;  
  INT32 inline_setting;
  INT64 flags;
  
  ignoreVar("AT_OBJ_NAME");
  setIntVar("num actual args", &num_args);
  setLongVar("type", &type);
  setIntVar("call type", &call_type);
  setIntVar("alt return", &alt_return_flag);
  setIntVar("IR_INLINE_STATE", &inline_setting);
  
  flags = 0;
  
  fei_call                     ( num_args,
                                 PDG_AT_TYP_IDX(type),
                                 call_type,
                                 alt_return_flag,
                                 inline_setting,
                                 flags );
}


void setup_PDGCS_do_proc()
{
	PDGCS_do_proc();
}

void setup_PDGCS_terminate()
{
	PDGCS_terminate();
}

void setup_PDGCS_end_procs()
{
  INT32 code_size;
  INT32 data_size;

  setIntVar("after pgm code", &code_size);
  setIntVar("after pgm data", &data_size);
  
  PDGCS_end_procs        	  ( &code_size,
                                &data_size );
}

void setup_PDGCS_new_proc()
{
  INT32 ir_count;
  INTPTR func_st_idx;
  INT32 alt_entry_count;
  INT32 scalar_opt_level;
  INT32 vector_opt_level;
  INT32 task_opt_level;
  INT32 opt_flags;
  INT32 user_mobes;
  INT32 user_sades;
  INT32 pipeline_opt_level;
  INT32 stream_opt_level;

  setIntVar("num ir", &ir_count);
  setLongVar("PDG_AT_IDX", &func_st_idx);
  setIntVar("# alt entries", &alt_entry_count);
  setIntVar("scalar level", &scalar_opt_level);
  setIntVar("vector level", &vector_opt_level);
  setIntVar("task level", &task_opt_level);
  setIntFlagsVar("flags", &opt_flags);
  setIntVar("user mobes", &user_mobes);
  setIntVar("user sades", &user_sades);

  pipeline_opt_level = 0;
  stream_opt_level = 0;
  
  PDGCS_new_proc         	  ( ir_count,
                                PDG_AT_IDX(func_st_idx),
                                alt_entry_count,
                                scalar_opt_level,
                                vector_opt_level,
                                task_opt_level,
                                opt_flags,
                                user_mobes,
                                user_sades,
                                pipeline_opt_level,
                                stream_opt_level );
}

void setup_PDGCS_end_comp_unit()
{
  PDGCS_end_comp_unit();
}

void setup_fei_null_expr()
{
  fei_null_expr();
}

void setup_fei_control_list()
{
  INT32 io_type;
  
  setEnumVar("io_type", &io_type);
  
  fei_control_list             ( io_type );
}

void setup_fei_IO_list()
{
  INT32 n_opnds;
  INT32 io_type;

  setIntVar("list count", &n_opnds);
  setEnumVar("io_type", &io_type);

  fei_IO_list(n_opnds, io_type);
}

void setup_fei_formatted_write()
{
  fei_formatted_write();
}

void setup_fei_push_arith_con()
{
  INTPTR cdx;

  setLongVar("PDG_CN_IDX", &cdx);

  fei_push_arith_con(PDG_CN_IDX(cdx));

}

void setup_fei_iotype()
{
  fei_iotype();
}

void setup_fei_user_code_start()
{
  fei_user_code_start();
}

void setup_fei_start_ioblock()
{
  fei_start_ioblock();
}

void setup_fei_end_ioblock()
{
  fei_end_ioblock();
}

void setup_fei_label()
{
  INT32 ret;
  
  INTPTR ID;
  char  name_string[1024];
  INT32 flag_bits;
  INT32 Class;
  char  format_string[100000];
  INT32 debug_label_type;
  
  setLongVar("AT ID", &ID);
  setStrVar("AT_OBJ_NAME", name_string);
  trim(name_string);
  setIntFlagsVar("flags", &flag_bits);
  setEnumVar("label class", &Class);
  setStrVar("fmt_ptr", format_string);
  setIntVar("ATL_DEBUG_CLASS", &debug_label_type);
  
  ret = fei_label           	  ( name_string,
                              	    flag_bits,
                               	    Class,
                               	    format_string, 
                               	    debug_label_type );

  addPdgLink(AT, ID, ret);
}

void setup_fei_goto()
{
  INT32 lbl_idx;
  
  setIntVar("PDG_AT_IDX", &lbl_idx);
  
  fei_goto(PDG_AT_IDX(lbl_idx));
}

void setup_fei_label_def_named()
{
  INT32 lbl_idx;
  INT64 label_flag_word;
  INT32 lineno;
  INT32 sup_cnt;
  INT32 keepme;
  INT32 storage_seg;
  INT32 safevl;
  INT32 unroll_cnt;
  char  mark_name[1024];
  INT32 noncache_cnt;
  INT32 safedist;
  INT32 blockable_grp;
  INT32 interchange_grp;
  INT32 interchange_lvl;

  ignoreVar("AT_OBJ_NAME");
  setIntVar("PDG_AT_IDX", &lbl_idx);
  setLongLongFlagsVar("flags", &label_flag_word);
  setIntVar("line num", &lineno);
  setIntVar("suppress cnt", &sup_cnt);
  setIntVar("keep me", &keepme);
  setIntVar("safevl", &safevl);
  setIntVar("unroll cnt", &unroll_cnt);
  setStrVar("mark name", mark_name);
  setIntVar("cache bypass ct", &noncache_cnt);
  setIntVar("safe distance", &safedist);
  setIntVar("blockable grp", &blockable_grp);
  setIntVar("interchange grp", &interchange_grp);
  setIntVar("interchange lvl", &interchange_lvl);

  fei_label_def_named          (PDG_AT_IDX(lbl_idx),
                                label_flag_word,
                                lineno,
                                sup_cnt,
                                keepme,
                                0, /*INT32 storage_seg,*/
                                safevl,
                                unroll_cnt,
				mark_name,
                                noncache_cnt,
                                safedist,
                                blockable_grp,
                                interchange_grp,
                                interchange_lvl);

}

void setup_fei_if()
{
  fei_if();
}

void setup_fei_else()
{
  fei_else();
}

void setup_fei_endif()
{
  fei_endif();
}

void setup_fei_static_base()
{

  INTPTR st_idx;
  
  ignoreVar("AT_OBJ_NAME");
  setLongVar("PDG_AT_IDX", &st_idx);

  fei_static_base(PDG_AT_IDX(st_idx));
}

void setup_fei_static_simple_init()
{
  INT64 dup_count;
  INT64 stride;
  INT32 ignore_types;
  INT32 string_literal;
  
  setLongLongVar("rep_count", &dup_count);
  setLongLongVar("stride", &stride);
  setIntVar("ignore_types", &ignore_types);
  setIntVar("string_literal", &string_literal);
  
  fei_static_simple_init       ( dup_count,
                                 stride,
                                 ignore_types,
                                 string_literal );

}


void setup_fei_static_next_simple_init()
{
  INT64 CHAR_BIT;
  INT64 pad;
  INT64 offset;
  
  setLongLongVar("CHAR_BIT", &CHAR_BIT);
  setLongLongVar("pad", &pad);
  setLongLongVar("offset", &offset);
  
  fei_static_next_simple_init  ( CHAR_BIT,
                                 pad,
                                 offset,
                                 0 );

}

void setup_fei_arg_addr()
{
  INTPTR type;

  setLongVar("type", &type);

  fei_arg_addr(PDG_AT_TYP_IDX(type));
}

void setup_fei_return()
{

  INT32 return_class;
  INTPTR type;
  
  setEnumVar("return_kind", &return_class);
  setLongVar("type", &type);
  
  fei_return(return_class, PDG_AT_TYP_IDX(type));
}

void setup_fei_doloop()
{

  INT32 line;
  
  setIntVar("line", &line);

  fei_doloop(line);
}

void setup_fei_dowhile()
{
  fei_dowhile();
}

void setup_fei_doforever()
{
  fei_doforever();
}

void setup_fei_enddo()
{
  fei_enddo();
}

void setup_fei_array_dimen()
{

  INTPTR ret;
  
  INTPTR ID;
  INT32 flag_bits;
  INT64 low_bound;
  INT64 extent;
  INT32 rank;
  INTPTR span_type;
  INT64 bitsize;
  INT32 distribution;
  INT64 upper_bound;
  setLongVar("AT ID", &ID);
  setIntFlagsVar("flags", &flag_bits);
  setLongLongVar("lbound", &low_bound);
  setLongLongVar("extent", &extent);
  setIntVar("rank", &rank);
  setLongVar("type", &span_type);
  setLongLongVar("span", &bitsize);
  setIntVar("distribution", &distribution);
  setLongLongVar("ubound", &upper_bound);

  ret = fei_array_dimen     	  ( flag_bits,
                                    (flag_bits & (1<<FEI_ARRAY_DIMEN_VARY_LB)) ?
				      PDG_AT_IDX(low_bound) : low_bound,
                                    (flag_bits & (1<<FEI_ARRAY_DIMEN_VARY_EXT)) ?
				      PDG_AT_IDX(extent) : extent,
                                    rank,
                                    PDG_AT_TYP_IDX(span_type),
                                    bitsize,
                                    distribution,
                                    (flag_bits & (1<<FEI_ARRAY_DIMEN_VARY_UB)) ?
				      PDG_AT_IDX(upper_bound) : upper_bound );

  addPdgLink(AT, ID, ret);

}

void setup_fei_subscr_triplet()
{
  fei_subscr_triplet(null_type);
}

void setup_fei_subscr_size()
{

  INTPTR type;
  INT32 bounds_check;
  
  setLongVar("type", &type);
  setIntVar("bound check", &bounds_check);

  fei_subscr_size( PDG_AT_TYP_IDX(type), bounds_check );
}

void setup_fei_seq_subscr()
{

  INTPTR type;

  setLongVar("type", &type);

  fei_seq_subscr(PDG_AT_TYP_IDX(type));
}

void setup_fei_substr()
{

  INT32 bound_chk;
  
  setIntVar("bound_chk", &bound_chk);
  
  fei_substr(bound_chk);
}

void setup_fei_paren()
{

  INTPTR type;
  
  setLongVar("type", &type);

  fei_paren(PDG_AT_TYP_IDX(type));
}

void setup_fei_backspace()
{
  fei_backspace();
}

void setup_fei_close()
{
  fei_close();
}

void setup_fei_endfile()
{
  fei_endfile();
}

void setup_fei_inquire()
{
  fei_inquire();
}

void setup_fei_open()
{
  fei_open();
}

void setup_fei_rewind()
{
  fei_rewind();
}

void setup_fei_malloc()
{
  fei_malloc();
}

void setup_fei_mfree()
{
  fei_mfree();
}

void setup_fei_addr()
{
  INTPTR type;

  setLongVar("type", &type);

  fei_addr(PDG_AT_TYP_IDX(type));
}

void setup_fei_cvtop()
{
  INTPTR type;

  setLongVar("PDG_AT_TYP_IDX", &type);

  fei_cvtop(PDG_AT_TYP_IDX(type));
}

void setup_formatted_read()
{
  fei_formatted_read();
}

void setup_unformatted_read()
{
  fei_unformatted_read();
}

void setup_fei_namelist()
{

  INTPTR ret;

  INTPTR ID;

  char   name_string[1024];
  INT32  nitems;
  INTPTR idx;
  
  setLongVar("AT ID", &ID);
  setStrVar("AT_OBJ_NAME", name_string);
  setIntVar("count", &nitems);
  setLongVar("prev_idx", &idx);

  ret = fei_namelist         	  ( name_string,
                        	    nitems,
                        	    PDG_AT_IDX(idx));

  addPdgLink(AT, ID, ret);
  
}

void setup_fei_static_substr()
{
  INT32 start;
  
  setIntVar("constant", &start);

  fei_static_substr(start);
}

void setup_fei_namelist_write()
{
  fei_namelist_write();
}

void setup_fei_namelist_read()
{
  fei_namelist_read();
}

void setup_fei_static_subscripts()
{
  int i;
  INT64 subscripts[7];
  INT32 num_subscripts;
  
  setIntVar("num subscripts", &num_subscripts);
  for(i = 0; i < num_subscripts; i++)
    setLongLongVar("static subscript", &subscripts[i]); 

  fei_static_subscripts(subscripts);
}

void setup_fei_namelist_ref()
{
  INTPTR sym_idx;

  ignoreVar("AT_OBJ_NAME");
  setLongVar("PDG_AT_IDX", &sym_idx);
  fei_namelist_ref(PDG_AT_IDX(sym_idx));
}

void setup_fei_label_ref()
{
  INTPTR lbl_idx;
  
  setLongVar("PDG_AT_IDX", &lbl_idx);
  
  fei_label_ref(PDG_AT_IDX(lbl_idx));
}

void setup_fei_brtrue()
{
  INT32 lbl_idx;
  
  setIntVar("PDG_AT_IDX", &lbl_idx);

  fei_brtrue(PDG_AT_IDX(lbl_idx));
}

void setup_fei_implied_do()
{
  fei_implied_do();
}

void setup_fei_unformatted_write()
{

  fei_unformatted_write();
}

void setup_fei_concat()
{
  INT32 n_opnds;
  
  setIntVar("num ops", &n_opnds);
  
  fei_concat(n_opnds);
}

void setup_fei_entry_pt()
{
  INTPTR st_idx;
  
  setLongVar("PDG_AT_IDX", &st_idx);
  
  fei_entry_pt(PDG_AT_IDX(st_idx));
}

void setup_fei_dope_vector()
{
  TYPE ret;

  INTPTR ID;
  INT32 num_dims;
  INTPTR  base_type;
  INT32 flags;

  setLongVar("AT TYP ID", &ID);
  setIntVar("rank", &num_dims);
  setLongVar("PDG_AT_TYP_IDX", &base_type);
  setIntFlagsVar("flags", &flags);
  
  ret = fei_dope_vector              ( num_dims, 
                                       PDG_AT_TYP_IDX(base_type),
                                       flags );

  addPdgTypeLink(AT_TYP, ID, ret);
}

void setup_fei_dv_def()
{
  INT32 num_dims;
  
  setIntVar("dim", &num_dims);

  fei_dv_def(num_dims);
}

void setup_fei_dv_deref()
{
  /* always NULL type */
  fei_dv_deref(null_type);
}

void setup_fei_set_dv_hdr_fld()
{

  INT32 field;
  
  setIntVar("field num", &field);

  fei_set_dv_hdr_fld(field);
}

void setup_fei_get_dv_hdr_fld()
{

  INT32 field;
  
  setIntVar("field num", &field);

  fei_get_dv_hdr_fld(field);
}

void setup_fei_mask()
{
  INTPTR type;
  
  setLongVar("PDG_AT_TYP_IDX", &type);
  
  fei_mask(PDG_AT_TYP_IDX(type));
}

void setup_fei_static_simple_reloc_init()
{

  INT64 bit_offset;
  INT64 dup_count;
  INT64 stride;
  INT64 bit_size;
  INT32 ignore_types;

  setLongLongVar("offset", &bit_offset);
  setLongLongVar("rep count", &dup_count);
  setLongLongVar("stride", &stride);
  setLongLongVar("bit size", &bit_size);
  setIntVar("ignore_types", &ignore_types);
  
  fei_static_simple_reloc_init ( bit_offset, 
                                 dup_count,
                                 stride,
                                 bit_size,
                                 ignore_types );
}

void setup_fei_set_dv_low_bnd()
{
  INT32 dim;
  
  setIntVar("dim", &dim);
  
  fei_set_dv_low_bnd(dim);
}

void setup_fei_set_dv_extent()
{
  INT32 dim;
  
  setIntVar("dim", &dim);
  
  fei_set_dv_extent(dim);
}

void setup_fei_set_dv_str_mult()
{
  INT32 dim;
  
  setIntVar("dim", &dim);
  
  fei_set_dv_str_mult(dim);
}

void setup_fei_new_select()
{
  INT32 num_cases;
  INT32 default_label_idx;
  
  setIntVar("num cases", &num_cases);
  setIntVar("default label", &default_label_idx);
  
  fei_new_select      	  ( num_cases,
                            PDG_AT_IDX(default_label_idx));
}

void setup_fei_index()
{
  fei_index();
}

void setup_fei_alloc()
{
  fei_alloc();
}

void setup_fei_free()
{
  fei_free();
}

void setup_fei_allocate()
{
  INT32 nargs;
  
  setIntVar("list count", &nargs);
  
  fei_allocate(nargs);
}

void setup_fei_get_dv_low_bnd()
{
  INT32 dim;
  INT32 expand;
  
  setIntVar("dim", &dim);
  setIntVar("expand", &expand);
  
  fei_get_dv_low_bnd(dim, expand);
}

void setup_fei_get_dv_extent()
{
  INT32 dim;
  INT32 expand;
  
  setIntVar("dim", &dim);
  setIntVar("expand", &expand);
  
  fei_get_dv_extent(dim, expand);
}

void setup_fei_get_dv_str_mult()
{
  INT32 dim;
  INT32 expand;
  
  setIntVar("dim", &dim);
  setIntVar("expand", &expand);
  
  fei_get_dv_str_mult(dim, expand);
}

void setup_fei_nseq_subscr()
{
  fei_nseq_subscr(null_type);
}

void setup_fei_dv_ptr_asg()
{
  fei_dv_ptr_asg();
}

void setup_fei_present()
{
  fei_present();
}

void setup_fei_as_ref()
{
  fei_as_ref(null_type);
}

void setup_PDGCS_debug_init()
{
  char  org_file_name[1024];
  char  comp_gen_date[1024];
  
  setStrVar("src path name", org_file_name);
  setStrVar("gen date", comp_gen_date);
  
  PDGCS_debug_init       	  ( org_file_name,
                                    comp_gen_date );
}

void setup_fei_smt_actual_to_generic()
{
  INT32 act_st_idx;
  char generic_name[1024];
  
  setIntVar("PDG_AT_IDX", &act_st_idx);
  setStrVar("AT_OBJ_NAME", generic_name);
  fei_smt_actual_to_generic    ( act_st_idx,
                                 generic_name );
}

void setup_fei_smt_parameter()
{
  char name_string[1024];
  INTPTR type;
  INT32 con_idx;
  INT32 Class;
  INT32 line_num;
  
  setStrVar("AT_OBJ_NAME", name_string);
  setLongVar("PDG_AT_TYP_IDX", &type);
  setIntVar("PDG_CN_IDX", &con_idx);
  setIntVar("constant_class", &Class);
  setIntVar("line num", &line_num);
  
  /* ignore return*/
  fei_smt_parameter           ( name_string,
                                PDG_AT_TYP_IDX(type),
                                PDG_CN_IDX(con_idx),
                                Class,
                                line_num );
}

void setup_fei_where()
{
  INT32 defined_asg;
  INT32 inline_state;
  
  setIntVar("defined_asg", &defined_asg);

  /* inline state not supported in ABSOFT fe*/
  inline_state = 0;
  
  fei_where                    ( defined_asg,
                                 inline_state );
}

void setup_fei_new_select_case()
{
  INT64 low_value_pres;
  INT64 high_value_pres;
  INT32 case_follows;
  
  setLongLongVar("low_range", &low_value_pres);
  setLongLongVar("high_range", &high_value_pres);
  setIntVar("constant", &case_follows);
  fei_new_select_case 	  ( low_value_pres,
                            high_value_pres,
                            case_follows );
}

void setup_fei_add_use_path()
{
  INT32 st_idx;
  INT32 path_idx;
  INT32 module_idx;
  
  setIntVar("PDG_AT_IDX", &st_idx);
  setIntVar("path index", &path_idx);
  setIntVar("name index", &module_idx);
  
  fei_add_use_path             ( PDG_AT_IDX(st_idx),
                                 PDG_AT_IDX(path_idx),
                                 PDG_AT_IDX(module_idx) );
}

void setup_fei_static_member()
{

  INT32 st_idx;
  
  ignoreVar("AT_OBJ_NAME");
  setIntVar("PDG_AT_IDX", &st_idx);
  
  fei_static_member(PDG_AT_IDX(st_idx));
}

void setup_fei_fcd()
{
  INTPTR type_idx;
  
  setLongVar("PDG_AT_TYP_IDX", &type_idx);
  
  fei_fcd(PDG_AT_TYP_IDX(type_idx));
}

int ignoreVar(char *label)
{
  lineNo++;
  if(!fgets(inLine, MAX_LINE_LEN, infile))
    printError("Unexpected EOF");
  strtok(&inLine[START_COL], "=");
  trim(&inLine[START_COL]);
  return checkLabel(label, &inLine[START_COL]);
}

int setStrVar(char *label, char *out)
{
  lineNo++;

  if(!fgets(inLine, MAX_LINE_LEN, infile))
    printError("Unexpected EOF");

  int i = START_COL;
  int j = 0;
  while(inLine[++i] != '\n' && inLine[i] != '=')
    LHS[j++] = inLine[i];
  LHS[j] = '\0';
  trim(LHS);
  
  j = 0; i++;
  while(inLine[++i] != '\n') {
        if(inLine[i] == '\\' && inLine[i+1] == '\\') {
	    RHS[j++] = '\\';
	    i ++;
        } else if(inLine[i] == '\\' && inLine[i+1] == 'n') {
	    RHS[j++] = '\n';
	    i ++;
	} else if(inLine[i] == '\\' && inLine[i+1] == 'r') {
	    RHS[j++] = '\r';
	    i ++;
	} else if(inLine[i] == '\\' && inLine[i+1] == 't') {
	    RHS[j++] = '\t';
	    i ++;
	} else if(inLine[i] == '\\' && inLine[i+1] == '0') {
	    RHS[j++] = '\0';
	    i ++;
	} else
	    RHS[j++] = inLine[i];
  }
  RHS[j] = '\0';
//    trim(RHS);

  int err = checkLabel(label, LHS);
  strcpy(out, RHS);
//    trim(out);
  return err;
}

int setLongLongVar(char *label, long long *out)
{
  lineNo++;
  if(!fgets(inLine, MAX_LINE_LEN, infile))
    printError("Unexpected EOF");

  int i = START_COL;
  int j = 0;
  while(inLine[++i] != '\n' && inLine[i] != '=')
    LHS[j++] = inLine[i];
  LHS[j] = '\0';
  trim(LHS);
  
  j = 0; i++;
  while(inLine[++i] != '\n')
    RHS[j++] = inLine[i];
  RHS[j] = '\0';
  trim(RHS);

  int err = checkLabel(label, LHS);
  sscanf(RHS, "%lld", out);
//  *out = atoi(RHS);
  return err;
}

int setLongLongFlagsVar(char *label, long long *out)
{
  lineNo++;
  if(!fgets(inLine, MAX_LINE_LEN, infile))
    printError("Unexpected EOF");

  int i = START_COL;
  int j = 0;
  int digit;
  while(inLine[++i] != '\n' && inLine[i] != '=')
    LHS[j++] = inLine[i];
  LHS[j] = '\0';
  trim(LHS);
  
  j = 0; i++;
  while(inLine[++i] != '\n')
    RHS[j++] = inLine[i];
  RHS[j] = '\0';
  trim(RHS);

  int err = checkLabel(label, LHS);

  *out = 0;  
  for(i = strlen(RHS)-1; i >= 0; i --) {
    digit = strlen(RHS)-1 - i;
    *out += (RHS[i]-'0') * pow(8,digit);
  }
  return err;
}

int setIntFlagsVar(char *label, INT32 *out)
{
  lineNo++;
  if(!fgets(inLine, MAX_LINE_LEN, infile))
    printError("Unexpected EOF");

  int i = START_COL;
  int j = 0;
  int digit;
  while(inLine[++i] != '\n' && inLine[i] != '=')
    LHS[j++] = inLine[i];
  LHS[j] = '\0';
  trim(LHS);
  
  j = 0; i++;
  while(inLine[++i] != '\n')
    RHS[j++] = inLine[i];
  RHS[j] = '\0';
  trim(RHS);

  int err = checkLabel(label, LHS);

  *out = 0;  
  for(i = strlen(RHS)-1; i >= 0; i --) {
    digit = strlen(RHS)-1 - i;
    *out += (RHS[i]-'0') * pow(8,digit);
  }
  return err;
}

int setLongVar(char *label, long *out)
{
  lineNo++;
  if(!fgets(inLine, MAX_LINE_LEN, infile))
    printError("Unexpected EOF");

  int i = START_COL;
  int j = 0;
  while(inLine[++i] != '\n' && inLine[i] != '=')
    LHS[j++] = inLine[i];
  LHS[j] = '\0';
  trim(LHS);
  
  j = 0; i++;
  while(inLine[++i] != '\n')
    RHS[j++] = inLine[i];
  RHS[j] = '\0';
  trim(RHS);

  int err = checkLabel(label, LHS);
  *out = atol(RHS);
  return err;
}

int setIntVar(char *label, int *out)
{
  lineNo++;
  if(!fgets(inLine, MAX_LINE_LEN, infile))
    printError("Unexpected EOF");

  int i = START_COL;
  int j = 0;
  while(inLine[++i] != '\n' && inLine[i] != '=')
    LHS[j++] = inLine[i];
  LHS[j] = '\0';
  trim(LHS);
  
  j = 0; i++;
  while(inLine[++i] != '\n')
    RHS[j++] = inLine[i];
  RHS[j] = '\0';
  trim(RHS);

  int err = checkLabel(label, LHS);
  *out = atoi(RHS);
  return err;
}

int setEnumVar(char *label, int *out)
{
  lineNo++;
  if(!fgets(inLine, MAX_LINE_LEN, infile))
    printError("Unexpected EOF");

  int i = START_COL;
  int j = 0;
  while(inLine[++i] != '\n' && inLine[i] != '=')
    LHS[j++] = inLine[i];
  LHS[j] = '\0';
  trim(LHS);
  
  j = 0; i++;
  while(inLine[++i] != '\n' && inLine[i] != '(')
    RHS[j++] = inLine[i];
  RHS[j] = '\0';
  trim(RHS);

  int err = checkLabel(label, LHS);
  *out = atoi(RHS);
  return err;
}

int setTypelessPatternConstVar(char *label, char *out)
{
  char patternLine[MAX_PATTERN_LINE_LEN];
  lineNo++;
  if(!fgets(inLine, MAX_PATTERN_LINE_LEN, infile))
    printError("Unexpected EOF");

  int i = START_COL;
  int j = 0;
  while(inLine[++i] != '\n' && inLine[i] != '=')
    LHS[j++] = inLine[i];
  LHS[j] = '\0';
  trim(LHS);
  
  j = 0; i++;
  while(inLine[++i] != '\n' && inLine[i] != '(')
    RHS[j++] = inLine[i];
  RHS[j] = '\0';
  trim(RHS);

  int err = checkLabel(label, LHS);
  
  i = 0;
  char *temp;
  temp = strtok(RHS, "~");
  while(temp) {
    sscanf(temp, "%lx", ((unsigned long*)&(out[i*4])));
    i++;
    temp = strtok(NULL, "~");
  }
  return err;
}

int setTypelessPatternConstMultiLineVar(char *label, char *out, long long bit_length)
{
  int num_lines = (int)(((bit_length)/32)/1000);
  if(!num_lines)
    num_lines = 1;
  else if( (bit_length - (num_lines*32000)) > 0 ){
    num_lines ++;
  }
/* YINMA: Don't what's this for " 
   else if((((bit_length+31)/32) % 1000 == 0))
    num_lines--;*/
  lineNo++;

  int i = START_COL;
  int j = 0;
  int k = 0;
  int out_count = 0;

  if(!fgets(inLine, MAX_PATTERN_LINE_LEN, infile))
    printError("Unexpected EOF");

  while(inLine[++i] != '\n' && inLine[i] != '=')
    LHS[j++] = inLine[i];
  LHS[j] = '\0';
  trim(LHS);
  int err = checkLabel(label, LHS);
  
  for(k = 0; k < num_lines; k++) {
    j = 0;
    if(k == 0)
      i++;
    else {
      if(!fgets(inLine, MAX_PATTERN_LINE_LEN, infile))
        printError("Unexpected EOF");
      lineNo++;
      i = -1;
    }
      
    while(inLine[++i] != '\n' && inLine[i] != '(')
      RHS[j++] = inLine[i];
    RHS[j] = '\0';
    trim(RHS);

    char *temp;
    temp = strtok(RHS, "~");
    while(temp) {
      sscanf(temp, "%lx", ((unsigned long*)&(out[out_count*4])));
      out_count++;
      temp = strtok(NULL, "~");
    }
  }
  
  return err;
}

void printError(char *text)
{
  if(!lineNo)
    printf("Error: %s\n", text);
  else
    printf("Error on line %d: %s\n", lineNo, text);
  exit(1);
}

void trim(char s[])
{
  int n, start, len;
  for(n = strlen(s)-1; n >=0; n--)
    if(s[n] != ' ' && s[n] != '\t' && s[n] != '\n')
      break;
  s[n+1] = '\0';
  
  for(n = 0; n < strlen(s); n++)
    if(s[n] != ' ' && s[n] != '\t' && s[n] != '\n')
      break;
  start = n;
  len = strlen(s)-start;
  for(n = 0; n < len; n++)
    s[n] = s[n+start];
  s[len] = '\0';
}

void addPdgTypeLink(pdg_type_enum type, long idx, TYPE contents)
{
  if(type == AT_TYP && idx >= reader_pdg_type_tbl_idx) {
    reader_pdg_type_tbl = (PDG_TYPE*)realloc(reader_pdg_type_tbl,(reader_pdg_type_tbl_idx+1)*sizeof(PDG_TYPE));
    reader_pdg_type_tbl_idx++;
  }

  PDG_AT_TYP_IDX(idx) = contents;

}

void addPdgTypeInternalLink(pdg_type_enum type, long idx, long contents)
{
  if(idx < 0)
    return;

  if(type == AT_TYP && idx >= reader_pdg_type_tbl_idx) {
    reader_pdg_type_tbl = (PDG_TYPE*)realloc(reader_pdg_type_tbl, (reader_pdg_type_tbl_idx+1)*sizeof(PDG_TYPE));
    reader_pdg_type_tbl_idx++;
  }

  PDG_AT_TYP_INTERNAL_IDX(idx) = contents;

}

void addPdgLink(pdg_type_enum type, long idx, long contents)
{
  if(idx < 0)
    return;
    
  if(idx >= reader_pdg_link_tbl_idx) {
    TBL_REALLOC_CK(reader_pdg_link_tbl, 1);
    PDG_AT_IDX(idx) = 0;
    PDG_CN_IDX(idx) = 0;
    PDG_SB_IDX(idx) = 0;
  }

  switch(type) {
    case AT:
      PDG_AT_IDX(idx) = contents;
      break;
    case CN:
      PDG_CN_IDX(idx) = contents;
      break;
    case SB:
      PDG_SB_IDX(idx) = contents;
      break;
    case AT_TYP:
      printError("Called addPdgLink, should call addPdgTypeLink");
      break;
  };  
}

void initPdgTbl()
{
  TBL_ALLOC(reader_pdg_link_tbl);
  reader_pdg_link_tbl_idx = 0;
  TBL_REALLOC_CK(reader_pdg_link_tbl, 1);
  PDG_AT_IDX(0) = 0;
  PDG_CN_IDX(0) = 0;
  PDG_SB_IDX(0) = 0;
  PDG_AT_IDX(1) = 0;
  PDG_CN_IDX(1) = 0;
  PDG_SB_IDX(1) = 0;
  reader_pdg_type_tbl = (PDG_TYPE*)malloc(2*sizeof(PDG_TYPE));
  reader_pdg_type_tbl_idx = 1;
}
