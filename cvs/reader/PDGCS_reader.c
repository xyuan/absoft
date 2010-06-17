
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

#include "PDGCS_reader.h"

FILE *infile = NULL;
long lineNo = 0;
char inLine[200000] = "";
int START_COL = -1;

extern int VF_CHAR_OPTION;
extern int One_Trip_Do_Loops;
extern int Standard_Return;
extern long Debug_Level;
extern int Pointer_Size;
extern char *Irb_File_Name;
extern char * ABI_Name;
extern int Gen_PIC_Shared;
extern int Debug_Name_Folding;

int main (int argc, char *argv[])
{
  int currArg = 1;
  int lastArg = 0;
  int i;
  
  if(argc < 4 || argc > 8) {
    printError("Usage: PDGCS_read [-g] [-TARG:abi=nXX] [-TENV:PIC] -o <output_file> <input_file>\n");
    exit(1);
  }

  while( lastArg != currArg ){
	lastArg = currArg;
	if(!strncmp(argv[currArg], "-g",2)) {
	    if(argv[currArg][2] == '\0')
	       Debug_Level = 2;
	    else
	       Debug_Level = atoi(&argv[currArg][2]);
	    currArg++;
	}
	
	if (!strncmp(argv[currArg], "-ej",3)) {
		One_Trip_Do_Loops = 1;
		currArg++;
	}

	if (!strncmp(argv[currArg], "-YVF_CHAR",9)) {
		VF_CHAR_OPTION = 1;
		currArg++;
	}
	
	if (!strncmp(argv[currArg], "-TENV:PIC",9)) {
		Gen_PIC_Shared = 1;
		currArg++;
	}
	
	if (!strncmp(argv[currArg], "-TARG:abi=n32",13)) {
		ABI_Name = "n32";
		currArg++;
	}
	
	if (!strncmp(argv[currArg], "-TARG:abi=n64",13)) {
		ABI_Name = "n64";
		currArg++;
	}
	
	if (!strncmp(argv[currArg], "-std_return",11)) {
		Standard_Return = 1;
		currArg++;
	}
 	
	if(!strncmp(argv[currArg], "-f90debug_names:folded",22)){
		Debug_Name_Folding = 1;
		currArg++;
	}

	if(!strncmp(argv[currArg], "-f90debug_names:asis",20)){
		Debug_Name_Folding = 0;
		currArg++;
	}
  }

  PDGCS_entry_no_SGI_fe();

  if(strcmp(argv[currArg], "-o")) {
    printError("Usage: no output file specified\n");
    for(i = 0; i < argc; i++)
      printf("%s\n", argv[i]);
  }
  currArg++;

  Irb_File_Name = strdup(argv[currArg]);
  currArg++;
  
  infile = fopen(argv[currArg], "r");
  
  if(!infile)
  {
    char buf[1024];
    sprintf(buf, "Unable to open file: \"%s\"", argv[currArg]);
    printError(buf);
  }
    
  initPdgTbl();
  
  while(processCall());
  
  return 0;
}

