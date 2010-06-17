
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

static INT32 last_task_idx = 0;
static INT32 first_task_idx = 0;

void setup_fei_parallelworkshare_open_mp()
{
  INT32 task_if_idx;
  INT32 defaultt;
  INT32 num_threads_idx;


  setIntVar("if_idx", &task_if_idx);
  setIntVar("num_threads_idx", &num_threads_idx);
  setIntVar("defaultt", &defaultt);

  fei_parallelworkshare_open_mp(PDG_AT_IDX(task_if_idx), PDG_AT_IDX(num_threads_idx), defaultt);
}

void setup_fei_endparallelworkshare_open_mp()
{
  fei_endparallelworkshare_open_mp();
}

void setup_fei_parallelsections_open_mp()
{
  INT32 task_if_idx;
  INT32 defaultt;
  INT32 num_threads_idx;


  setIntVar("if_idx", &task_if_idx);
  setIntVar("num_threads_idx", &num_threads_idx);
  setIntVar("defaultt", &defaultt);

  fei_parallelsections_open_mp(PDG_AT_IDX(task_if_idx), PDG_AT_IDX(num_threads_idx), defaultt);

}

void setup_fei_endparallelsections_open_mp()
{
  fei_endparallelsections_open_mp();
}

void setup_fei_workshare_open_mp()
{
  fei_workshare_open_mp();
}

void setup_fei_endworkshare_open_mp()
{
  INT32 nowait;

  setIntVar("nowait", &nowait);

  fei_endworkshare_open_mp(nowait);
}

void setup_fei_master_open_mp()
{
  fei_master_open_mp();
}

void setup_fei_endmaster_open_mp()
{
  fei_endmaster_open_mp();
}

void setup_fei_paralleldo_open_mp()
{
  INT32 ordered;
  INT32 scheduletype;
  INT32 schedulechunk;
  INT32 threadcount;
  INT32 datacount;
  INT32 ontocount;
  INT32 task_if_idx;
  INT32 defaultt;
  INT32 num_threads_idx;


  setIntVar("if_idx", &task_if_idx);
  setIntVar("num_threads_idx", &num_threads_idx);
  setIntVar("defaultt", &defaultt);
  setIntVar("ordered", &ordered);
  setIntVar("scheduletype", &scheduletype);
  setIntVar("schedulechunk", &schedulechunk);
  setIntVar("threadcount", &threadcount);
  setIntVar("datacount", &datacount);
  setIntVar("ontocount", &ontocount);

           fei_paralleldo_open_mp(PDG_AT_IDX(task_if_idx), PDG_AT_IDX(num_threads_idx), defaultt, ordered,
                          scheduletype,
                          PDG_AT_IDX(schedulechunk),
			  threadcount,
                          datacount,
                          ontocount);
}

void setup_fei_endparalleldo_open_mp()
{
  fei_endparalleldo_open_mp();
}

void setup_fei_endsections_open_mp()
{
  INT32 nowait;

  setIntVar("nowait", &nowait);

  fei_endsections_open_mp(nowait);
}

void setup_fei_sections_open_mp()
{
  fei_sections_open_mp();
}

void setup_fei_section_open_mp()
{
  fei_section_open_mp();
}

void setup_fei_barrier_open_mp()
{
  fei_barrier_open_mp();
}

void setup_fei_atomic_open_mp()
{
  fei_atomic_open_mp();
}

void setup_fei_flush_open_mp()
{
  INT32 list_cnt;

  setIntVar("list_cnt", &list_cnt);

  fei_flush_open_mp(list_cnt);
}

void setup_fei_ordered_open_mp()
{
  fei_ordered_open_mp();
}

void setup_fei_endordered_open_mp()
{
  fei_endordered_open_mp();
}

void setup_fei_do_open_mp()
{
  INT32 ordered;
  INT32 scheduletype;
  INT32 schedulechunk;
  INT32 threadcount;
  INT32 datacount;
  INT32 ontocount;


  setIntVar("ordered", &ordered);
  setIntVar("scheduletype", &scheduletype);
  setIntVar("schedulechunk", &schedulechunk);
  setIntVar("threadcount", &threadcount);
  setIntVar("datacount", &datacount);
  setIntVar("ontocount", &ontocount);

           fei_do_open_mp(ordered,
                          scheduletype,
                          PDG_AT_IDX(schedulechunk),
			  threadcount,
                          datacount,
                          ontocount);
}

