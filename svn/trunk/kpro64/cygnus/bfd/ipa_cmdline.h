/*
 * Copyright 2003, 2004, 2005 PathScale, Inc.  All Rights Reserved.
 */

#ifndef __IPA_CMDLINE_H__
#define __IPA_CMDLINE_H__

extern CYGWINDLLOUTPUT char* psclp_arg;

extern CYGWINDLLOUTPUT int arg_count;			    /* argument count */
extern CYGWINDLLOUTPUT char **arg_vector;		    /* argument vector */
extern CYGWINDLLOUTPUT char **environ_vars;		    /* list of environment variables */

extern CYGWINDLLOUTPUT int ipa_argc;
extern CYGWINDLLOUTPUT char **ipa_argv;
extern CYGWINDLLOUTPUT unsigned int max_gpa_size;
extern CYGWINDLLOUTPUT bfd_boolean is_ipa;
extern CYGWINDLLOUTPUT unsigned int used_gp_area;

extern CYGWINDLLOUTPUT bfd_boolean
ipa_search_command_line(int, char **, char **);



#endif /* __IPA_CMDLINE_H__ */
