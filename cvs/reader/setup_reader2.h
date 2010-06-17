
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

#ifndef SETUP_READER2_H
#define SETUP_READER2_H

void setup_fei_next_name();
void setup_fei_next_type_idx();
void setup_fei_cos();
void setup_fei_user_type();
void setup_fei_member();
void setup_fei_name();
void setup_fei_member_ref();
void setup_fei_field_dot();
void setup_fei_plus();
void setup_fei_minus();
void setup_fei_len_trim();

void setup_fei_div();
void setup_fei_mod();
void setup_fei_lt();
void setup_fei_eqv();
void setup_fei_leqv();
void setup_fei_eq();
void setup_fei_qt();
void setup_fei_or();
void setup_fei_lor();
void setup_fei_ge();
void setup_fei_ne();
void setup_fei_le();
void setup_fei_xor();
void setup_fei_lxor();
void setup_fei_and();
void setup_fei_land();
void setup_fei_lshift();
void setup_fei_rshift();
void setup_fei_ashift();
void setup_fei_hw_rshift();
void setup_fei_hw_lshift();
void setup_fei_exponentiate();
void setup_fei_complex();
void setup_fei_select();
void setup_fei_mbits();
/*
void setup_fei_dshiftl();
void setup_fei_dshiftr();
*/
void setup_fei_ranf();
void setup_fei_ranget();
void setup_fei_ranset();
void setup_fei_arith_goto();
void setup_fei_push_pattern_con();
void setup_fei_mult();
void setup_fei_indirect_goto();
void setup_fei_label_addr();
void setup_fei_lneg();
void setup_fei_uminus();
void setup_fei_abs();
void setup_fei_max();
void setup_fei_sqrt();
void setup_fei_exp();
void setup_fei_addr_con();
void setup_fei_trunc();
void setup_fei_min();
void setup_fei_log();
void setup_fei_log10();
void setup_fei_sign_xfer();
void setup_fei_pos_diff();
void setup_fei_sin();
void setup_fei_sinh();
void setup_fei_tan();
void setup_fei_tanh();
void setup_fei_atan();
void setup_fei_atan2();
void setup_fei_atand();
void setup_fei_round();
void setup_fei_asin();
void setup_fei_cosh();
void setup_fei_acos();
void setup_fei_imag();
void setup_fei_len();
void setup_fei_entry_pt();
void setup_fei_conjg();
void setup_fei_cot();
void setup_fei_all();
void setup_fei_matmul();
void setup_fei_spread();
void setup_fei_reshape();
void setup_fei_transpose();
void setup_fei_sum();
void setup_fei_eoshift();
void setup_fei_maxval();
void setup_fei_minval();
void setup_fei__maxloc();
void setup_fei__minloc();
void setup_fei_any();
void setup_fei_count();
void setup_fei_product();
void setup_fei_cshift();
void setup_fei_dot_product();
void setup_fei_dot_product_logical();
void setup_fei_adjustl();
void setup_fei_verify();
void setup_fei_scan();
void setup_fei_adjustr();
void setup_fei_iolength();
void setup_fei_non_conform_store();
void setup_fei_bneg();
void setup_fei_ceiling();
void setup_fei_exponent();
void setup_fei_floor();
void setup_fei_modulo();
void setup_fei_near();
void setup_fei_rrspace();
void setup_fei_space();
void setup_fei_scale();
void setup_fei_fraction();
void setup_fei_set_exponent();
void setup_fei_popcnt();
void setup_fei_poppar();
void setup_fei_leadz();
void setup_fei_ishftc();
void setup_fei_ibits();
void setup_fei_pack();
void setup_fei_unpack();
void setup_fei_copyin_bound();
void setup_fei_new_binop_cshift();

void setup_fei_task_var();
void setup_fei_parallel_open_mp();
void setup_fei_endparallel_open_mp();
void setup_fei_single_open_mp();
void setup_fei_endsingle_open_mp();
void setup_fei_enddo_open_mp();
void setup_fei_critical_open_mp();
void setup_fei_endcritical_open_mp();
void setup_fei_do_open_mp();
void setup_fei_ordered_open_mp();
void setup_fei_endordered_open_mp();
void setup_fei_flush_open_mp();
void setup_fei_atomic_open_mp();
void setup_fei_barrier_open_mp();
void setup_fei_section_open_mp();
void setup_fei_sections_open_mp();
void setup_fei_endsections_open_mp();
void setup_fei_paralleldo_open_mp();
void setup_fei_endparalleldo_open_mp();
void setup_fei_master_open_mp();
void setup_fei_endmaster_open_mp();
void setup_fei_workshare_open_mp();
void setup_fei_endworkshare_open_mp();
void setup_fei_parallelsections_open_mp();
void setup_fei_endparallelsections_open_mp();
void setup_fei_parallelworkshare_open_mp();
void setup_fei_endparallelworkshare_open_mp();

#endif