void setup_fei_endcritical_open_mp()
{
  char name[1024];

  setStrVar("criticalname", &name);

  if(!strcmp(name, ""))
    fei_endcritical_open_mp(NULL);
  else
    fei_endcritical_open_mp(name);
}

void setup_fei_critical_open_mp()
{
  char name[1024];

  setStrVar("criticalname", &name);

  if(!strcmp(name, ""))
    fei_critical_open_mp(NULL);
  else
    fei_critical_open_mp(name);
}

void setup_fei_enddo_open_mp()
{
  INT32 nowait;

  setIntVar("nowait", &nowait);

  fei_enddo_open_mp(nowait);
}

void setup_fei_endsingle_open_mp()
{
  INT32 nowait;

  setIntVar("nowait", &nowait);

  fei_endsingle_open_mp(nowait);
}

void setup_fei_single_open_mp()
{
  fei_single_open_mp();
}

void setup_fei_parallel_open_mp()
{
  INT32 task_if_idx;
  INT32 defaultt;
  INT32 num_threads_idx;


  setIntVar("if_idx", &task_if_idx);
  setIntVar("num_threads_idx", &num_threads_idx);
  setIntVar("defaultt", &defaultt);

  fei_parallel_open_mp(PDG_AT_IDX(task_if_idx), PDG_AT_IDX(num_threads_idx), defaultt);

}

void setup_fei_endparallel_open_mp()
{
  fei_endparallel_open_mp();
}

void setup_fei_task_var()
{
  INT32 idx;
  INT32 context;

  setIntVar("PDG_AT_IDX", &idx);
  setIntVar("context", &context);

  last_task_idx = fei_task_var(PDG_AT_IDX(idx), context);

  if (first_task_idx == 0) {
    first_task_idx = last_task_idx;
  }
}

void setup_fei_next_name()
{
  INT32 ret;
  INTPTR ID;
  INT32 increment;
  

  setLongVar("AT ID", &ID);
  setIntVar("logical", &increment);

  ret = fei_next_name                ( increment );


  addPdgLink(AT, ID, ret);
}


void setup_fei_cos()
{
  INTPTR type;

  setLongVar("type", &type);

  fei_cos(PDG_AT_TYP_IDX(type));
}

void setup_fei_next_type_idx()
{
  INT32 ret;

  INTPTR ID;
  INT32 flag;
  INT32 alignment;

  setLongVar("AT TYP INTERNAL ID", &ID);
  setIntFlagsVar("flags", &flag);
  setIntVar("alignment", &alignment);

  ret = fei_next_type_idx(flag,
				alignment);

  addPdgTypeInternalLink(AT_TYP, ID, ret);
}


void setup_fei_user_type()
{
  char name_string[1024];
  INT32 nbr_components;
  INT32 first_idx;
  INT64 size;
  INT32 sequence;
  INT32 st_idx;
  INT32 alignment;

  setStrVar("AT_OBJ_NAME", name_string);
  setIntVar("ATT_NUM_CPNTS", &nbr_components);
  setIntVar("cpnt idx", &first_idx);
  setLongLongVar("struct size", &size);
  setEnumVar("sequence", &sequence);
  setIntVar("dt_idx", &st_idx);
  setIntVar("alignment", &alignment);

  fei_user_type(name_string,
			nbr_components,
			PDG_AT_IDX(first_idx),
			size,
			sequence,
			PDG_AT_TYP_INTERNAL_IDX(st_idx),
			alignment);
}


void setup_fei_member()
{
  INTPTR ret;
  INTPTR ID;
  
  char name_string[1024];
  INTPTR type;
  INT64 offset;
  INT64 size;
  INT32 alignment;
  INT32 line_num;
  INT64 flag_bits;
  INT64 io_code;
  

  setLongVar("AT_ID", &ID);
  setStrVar("AT_OBJ_NAME", name_string);
  setLongVar("type", &type);
  setLongLongVar("offset", &offset);
  setLongLongVar("bit_len",&size);
  setIntVar("storage align", &alignment);
  setIntVar("AT_DEF_LINE", &line_num);
  setLongLongFlagsVar("flags", &flag_bits);
  setLongLongVar("io descriptor", &io_code);
  
  ret = fei_member          ( name_string,
                            PDG_AT_TYP_IDX(type),
                            offset,
                            size,
                            alignment,
                            line_num, 
			    flag_bits,
                            io_code );

  addPdgLink(AT, ID, ret);
}