/* line points to first line of call */
int processCall()
{
  char callName[MAX_LINE_LEN];
  
  if(!setCallName(callName))
    return 0;
  
  if(!strcmp(callName, "PDGCS_initialize"))
    setup_PDGCS_initialize();
  else if(!strcmp(callName, "fei_descriptor"))
    setup_fei_descriptor();
  else if(!strcmp(callName, "fei_descriptor_size_cn_idx"))
    setup_fei_descriptor_size_cn_idx();
  else if(!strcmp(callName, "fei_next_func_idx"))
    setup_fei_next_func_idx();
  else if(!strcmp(callName, "fei_seg"))
    setup_fei_seg();
  else if(!strcmp(callName, "fei_proc"))
    setup_fei_proc();
  else if(!strcmp(callName, "fei_arith_con"))
    setup_fei_arith_con();
  else if(!strcmp(callName, "cwh_add_to_used_files_table"))
    setup_cwh_add_to_used_files_table();
  else if(!strcmp(callName, "fei_object"))
    setup_fei_object();
  else if(!strcmp(callName, "fei_object_at_offset"))
    setup_fei_object_at_offset();
  else if(!strcmp(callName, "PDGCS_comp_unit"))
    setup_PDGCS_comp_unit();
  else if (!strcmp(callName, "fei_proc_body"))
  	setup_fei_proc_body();
  else if (!strcmp(callName, "fei_stmt"))
  	setup_fei_stmt();
  else if (!strcmp(callName, "fei_object_ref"))
    setup_fei_object_ref();
  else if (!strcmp(callName, "fei_constant"))
  	setup_fei_constant();
  else if (!strcmp(callName, "fei_store"))
    setup_fei_store();
  else if (!strcmp(callName, "fei_function_ref"))
    setup_fei_function_ref();
  else if (!strcmp(callName, "fei_call"))
  	setup_fei_call();
  else if (!strcmp(callName, "PDGCS_do_proc"))
  	setup_PDGCS_do_proc();
  else if (!strcmp(callName, "PDGCS_end_procs"))
  	setup_PDGCS_end_procs();
  else if (!strcmp(callName, "PDGCS_terminate"))
  	setup_PDGCS_terminate();
  else if (!strcmp(callName, "PDGCS_new_proc"))
  	setup_PDGCS_new_proc();
  else if (!strcmp(callName, "PDGCS_end_comp_unit"))
    setup_PDGCS_end_comp_unit();
  else if (!strcmp(callName, "fei_null_expr"))
    setup_fei_null_expr();
  else if (!strcmp(callName, "fei_control_list"))
    setup_fei_control_list();
  else if (!strcmp(callName, "fei_IO_list"))
    setup_fei_IO_list();
  else if (!strcmp(callName, "fei_formatted_write"))
    setup_fei_formatted_write();
  else if (!strcmp(callName, "fei_push_arith_con"))
    setup_fei_push_arith_con();
  else if (!strcmp(callName, "fei_iotype"))
    setup_fei_iotype();
  else if (!strcmp(callName, "fei_user_code_start"))
    setup_fei_user_code_start();
  else if (!strcmp(callName, "fei_cos"))
    setup_fei_cos();
  else if (!strcmp(callName, "fei_start_ioblock"))
    setup_fei_start_ioblock();
  else if (!strcmp(callName, "fei_end_ioblock"))
    setup_fei_end_ioblock();
  else if (!strcmp(callName, "fei_next_name"))
    setup_fei_next_name();
  else if (!strcmp(callName, "fei_next_type_idx"))
    setup_fei_next_type_idx();
  else if (!strcmp(callName, "fei_user_type"))
    setup_fei_user_type();
  else if (!strcmp(callName, "fei_descriptor_size_at_typ_idx"))
    setup_fei_descriptor_size_at_typ_idx();
  else if (!strcmp(callName, "fei_descriptor_size_at_idx"))
    setup_fei_descriptor_size_at_idx();
  else if (!strcmp(callName, "fei_label"))
    setup_fei_label();
  else if (!strcmp(callName, "fei_goto"))
    setup_fei_goto();
  else if (!strcmp(callName, "fei_label_def_named"))
    setup_fei_label_def_named();
  else if (!strcmp(callName, "fei_if"))
    setup_fei_if();
  else if (!strcmp(callName, "fei_else"))
    setup_fei_else();
  else if (!strcmp(callName, "fei_endif"))
    setup_fei_endif();
  else if (!strcmp(callName, "fei_member"))
    setup_fei_member();
  else if (!strcmp(callName, "fei_name"))
    setup_fei_name();
  else if (!strcmp(callName, "fei_member_ref"))
    setup_fei_member_ref();
  else if (!strcmp(callName, "fei_field_dot"))
    setup_fei_field_dot();
  else if (!strcmp(callName, "fei_plus"))
    setup_fei_plus();
  else if (!strcmp(callName, "fei_minus"))
    setup_fei_minus();
    else if (!strcmp(callName, "fei_div"))
    setup_fei_div();
  else if (!strcmp(callName, "fei_mod"))
    setup_fei_mod();
  else if (!strcmp(callName, "fei_lt"))
    setup_fei_lt();
  else if (!strcmp(callName, "fei_eqv"))
    setup_fei_eqv();
  else if (!strcmp(callName, "fei_leqv"))
    setup_fei_leqv();
  else if (!strcmp(callName, "fei_eq"))
    setup_fei_eq();
  else if (!strcmp(callName, "fei_gt"))
    setup_fei_gt();
  else if (!strcmp(callName, "fei_or"))
    setup_fei_or();
  else if (!strcmp(callName, "fei_lor"))
    setup_fei_lor();
  else if (!strcmp(callName, "fei_ge"))
    setup_fei_ge();
  else if (!strcmp(callName, "fei_ne"))
    setup_fei_ne();
  else if (!strcmp(callName, "fei_le"))
    setup_fei_le();
  else if (!strcmp(callName, "fei_xor"))
    setup_fei_xor();
  else if (!strcmp(callName, "fei_lxor"))
    setup_fei_lxor();
  else if (!strcmp(callName, "fei_and"))
    setup_fei_and();
  else if (!strcmp(callName, "fei_land"))
    setup_fei_land();
  else if (!strcmp(callName, "fei_lshift"))
    setup_fei_lshift();
  else if (!strcmp(callName, "fei_rshift"))
    setup_fei_rshift();
  else if (!strcmp(callName, "fei_ashift"))
    setup_fei_ashift();
  else if (!strcmp(callName, "fei_hw_rshift"))
    setup_fei_hw_rshift();
  else if (!strcmp(callName, "fei_hw_lshift"))
    setup_fei_hw_lshift();
  else if (!strcmp(callName, "fei_exponentiate"))
    setup_fei_exponentiate();
  else if (!strcmp(callName, "fei_complex"))
    setup_fei_complex();
  else if (!strcmp(callName, "fei_select"))
    setup_fei_select();
  else if (!strcmp(callName, "fei_mbits"))
    setup_fei_mbits();
/*  else if (!strcmp(callName, "fei_dshiftl"))
    setup_fei_dshiftl();
  else if (!strcmp(callName, "fei_dshiftr"))
    setup_fei_dshiftr();
*/
  else if (!strcmp(callName, "fei_ranf"))
    setup_fei_ranf();
  else if (!strcmp(callName, "fei_ranget"))
    setup_fei_ranget();
  else if (!strcmp(callName, "fei_ranset"))
    setup_fei_ranset();
  else if (!strcmp(callName, "fei_static_base"))
    setup_fei_static_base();
  else if (!strcmp(callName, "fei_static_simple_init"))
    setup_fei_static_simple_init();
  else if (!strcmp(callName, "fei_arg_addr"))
    setup_fei_arg_addr();
  else if (!strcmp(callName, "fei_return"))
    setup_fei_return();
  else if (!strcmp(callName, "fei_doloop"))
    setup_fei_doloop();
  else if (!strcmp(callName, "fei_dowhile"))
    setup_fei_dowhile();
  else if (!strcmp(callName, "fei_enddo"))
    setup_fei_enddo();
  else if (!strcmp(callName, "fei_doforever"))
    setup_fei_doforever();
  else if (!strcmp(callName, "fei_array_dimen"))
    setup_fei_array_dimen();
  else if (!strcmp(callName, "fei_subscr_triplet"))
    setup_fei_subscr_triplet();
  else if (!strcmp(callName, "fei_subscr_size"))
    setup_fei_subscr_size();
  else if (!strcmp(callName, "fei_seq_subscr"))
    setup_fei_seq_subscr();
  else if (!strcmp(callName, "fei_substr"))
    setup_fei_substr();
  else if (!strcmp(callName, "fei_paren"))
    setup_fei_paren();
  else if (!strcmp(callName, "fei_backspace"))
    setup_fei_backspace();
  else if (!strcmp(callName, "fei_close"))
    setup_fei_close();
  else if (!strcmp(callName, "fei_endfile"))
    setup_fei_endfile();
  else if (!strcmp(callName, "fei_inquire"))
    setup_fei_inquire();
  else if (!strcmp(callName, "fei_open"))
    setup_fei_open();
  else if (!strcmp(callName, "fei_rewind"))
    setup_fei_rewind();
  else if (!strcmp(callName, "fei_malloc"))
    setup_fei_malloc();
  else if (!strcmp(callName, "fei_mfree"))
    setup_fei_mfree();
  else if (!strcmp(callName, "fei_addr"))
    setup_fei_addr();
  else if (!strcmp(callName, "fei_cvtop"))
    setup_fei_cvtop();
  else if (!strcmp(callName, "fei_formatted_read"))
    setup_formatted_read();
  else if (!strcmp(callName, "fei_unformatted_read"))
    setup_unformatted_read();
  else if (!strcmp(callName, "fei_namelist"))
    setup_fei_namelist();
  else if (!strcmp(callName, "fei_static_substr"))
    setup_fei_static_substr();
  else if (!strcmp(callName, "fei_namelist_write"))
    setup_fei_namelist_write();
  else if (!strcmp(callName, "fei_namelist_read"))
    setup_fei_namelist_read();
  else if (!strcmp(callName, "fei_static_subscripts"))
    setup_fei_static_subscripts();
  else if (!strcmp(callName, "fei_namelist_ref"))
    setup_fei_namelist_ref();
  else if (!strcmp(callName, "fei_label_ref"))
    setup_fei_label_ref();
  else if (!strcmp(callName, "fei_arith_goto"))
    setup_fei_arith_goto();
  else if (!strcmp(callName, "fei_push_pattern_con"))
    setup_fei_push_pattern_con();
  else if (!strcmp(callName, "fei_mult"))
    setup_fei_mult();
  else if (!strcmp(callName, "fei_indirect_goto"))
    setup_fei_indirect_goto();
  else if (!strcmp(callName, "fei_label_addr"))
    setup_fei_label_addr();
  else if (!strcmp(callName, "fei_lneg"))
    setup_fei_lneg();
  else if (!strcmp(callName, "fei_uminus"))
    setup_fei_uminus();
  else if (!strcmp(callName, "fei_abs"))
    setup_fei_abs();
  else if (!strcmp(callName, "fei_max"))
    setup_fei_max();
  else if (!strcmp(callName, "fei_sqrt"))
    setup_fei_sqrt();
  else if (!strcmp(callName, "fei_exp"))
    setup_fei_exp();
  else if (!strcmp(callName, "fei_addr_con"))
    setup_fei_addr_con();
  else if (!strcmp(callName, "fei_trunc"))
    setup_fei_trunc();
  else if (!strcmp(callName, "fei_min"))
    setup_fei_min();
  else if (!strcmp(callName, "fei_log"))
    setup_fei_log();
  else if (!strcmp(callName, "fei_log10"))
    setup_fei_log10();
  else if (!strcmp(callName, "fei_sign_xfer"))
    setup_fei_sign_xfer();
  else if (!strcmp(callName, "fei_pos_diff"))
    setup_fei_pos_diff();
  else if (!strcmp(callName, "fei_sin"))
    setup_fei_sin();
  else if (!strcmp(callName, "fei_sinh"))
    setup_fei_sinh();
  else if (!strcmp(callName, "fei_tan"))
    setup_fei_tan();
  else if (!strcmp(callName, "fei_tanh"))
    setup_fei_tanh();
  else if (!strcmp(callName, "fei_atan"))
    setup_fei_atan();
  else if (!strcmp(callName, "fei_atan2"))
    setup_fei_atan2();
  else if (!strcmp(callName, "fei_atand"))
    setup_fei_atand();
  else if (!strcmp(callName, "fei_brtrue"))
    setup_fei_brtrue();
  else if (!strcmp(callName, "fei_implied_do"))
    setup_fei_implied_do();
  else if (!strcmp(callName, "fei_round"))
    setup_fei_round();
  else if (!strcmp(callName, "fei_asin"))
    setup_fei_asin();
  else if (!strcmp(callName, "fei_cosh"))
    setup_fei_cosh();
  else if (!strcmp(callName, "fei_acos"))
    setup_fei_acos();
  else if (!strcmp(callName, "fei_unformatted_write"))
    setup_fei_unformatted_write();
  else if (!strcmp(callName, "fei_imag"))
    setup_fei_imag();
  else if (!strcmp(callName, "fei_concat"))
    setup_fei_concat();
  else if (!strcmp(callName, "fei_len"))
    setup_fei_len();
  else if (!strcmp(callName, "fei_entry_pt"))
    setup_fei_entry_pt();
  else if (!strcmp(callName, "fei_conjg"))
    setup_fei_conjg();
  else if (!strcmp(callName, "fei_len_trim"))
    setup_fei_len_trim();
  else if (!strcmp(callName, "fei_dope_vector"))
    setup_fei_dope_vector();
  else if (!strcmp(callName, "fei_dv_def"))
    setup_fei_dv_def();
  else if (!strcmp(callName, "fei_dv_deref"))
    setup_fei_dv_deref();
  else if (!strcmp(callName, "fei_set_dv_hdr_fld"))
    setup_fei_set_dv_hdr_fld();
  else if (!strcmp(callName, "fei_get_dv_hdr_fld"))
    setup_fei_get_dv_hdr_fld();
  else if (!strcmp(callName, "fei_mask"))
    setup_fei_mask();
  else if (!strcmp(callName, "fei_cot"))
    setup_fei_cot();
  else if (!strcmp(callName, "fei_static_simple_reloc_init"))
    setup_fei_static_simple_reloc_init();
  else if (!strcmp(callName, "fei_set_dv_str_mult"))
    setup_fei_set_dv_str_mult();
  else if (!strcmp(callName, "fei_set_dv_extent"))
    setup_fei_set_dv_extent();
  else if (!strcmp(callName, "fei_set_dv_low_bnd"))
    setup_fei_set_dv_low_bnd();
  else if (!strcmp(callName, "fei_new_select"))
    setup_fei_new_select();
  else if (!strcmp(callName, "fei_all"))
    setup_fei_all();
  else if (!strcmp(callName, "fei_matmul"))
    setup_fei_matmul();
  else if (!strcmp(callName, "fei_spread"))
    setup_fei_spread();
  else if (!strcmp(callName, "fei_reshape"))
    setup_fei_reshape();
  else if (!strcmp(callName, "fei_transpose"))
    setup_fei_transpose();
  else if (!strcmp(callName, "fei_sum"))
    setup_fei_sum();
  else if (!strcmp(callName, "fei_eoshift"))
    setup_fei_eoshift();
  else if (!strcmp(callName, "fei_maxval"))
    setup_fei_maxval();
  else if (!strcmp(callName, "fei_minval"))
    setup_fei_minval();
  else if (!strcmp(callName, "fei__maxloc"))
    setup_fei__maxloc();
  else if (!strcmp(callName, "fei__minloc"))
    setup_fei__minloc();
  else if (!strcmp(callName, "fei_any"))
    setup_fei_any();
  else if (!strcmp(callName, "fei_count"))
    setup_fei_count();
  else if (!strcmp(callName, "fei_product"))
    setup_fei_product();
  else if (!strcmp(callName, "fei_cshift"))
    setup_fei_cshift();
  else if (!strcmp(callName, "fei_dot_product"))
    setup_fei_dot_product();
  else if (!strcmp(callName, "fei_dot_product_logical"))
    setup_fei_dot_product_logical();
  else if (!strcmp(callName, "fei_index"))
    setup_fei_index();
  else if (!strcmp(callName, "fei_adjustl"))
    setup_fei_adjustl();
  else if (!strcmp(callName, "fei_alloc"))
    setup_fei_alloc();
  else if (!strcmp(callName, "fei_free"))
    setup_fei_free();
  else if (!strcmp(callName, "fei_allocate"))
    setup_fei_allocate();
  else if (!strcmp(callName, "fei_get_dv_str_mult"))
    setup_fei_get_dv_str_mult();
  else if (!strcmp(callName, "fei_get_dv_extent"))
    setup_fei_get_dv_extent();
  else if (!strcmp(callName, "fei_get_dv_low_bnd"))
    setup_fei_get_dv_low_bnd();
  else if (!strcmp(callName, "fei_nseq_subscr"))
    setup_fei_nseq_subscr();
  else if (!strcmp(callName, "fei_dv_ptr_asg"))
    setup_fei_dv_ptr_asg();
  else if (!strcmp(callName, "fei_present"))
    setup_fei_present();
  else if (!strcmp(callName, "PDGCS_debug_init"))
    setup_PDGCS_debug_init();
  else if (!strcmp(callName, "fei_smt_actual_to_generic"))
    setup_fei_smt_actual_to_generic();
  else if (!strcmp(callName, "fei_smt_parameter"))
    setup_fei_smt_parameter();
  else if (!strcmp(callName, "fei_where"))
    setup_fei_where();
  else if (!strcmp(callName, "fei_new_select_case"))
    setup_fei_new_select_case();
  else if (!strcmp(callName, "fei_as_ref"))
    setup_fei_as_ref();
  else if (!strcmp(callName, "fei_add_use_path"))
    setup_fei_add_use_path();
  else if (!strcmp(callName, "fei_static_member"))
    setup_fei_static_member();
  else if (!strcmp(callName, "fei_fcd"))
    setup_fei_fcd();
  else if (!strcmp(callName, "fei_verify"))
    setup_fei_verify();
  else if (!strcmp(callName, "fei_scan"))
    setup_fei_scan();
  else if (!strcmp(callName, "fei_bneg"))
    setup_fei_bneg();
  else if (!strcmp(callName, "fei_adjustr"))
    setup_fei_adjustr();
  else if (!strcmp(callName, "fei_pattern_con"))
    setup_fei_pattern_con();
  else if (!strcmp(callName, "fei_iolength"))
    setup_fei_iolength();
  else if (!strcmp(callName, "fei_non_conform_store"))
    setup_fei_non_conform_store();
  else if (!strcmp(callName, "fei_ceiling"))
    setup_fei_ceiling();
  else if (!strcmp(callName, "fei_floor"))
    setup_fei_floor();
  else if (!strcmp(callName, "fei_exponent"))
    setup_fei_exponent();
  else if (!strcmp(callName, "fei_modulo"))
    setup_fei_modulo();
  else if (!strcmp(callName, "fei_near"))
    setup_fei_near();
  else if (!strcmp(callName, "fei_rrspace"))
    setup_fei_rrspace();
  else if (!strcmp(callName, "fei_space"))
    setup_fei_space();
  else if (!strcmp(callName, "fei_scale"))
    setup_fei_scale();
  else if (!strcmp(callName, "fei_fraction"))
    setup_fei_fraction();
  else if (!strcmp(callName, "fei_set_exponent"))
    setup_fei_set_exponent();
  else if (!strcmp(callName, "fei_popcnt"))
    setup_fei_popcnt();
  else if (!strcmp(callName, "fei_poppar"))
    setup_fei_poppar();
  else if (!strcmp(callName, "fei_leadz"))
    setup_fei_leadz();
  else if (!strcmp(callName, "fei_ishftc"))
    setup_fei_ishftc();
  else if (!strcmp(callName, "fei_ibits"))
    setup_fei_ibits();
  else if (!strcmp(callName, "fei_pack"))
    setup_fei_pack();
  else if (!strcmp(callName, "fei_unpack"))
    setup_fei_unpack();
  else if (!strcmp(callName, "fei_copyin_bound"))
    setup_fei_copyin_bound();
  else if (!strcmp(callName, "fei_new_binop_cshift"))
    setup_fei_new_binop_cshift();
  else if (!strcmp(callName, "fei_static_next_simple_init"))
    setup_fei_static_next_simple_init();
  else if (!strcmp(callName, "GLOBAL_LINE_TBL"))
    read_global_line_table();
  else if (!strcmp(callName, "fei_task_var"))
    setup_fei_task_var();
  else if (!strcmp(callName, "fei_parallel_open_mp"))
    setup_fei_parallel_open_mp();
  else if (!strcmp(callName, "fei_endparallel_open_mp"))
    setup_fei_endparallel_open_mp();
  else if (!strcmp(callName, "fei_single_open_mp"))
    setup_fei_single_open_mp();
  else if (!strcmp(callName, "fei_endsingle_open_mp"))
    setup_fei_endsingle_open_mp();
  else if (!strcmp(callName, "fei_do_open_mp"))
    setup_fei_do_open_mp();
  else if (!strcmp(callName, "fei_enddo_open_mp"))
    setup_fei_enddo_open_mp();
  else if (!strcmp(callName, "fei_critical_open_mp"))
    setup_fei_critical_open_mp();
  else if (!strcmp(callName, "fei_endcritical_open_mp"))
    setup_fei_endcritical_open_mp();
  else if (!strcmp(callName, "fei_ordered_open_mp"))
    setup_fei_ordered_open_mp();
  else if (!strcmp(callName, "fei_endordered_open_mp"))
    setup_fei_endordered_open_mp();
  else if (!strcmp(callName, "fei_flush_open_mp"))
    setup_fei_flush_open_mp();
  else if (!strcmp(callName, "fei_atomic_open_mp"))
    setup_fei_atomic_open_mp();
  else if (!strcmp(callName, "fei_barrier_open_mp"))
    setup_fei_barrier_open_mp();
  else if (!strcmp(callName, "fei_section_open_mp"))
    setup_fei_section_open_mp();
  else if (!strcmp(callName, "fei_sections_open_mp"))
    setup_fei_sections_open_mp();
  else if (!strcmp(callName, "fei_endsections_open_mp"))
    setup_fei_endsections_open_mp();
  else if (!strcmp(callName, "fei_paralleldo_open_mp"))
    setup_fei_paralleldo_open_mp();
  else if (!strcmp(callName, "fei_endparalleldo_open_mp"))
    setup_fei_endparalleldo_open_mp();
  else if (!strcmp(callName, "fei_master_open_mp"))
    setup_fei_master_open_mp();
  else if (!strcmp(callName, "fei_endmaster_open_mp"))
    setup_fei_endmaster_open_mp();
  else if (!strcmp(callName, "fei_workshare_open_mp"))
    setup_fei_workshare_open_mp();
  else if (!strcmp(callName, "fei_endworkshare_open_mp"))
    setup_fei_endworkshare_open_mp();
  else if (!strcmp(callName, "fei_parallelsections_open_mp"))
    setup_fei_parallelsections_open_mp();
  else if (!strcmp(callName, "fei_endparallelsections_open_mp"))
    setup_fei_endparallelsections_open_mp();
  else if (!strcmp(callName, "fei_parallelworkshare_open_mp"))
    setup_fei_parallelworkshare_open_mp();
  else if (!strcmp(callName, "fei_endparallelworkshare_open_mp"))
    setup_fei_endparallelworkshare_open_mp();

  else {
    char temp[MAX_LINE_LEN];
    sprintf(temp, "Unrecognized call: %s", callName);
    printError(temp);
  }
  return 1;
}