void setup_fei_name()
{
  INTPTR ret;
  INTPTR ID;
  
  char name_string[1024];
  INT32 st_grp;
  INTPTR st_idx;
  INT32 prev;
  INT32 idx;
  
  setLongVar("AT ID", &ID);
  setStrVar("AT_OBJ_NAME", name_string);
  setEnumVar("table", &st_grp);
  setLongVar("PDG_AT_IDX", &st_idx);
  setIntVar("prev_idx", &prev);
  if(st_grp == Sym_Member)
    setIntVar("cpnt_idx", &idx);
  else
    setIntVar("darg_idx", &idx);
 
  ret = fei_name                    ( name_string,
                                    st_grp,
                                    PDG_AT_IDX(st_idx),
                                    PDG_AT_IDX(prev),
                                    PDG_AT_IDX(idx));

  addPdgLink(AT, ID, ret);
}


void setup_fei_member_ref()
{
  INT32 mem_idx;
  
  ignoreVar("AT_OBJ_NAME"); 
  setIntVar("PDG_AT_IDX", &mem_idx);
  
  fei_member_ref               (PDG_AT_IDX(mem_idx));
}


void setup_fei_field_dot()
{
  fei_field_dot                ( null_type );
}

void setup_fei_plus()
{
  INTPTR idx;
  
  setLongVar("PDG_AT_TYP_IDX", &idx);
  
  fei_plus(PDG_AT_TYP_IDX(idx));
}

void setup_fei_minus()
{
  INTPTR idx;
  
  setLongVar("PDG_AT_TYP_IDX", &idx);
  
  fei_minus(PDG_AT_TYP_IDX(idx));
}


/*
extern void  fei_div             	  ( TYPE type );
extern void  fei_mod             	  ( TYPE type );
extern void  fei_lt              	  ( TYPE type );
extern void  fei_eqv             	  ( TYPE type );
extern void  fei_leqv            	  ( TYPE type );
extern void  fei_eq              	  ( TYPE type );
extern void  fei_gt              	  ( TYPE type );
extern void  fei_or              	  ( TYPE type );
extern void  fei_lor             	  ( TYPE type );
extern void  fei_ge              	  ( TYPE type );
extern void  fei_ne              	  ( TYPE type );
extern void  fei_le              	  ( TYPE type );
extern void  fei_xor             	  ( TYPE type );
extern void  fei_lxor            	  ( TYPE type );
extern void  fei_and             	  ( TYPE type );
extern void  fei_land            	  ( TYPE type );
extern void  fei_lshift          	  ( TYPE type );
extern void  fei_rshift          	  ( TYPE type );
extern void  fei_ashift            	  ( TYPE type );
extern void  fei_hw_rshift       	  ( TYPE type );
extern void  fei_hw_lshift       	  ( TYPE type );
extern void  fei_exponentiate    	  ( TYPE type );
extern void  fei_complex         	  ( TYPE type );
extern void  fei_select          	  ( TYPE type );
extern void  fei_mbits           	  ( TYPE type );
extern void  fei_dshiftl         	  ( TYPE type );
extern void  fei_dshiftr         	  ( TYPE type );
extern void  fei_ranf            	  ( TYPE type );
extern void  fei_ranget          	  ( TYPE type );
extern void  fei_ranset          	  ( TYPE type );
*/

void setup_fei_div()
{
  INTPTR idx;
  
  setLongVar("PDG_AT_TYP_IDX", &idx);
  
  fei_div(PDG_AT_TYP_IDX(idx));
}

void setup_fei_mod()
{
  INTPTR idx;
  
  setLongVar("PDG_AT_TYP_IDX", &idx);
  
  fei_mod(PDG_AT_TYP_IDX(idx));
}

void setup_fei_lt()
{
  INTPTR idx;
  
  setLongVar("PDG_AT_TYP_IDX", &idx);
  
  fei_lt(PDG_AT_TYP_IDX(idx));
}

void setup_fei_eqv()
{
  INTPTR idx;
  
  setLongVar("PDG_AT_TYP_IDX", &idx);
  
  fei_eqv(PDG_AT_TYP_IDX(idx));
}

void setup_fei_leqv()
{
  INTPTR idx;
  
  setLongVar("PDG_AT_TYP_IDX", &idx);
  
  fei_leqv(PDG_AT_TYP_IDX(idx));
}

void setup_fei_eq()
{
  INTPTR idx;
  
  setLongVar("PDG_AT_TYP_IDX", &idx);
  
  fei_eq(PDG_AT_TYP_IDX(idx));
}

void setup_fei_gt()
{
  INTPTR idx;
  
  setLongVar("PDG_AT_TYP_IDX", &idx);
  
  fei_gt(PDG_AT_TYP_IDX(idx));
}

void setup_fei_or()
{
  INTPTR idx;
  
  setLongVar("PDG_AT_TYP_IDX", &idx);
  
  fei_or(PDG_AT_TYP_IDX(idx));
}

void setup_fei_lor()
{
  INTPTR idx;
  
  setLongVar("PDG_AT_TYP_IDX", &idx);
  
  fei_lor(PDG_AT_TYP_IDX(idx));
}

void setup_fei_ge()
{
  INTPTR idx;
  
  setLongVar("PDG_AT_TYP_IDX", &idx);
  
  fei_ge(PDG_AT_TYP_IDX(idx));
}

void setup_fei_ne()
{
  INTPTR idx;
  
  setLongVar("PDG_AT_TYP_IDX", &idx);
  
  fei_ne(PDG_AT_TYP_IDX(idx));
}

void setup_fei_le()
{
  INTPTR idx;
  
  setLongVar("PDG_AT_TYP_IDX", &idx);
  
  fei_le(PDG_AT_TYP_IDX(idx));
}

void setup_fei_xor()
{
  INTPTR idx;
  
  setLongVar("PDG_AT_TYP_IDX", &idx);
  
  fei_xor(PDG_AT_TYP_IDX(idx));
}

void setup_fei_lxor()
{
  INTPTR idx;
  
  setLongVar("PDG_AT_TYP_IDX", &idx);
  
  fei_lxor(PDG_AT_TYP_IDX(idx));
}

void setup_fei_and()
{
  INTPTR idx;
  
  setLongVar("PDG_AT_TYP_IDX", &idx);
  
  fei_and(PDG_AT_TYP_IDX(idx));
}

void setup_fei_land()
{
  INTPTR idx;
  
  setLongVar("PDG_AT_TYP_IDX", &idx);
  
  fei_land(PDG_AT_TYP_IDX(idx));
}

void setup_fei_lshift()
{
  INTPTR idx;
  
  setLongVar("PDG_AT_TYP_IDX", &idx);
  
  fei_lshift(PDG_AT_TYP_IDX(idx));
}

void setup_fei_rshift()
{
  INTPTR idx;
  
  setLongVar("PDG_AT_TYP_IDX", &idx);
  
  fei_rshift(PDG_AT_TYP_IDX(idx));
}

void setup_fei_ashift()
{
  INTPTR idx;
  
  setLongVar("PDG_AT_TYP_IDX", &idx);
  
  fei_ashift(PDG_AT_TYP_IDX(idx));
}

void setup_fei_hw_rshift()
{
  INTPTR idx;
  
  setLongVar("type idx", &idx);
  
  #warning FIX: fei_hw_rshift undefined
  //fei_hw_rshift(PDG_AT_TYP_IDX(idx));
}

void setup_fei_hw_lshift()
{
  INTPTR idx;
  
  setLongVar("type idx", &idx);
  
  #warning FIX: fei_hw_lshift undefined
  //fei_hw_lshift(PDG_AT_TYP_IDX(idx));
}

void setup_fei_exponentiate()
{
  INTPTR idx;
  
  setLongVar("PDG_AT_TYP_IDX", &idx);
  
  fei_exponentiate(PDG_AT_TYP_IDX(idx));
}

void setup_fei_complex()
{
  INTPTR idx;
  
  setLongVar("PDG_AT_TYP_IDX", &idx);
  
  fei_complex(PDG_AT_TYP_IDX(idx));
}

void setup_fei_select()
{
  INTPTR idx;
  
  setLongVar("PDG_AT_TYP_IDX", &idx);
  
  fei_select(PDG_AT_TYP_IDX(idx));
}