int checkLabel(char *label, char *inLabel)
{
  if(strcmp(label, inLabel)) {
    char temp[1024];
    sprintf(temp, "Looking for %s, found %s, ", label, inLabel);
    printError(temp);
  }
  return 1;
}


int setCallName(char *out)
{
  int i;

  lineNo++;

  if(!fgets(inLine, MAX_LINE_LEN, infile))
    return 0;

  if(START_COL == -1) {
    if(inLine[0] == '(')
      START_COL = 11;
    else
      START_COL = 4;
  }

  if(strncmp(&inLine[START_COL-4], "--->", 4))
    printError("call expected");
    
  i = START_COL;
  while(inLine[++i] == ' ');
  for(; i < strlen(inLine); i++)
    if(inLine[i] == ' ' || inLine[i] == '\t') {
      inLine[i] = '\0';
      break;
    }
  strcpy(out, &inLine[START_COL]);
  trim(out);
  return 1;
}

void read_global_line_table()
{

  int i, found, idx;
  long length, lengthp;

  long global_line;  
  long file_line;
  char file_name[1024];
  long file_name_idx;
  long cif_file_id;
  long file_name_len;
  long incld_file_line;
  long incld_file_col;
  char path_name[1024];
  long path_name_idx;
  long path_name_len;
  long source_lines;
  
  long num_global_lines;
  static int last_global_line_idx = 0;
  

  setLongVar("num_global_lines", &num_global_lines);
  TBL_REALLOC_CK (global_line_tbl, num_global_lines);
  
  for (i = last_global_line_idx + 1;
       i <= num_global_lines + last_global_line_idx;
       i++) {
   
    curr_glb_line = i;
    setLongVar("global_line", &global_line);
    setLongVar("file_line", &file_line);
    setStrVar("file_name", file_name);
    trim(file_name);
    setLongVar("file_name_idx", &file_name_idx);
    setLongVar("cif_file_id", &cif_file_id);
    setLongVar("file_name_len", &file_name_len);
    setLongVar("incld_file_line", &incld_file_line);
    setLongVar("incld_file_col", &incld_file_col);
    setStrVar("path_name", path_name);
    trim(path_name);
    setLongVar("path_name_idx", &path_name_idx);
    setLongVar("path_name_len", &path_name_len);
    setLongVar("source_lines", &source_lines);


    global_line_tbl[i].global_line = global_line;
    global_line_tbl[i].file_line = file_line;
    global_line_tbl[i].cif_file_id = cif_file_id;

    /* Clear the field.  It gets set at EOF of each file. */
    /* It also holds a running total of file lines at each end statement */
    /* because of mif inflexibility.                                     */

    global_line_tbl[i].source_lines = source_lines;
    global_line_tbl[i].incld_file_line = incld_file_line;
    global_line_tbl[i].incld_file_col = incld_file_col;


    /* prevent duplication of file name strings in string pool */

    global_line_tbl[i].file_name_idx = 0;
    global_line_tbl[i].path_name_idx = 0;
    length = file_name_len;
    lengthp = path_name_len;

    /* check for file name already in the string pool */

    if (global_line_tbl[i].file_name_idx == 0) {
       global_line_tbl[i].file_name_len	= length;
       global_line_tbl[i].file_name_idx = str_pool_idx+1;
       TBL_REALLOC_CK(str_pool, WORD_LEN(length));

       for (idx = global_line_tbl[i].file_name_idx;
            idx <= str_pool_idx; idx++) {
           str_pool[idx].name_long = 0;
       }

       strcpy(&str_pool[global_line_tbl[i].file_name_idx].name_char,
              file_name);
    }

    if (global_line_tbl[i].path_name_idx == 0) {
       global_line_tbl[i].path_name_len	= lengthp;
       global_line_tbl[i].path_name_idx	= str_pool_idx+1;
       TBL_REALLOC_CK(str_pool, WORD_LEN(lengthp));

       for (idx = global_line_tbl[i].path_name_idx;
            idx <= str_pool_idx; idx++) {
           str_pool[idx].name_long = 0;
       }

       strcpy(&str_pool[global_line_tbl[i].path_name_idx].name_char,
              path_name);
    }
  }

  last_global_line_idx += num_global_lines;

}