void setup_fei_mbits()
{
  INTPTR idx;
  
  setLongVar("PDG_AT_TYP_IDX", &idx);
  
  fei_mbits(PDG_AT_TYP_IDX(idx));
}

/*
void setup_fei_dshiftl()
{
  INTPTR idx;
  
  setLongVar("type idx", &idx);
  
  fei_dshiftl(PDG_AT_TYP_IDX(idx));
}


void setup_fei_dshiftr()
{
  INTPTR idx;
  
  setLongVar("type idx", &idx);
  
  fei_dshiftr(PDG_AT_TYP_IDX(idx));
}
*/

void setup_fei_ranf()
{
  INTPTR idx;
  
  setLongVar("PDG_AT_TYP_IDX", &idx);
  
  fei_ranf(PDG_AT_TYP_IDX(idx));
}

void setup_fei_ranget()
{
  INTPTR idx;
  
  setLongVar("PDG_AT_TYP_IDX", &idx);
  
  fei_ranget(PDG_AT_TYP_IDX(idx));
}

void setup_fei_ranset()
{
  INTPTR idx;
  
  setLongVar("PDG_AT_TYP_IDX", &idx);
  
  fei_ranset(PDG_AT_TYP_IDX(idx));
}


void setup_fei_arith_goto()
{
  INT32 zero_lab;
  INT32 pos_lab;
  INT32 neg_lab;
  
  setIntVar("label idx1", &zero_lab);
  setIntVar("label idx2", &pos_lab);
  setIntVar("label idx3", &neg_lab);

  fei_arith_goto               ( PDG_AT_IDX(zero_lab),
                                 PDG_AT_IDX(pos_lab),
                                 PDG_AT_IDX(neg_lab) );
}

void setup_fei_push_pattern_con()
{
  INTPTR ndx;
  
  setLongVar("PDG_CN_IDX", &ndx);
  
  fei_push_pattern_con(PDG_CN_IDX(ndx));
}

void setup_fei_mult()
{
  INTPTR type;
  
  setLongVar("PDG_AT_TYP_IDX", &type);
  
  fei_mult(PDG_AT_TYP_IDX(type));
}

void setup_fei_indirect_goto()
{
  INT32 num_labs;
  INT32 assign_goto_flag;
  
  setIntVar("list_cnt", &num_labs);
  setIntVar("assign_goto_flag", &assign_goto_flag);
  
  fei_indirect_goto( num_labs,
                     assign_goto_flag );
}

void setup_fei_label_addr()
{
  INT32 idx;
  
  setIntVar("PDG_AT_IDX", &idx);
  
  fei_label_addr(PDG_AT_IDX(idx));
}

void setup_fei_lneg()
{
  INTPTR type;
  
  setLongVar("PDG_AT_TYP_IDX", &type);

  fei_lneg(PDG_AT_TYP_IDX(type));
}

void setup_fei_uminus()
{
  INTPTR type;
  
  setLongVar("PDG_AT_TYP_IDX", &type);

  fei_uminus(PDG_AT_TYP_IDX(type));
}

void setup_fei_abs()
{
  INTPTR type;
  
  setLongVar("PDG_AT_TYP_IDX", &type);

  fei_abs(PDG_AT_TYP_IDX(type));
}

void setup_fei_max()
{
  INT32 n_opnds;
  INTPTR type;
  
  setIntVar("count", &n_opnds);
  setLongVar("PDG_AT_TYP_IDX", &type);
  
  fei_max(n_opnds, PDG_AT_TYP_IDX(type));
}

void setup_fei_min()
{
  INT32 n_opnds;
  INTPTR type;
  
  setIntVar("count", &n_opnds);
  setLongVar("PDG_AT_TYP_IDX", &type);
  
  fei_min(n_opnds, PDG_AT_TYP_IDX(type));
}

void setup_fei_sqrt()
{
  INTPTR type;
  
  setLongVar("PDG_AT_TYP_IDX", &type);
  
  fei_sqrt(PDG_AT_TYP_IDX(type));
}

void setup_fei_exp()
{
  INTPTR type;
  
  setLongVar("PDG_AT_TYP_IDX", &type);

  fei_exp(PDG_AT_TYP_IDX(type));
}

void setup_fei_addr_con()
{
  INTPTR type;

  setLongVar("PDG_AT_TYP_IDX", &type);

  fei_addr_con(PDG_AT_TYP_IDX(type));
}

void setup_fei_trunc()
{
  INTPTR type;
  
  setLongVar("PDG_AT_TYP_IDX", &type);
  
  fei_trunc(PDG_AT_TYP_IDX(type));
}

void setup_fei_log()
{
  INTPTR type;
  
  setLongVar("PDG_AT_TYP_IDX", &type);
  
  fei_log(PDG_AT_TYP_IDX(type));
}

void setup_fei_log10()
{
  INTPTR type;
  
  setLongVar("PDG_AT_TYP_IDX", &type);
  
  fei_log10(PDG_AT_TYP_IDX(type));
}

void setup_fei_sign_xfer()
{
  INTPTR type;
  
  setLongVar("PDG_AT_TYP_IDX", &type);
  
  fei_sign_xfer(PDG_AT_TYP_IDX(type));
}

void setup_fei_pos_diff()
{
  INTPTR type;
  
  setLongVar("PDG_AT_TYP_IDX", &type);
  
  fei_pos_diff(PDG_AT_TYP_IDX(type));
}

void setup_fei_sin()
{
  INTPTR type;
  
  setLongVar("PDG_AT_TYP_IDX", &type);
  
  fei_sin(PDG_AT_TYP_IDX(type));
}

void setup_fei_sinh()
{
  INTPTR type;
  
  setLongVar("PDG_AT_TYP_IDX", &type);
  
  fei_sinh(PDG_AT_TYP_IDX(type));
}

void setup_fei_tan()
{
  INTPTR type;
  
  setLongVar("PDG_AT_TYP_IDX", &type);
  
  fei_tan(PDG_AT_TYP_IDX(type));
}

void setup_fei_tanh()
{
  INTPTR type;
  
  setLongVar("PDG_AT_TYP_IDX", &type);
  
  fei_tanh(PDG_AT_TYP_IDX(type));
}

void setup_fei_atan()
{
  INTPTR type;
  
  setLongVar("PDG_AT_TYP_IDX", &type);
  
  fei_atan(PDG_AT_TYP_IDX(type));
}

void setup_fei_atan2()
{
  INTPTR type;
  
  setLongVar("PDG_AT_TYP_IDX", &type);
  
  fei_atan2(PDG_AT_TYP_IDX(type));
}

void setup_fei_atand()
{
  INTPTR type;
  
  setLongVar("PDG_AT_TYP_IDX", &type);
  
  fei_atand(PDG_AT_TYP_IDX(type));
}

void setup_fei_round()
{
  INTPTR type;
  
  setLongVar("PDG_AT_TYP_IDX", &type);
  
  fei_round(PDG_AT_TYP_IDX(type));
}

void setup_fei_asin()
{
  INTPTR type;
  
  setLongVar("PDG_AT_TYP_IDX", &type);
  
  fei_asin(PDG_AT_TYP_IDX(type));
}

void setup_fei_cosh()
{
  INTPTR type;
  
  setLongVar("PDG_AT_TYP_IDX", &type);
  
  fei_cosh(PDG_AT_TYP_IDX(type));
}

void setup_fei_acos()
{
  INTPTR type;
  
  setLongVar("PDG_AT_TYP_IDX", &type);
  
  fei_acos(PDG_AT_TYP_IDX(type));
}

void setup_fei_imag()
{
  INTPTR type;
  
  setLongVar("PDG_AT_TYP_IDX", &type);
  
  fei_imag(PDG_AT_TYP_IDX(type));
}

void setup_fei_len()
{
  INTPTR type;
  
  setLongVar("PDG_AT_TYP_IDX", &type);
  
  fei_len(PDG_AT_TYP_IDX(type));
}

void setup_fei_len_trim()
{
  fei_len_trim();
}

void setup_fei_conjg()
{
  INTPTR type;
  
  setLongVar("PDG_AT_TYP_IDX", &type);
  
  fei_conjg(PDG_AT_TYP_IDX(type));
}

void setup_fei_cot()
{
  INTPTR type;
  
  setLongVar("PDG_AT_TYP_IDX", &type);
  
  fei_cot(PDG_AT_TYP_IDX(type));
}

void setup_fei_matmul()
{
  INTPTR type;
  
  setLongVar("PDG_AT_TYP_IDX", &type);
  
  fei_matmul(PDG_AT_TYP_IDX(type));
}

void setup_fei_spread()
{
  INTPTR type;
  
  setLongVar("PDG_AT_TYP_IDX", &type);
  
  fei_spread(PDG_AT_TYP_IDX(type));
}

void setup_fei_reshape()
{
  INTPTR type;
  
  setLongVar("PDG_AT_TYP_IDX", &type);
  
  fei_reshape(PDG_AT_TYP_IDX(type));
}

void setup_fei_transpose()
{
  INTPTR type;
  
  setLongVar("PDG_AT_TYP_IDX", &type);
  
  fei_transpose(PDG_AT_TYP_IDX(type));
}

void setup_fei_sum()
{
  INTPTR type;
  
  setLongVar("PDG_AT_TYP_IDX", &type);
  
  fei_sum(PDG_AT_TYP_IDX(type));
}

void setup_fei_eoshift()
{
  INTPTR type;
  
  setLongVar("PDG_AT_TYP_IDX", &type);
  
  fei_eoshift(PDG_AT_TYP_IDX(type));
}

void setup_fei_maxval()
{
  INTPTR type;
  
  setLongVar("PDG_AT_TYP_IDX", &type);
  
  fei_maxval(PDG_AT_TYP_IDX(type));
}

void setup_fei_minval()
{
  INTPTR type;
  
  setLongVar("PDG_AT_TYP_IDX", &type);
  
  fei_minval(PDG_AT_TYP_IDX(type));
}

void setup_fei__minloc()
{
  INTPTR type;
  
  setLongVar("PDG_AT_TYP_IDX", &type);
  
  fei__minloc(PDG_AT_TYP_IDX(type));
}

void setup_fei__maxloc()
{
  INTPTR type;
  
  setLongVar("PDG_AT_TYP_IDX", &type);
  
  fei__maxloc(PDG_AT_TYP_IDX(type));
}

void setup_fei_all()
{
  INTPTR type;
  
  setLongVar("PDG_AT_TYP_IDX", &type);
  
  fei_all(PDG_AT_TYP_IDX(type));
}

void setup_fei_any()
{
  INTPTR type;
  
  setLongVar("PDG_AT_TYP_IDX", &type);
  
  fei_any(PDG_AT_TYP_IDX(type));
}

void setup_fei_count()
{
  INTPTR type;
  
  setLongVar("PDG_AT_TYP_IDX", &type);
  
  fei_count(PDG_AT_TYP_IDX(type));
}

void setup_fei_product()
{
  INTPTR type;
  
  setLongVar("PDG_AT_TYP_IDX", &type);
  
  fei_product(PDG_AT_TYP_IDX(type));
}

void setup_fei_cshift()
{
  INTPTR type;
  
  setLongVar("PDG_AT_TYP_IDX", &type);
  
  fei_cshift(PDG_AT_TYP_IDX(type));
}

void setup_fei_dot_product()
{
  INTPTR type;
  
  setLongVar("PDG_AT_TYP_IDX", &type);
  
  fei_dot_product(PDG_AT_TYP_IDX(type));
}

void setup_fei_dot_product_logical()
{
  INTPTR type;
  
  setLongVar("PDG_AT_TYP_IDX", &type);
  
  fei_dot_product_logical(PDG_AT_TYP_IDX(type));
}

void setup_fei_adjustl()
{
  INTPTR type;
  
  setLongVar("PDG_AT_TYP_IDX", &type);
  
  fei_adjustl(PDG_AT_TYP_IDX(type));
}

void setup_fei_verify()
{
  INTPTR type;
  
  setLongVar("PDG_AT_TYP_IDX", &type);
  
  fei_verify(PDG_AT_TYP_IDX(type));
}

void setup_fei_scan()
{
  INTPTR type;
  
  setLongVar("PDG_AT_TYP_IDX", &type);
  
  fei_scan(PDG_AT_TYP_IDX(type));
}

void setup_fei_adjustr()
{
  INTPTR type;
  
  setLongVar("PDG_AT_TYP_IDX", &type);
  
  fei_adjustr(PDG_AT_TYP_IDX(type));
}

void setup_fei_bneg()
{
  INTPTR type;
  
  setLongVar("PDG_AT_TYP_IDX", &type);
  
  fei_bneg(PDG_AT_TYP_IDX(type));
}

void setup_fei_ceiling()
{
  INTPTR type;
  
  setLongVar("PDG_AT_TYP_IDX", &type);
  
  fei_ceiling(PDG_AT_TYP_IDX(type));
}

void setup_fei_exponent()
{
  INTPTR type;
  
  setLongVar("PDG_AT_TYP_IDX", &type);
  
  fei_exponent(PDG_AT_TYP_IDX(type));
}

void setup_fei_floor()
{
  INTPTR type;
  
  setLongVar("PDG_AT_TYP_IDX", &type);
  
  fei_floor(PDG_AT_TYP_IDX(type));
}

void setup_fei_scale()
{
  INTPTR type;
  
  setLongVar("PDG_AT_TYP_IDX", &type);
  
  fei_scale(PDG_AT_TYP_IDX(type));
}

void setup_fei_modulo()
{
  INTPTR type;
  
  setLongVar("PDG_AT_TYP_IDX", &type);
  
  fei_modulo(PDG_AT_TYP_IDX(type));
}

void setup_fei_near()
{
  INTPTR type;
  
  setLongVar("PDG_AT_TYP_IDX", &type);
  
  fei_near(PDG_AT_TYP_IDX(type));
}

void setup_fei_rrspace()
{
  INTPTR type;
  
  setLongVar("PDG_AT_TYP_IDX", &type);
  
  fei_rrspace(PDG_AT_TYP_IDX(type));
}

void setup_fei_space()
{
  INTPTR type;
  
  setLongVar("PDG_AT_TYP_IDX", &type);
  
  fei_space(PDG_AT_TYP_IDX(type));
}

void setup_fei_set_exponent()
{
  INTPTR type;
  
  setLongVar("PDG_AT_TYP_IDX", &type);
  
  fei_set_exponent(PDG_AT_TYP_IDX(type));
}

void setup_fei_ishftc()
{
  INTPTR type;
  
  setLongVar("PDG_AT_TYP_IDX", &type);
  
  fei_ishftc(PDG_AT_TYP_IDX(type));
}

void setup_fei_ibits()
{
  INTPTR type;
  
  setLongVar("PDG_AT_TYP_IDX", &type);
  
  fei_ibits(PDG_AT_TYP_IDX(type));
}

void setup_fei_popcnt()
{
  INTPTR type;
  INTPTR arg_type;
  
  setLongVar("PDG_AT_TYP_IDX", &type);
  setLongVar("arg PDG_AT_TYP_IDX", &arg_type);
  
  fei_popcnt(PDG_AT_TYP_IDX(type), PDG_AT_TYP_IDX(arg_type));
}

void setup_fei_poppar()
{
  INTPTR type;
  INTPTR arg_type;
  
  setLongVar("PDG_AT_TYP_IDX", &type);
  setLongVar("arg PDG_AT_TYP_IDX", &arg_type);
  
  fei_poppar(PDG_AT_TYP_IDX(type), PDG_AT_TYP_IDX(arg_type));
}

void setup_fei_leadz()
{
  INTPTR type;
  INTPTR arg_type;
  
  setLongVar("PDG_AT_TYP_IDX", &type);
  setLongVar("arg PDG_AT_TYP_IDX", &arg_type);
  
  fei_leadz(PDG_AT_TYP_IDX(type), PDG_AT_TYP_IDX(arg_type));
}

void setup_fei_iolength()
{
  fei_iolength();
}

void setup_fei_fraction()
{
  fei_fraction();
}

void setup_fei_non_conform_store()
{
  fei_non_conform_store(null_type);
}

void setup_fei_pack()
{
  INTPTR type;
  
  setLongVar("PDG_AT_TYP_IDX", &type);
  
  fei_pack(PDG_AT_TYP_IDX(type));
}

void setup_fei_unpack()
{
  INTPTR type;
  
  setLongVar("PDG_AT_TYP_IDX", &type);
  
  fei_unpack(PDG_AT_TYP_IDX(type));
}


void setup_fei_copyin_bound()
{
  INTPTR sym_idx;
  
  setLongVar("PDG_AT_IDX", &sym_idx);
  
  fei_copyin_bound(PDG_AT_IDX(sym_idx));
}

void setup_fei_new_binop_cshift()
{
  INTPTR type;
  
  setLongVar("PDG_AT_TYP_IDX", &type);
  
  fei_new_binop_cshift(PDG_AT_TYP_IDX(type));
}
