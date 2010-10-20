/*
 * Copyright 2003, 2004, 2005 PathScale, Inc.  All Rights Reserved.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of version 2 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it would be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  
 *
 * Further, this software is distributed without any warranty that it is
 * free of the rightful claim of any third person regarding infringement 
 * or the like.  Any license provided herein, whether implied or 
 * otherwise, applies only to this software file.  Patent licenses, if 
 * any, provided herein do not apply to combinations of this program with 
 * other software, or any other product whatsoever.  
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write the Free Software Foundation, Inc., 59
 * Temple Place - Suite 330, Boston MA 02111-1307, USA.
 */

#if defined(__GNUC__)
#include <stdio.h>		/* for sys_errlist */
#endif
#include <stdlib.h>		/* for getenv(3) */
#include <unistd.h>		/* for unlink(2), rmdir(2), etc. */
#include <libgen.h>		/* for basename(3) */
#include <sys/stat.h>		/* for chmod(2) */
#include <sys/mman.h>		/* for mmap(2) */
#include <fcntl.h>		/* for open(2) */
#include <sys/dir.h>		/* for opendir(2), readdir, closedir */
#include <sys/wait.h>		/* for waitpid(2) */
#include <alloca.h>		/* for alloca(3) */
#include <signal.h>		/* for kill(2) */
#include <limits.h>		/* for PATH_MAX */
#include <errno.h>
#include <string.h>

#include "aout/ar.h"

#include "bfd.h"
#include "libbfd.h"
#include "elf-bfd.h"

#include "ipa_ld.h"
#include "ipa_cmdline.h"

char *psclp_arg = NULL;	// PathScale subscription

int arg_count;			    /* argument count */
char **arg_vector;		    /* argument vector */
char **environ_vars;		    /* list of environment variables */
    	    	    	    	    /* used by ipa to invoke recompilation */

unsigned int max_gpa_size = 0x100000; /* gp area size, needs to more accurate */
unsigned int used_gp_area;

int ipa_argc = 0;
char ** ipa_argv = NULL;

static int orig_iargc_size = 10;
static char char_opt[] = {'a','A','b','c','e','f','F','G','h','l','L','m','o','O','R','T','u','y','Y','z','0'};

extern string outfilename;
extern void ipa_insert_whirl_obj_marker(void);

/* 
    I took the following out of /usr/include/elf.h because
    for some reason bfd doesn't want to use it and it was
    too complicated to use the bfd model at this time.
    
    This is stupid, I know.
    
*/

/* Standard ELF types.  */

#include <stdint.h>

/* Type for a 16-bit quantity.  */
typedef uint16_t Elf32_Half;
typedef uint16_t Elf64_Half;

/* Types for signed and unsigned 32-bit quantities.  */
typedef uint32_t Elf32_Word;
typedef	int32_t  Elf32_Sword;
typedef uint32_t Elf64_Word;
typedef	int32_t  Elf64_Sword;

/* Types for signed and unsigned 64-bit quantities.  */
typedef uint64_t Elf32_Xword;
typedef	int64_t  Elf32_Sxword;
typedef uint64_t Elf64_Xword;
typedef	int64_t  Elf64_Sxword;

/* Type of addresses.  */
typedef uint32_t Elf32_Addr;
typedef uint64_t Elf64_Addr;

/* Type of file offsets.  */
typedef uint32_t Elf32_Off;
typedef uint64_t Elf64_Off;

/* Type for section indices, which are 16-bit quantities.  */
typedef uint16_t Elf32_Section;
typedef uint16_t Elf64_Section;

/* Type of symbol indices.  */
typedef uint32_t Elf32_Symndx;
typedef uint64_t Elf64_Symndx;

/* The ELF file header.  This appears at the start of every ELF file.  */

#ifndef EI_NIDENT
#define EI_NIDENT (16)
#endif

typedef struct
{
  unsigned char	e_ident[EI_NIDENT];	/* Magic number and other info */
  Elf32_Half	e_type;			/* Object file type */
  Elf32_Half	e_machine;		/* Architecture */
  Elf32_Word	e_version;		/* Object file version */
  Elf32_Addr	e_entry;		/* Entry point virtual address */
  Elf32_Off	e_phoff;		/* Program header table file offset */
  Elf32_Off	e_shoff;		/* Section header table file offset */
  Elf32_Word	e_flags;		/* Processor-specific flags */
  Elf32_Half	e_ehsize;		/* ELF header size in bytes */
  Elf32_Half	e_phentsize;		/* Program header table entry size */
  Elf32_Half	e_phnum;		/* Program header table entry count */
  Elf32_Half	e_shentsize;		/* Section header table entry size */
  Elf32_Half	e_shnum;		/* Section header table entry count */
  Elf32_Half	e_shstrndx;		/* Section header string table index */
} Elf32_Ehdr;

typedef struct
{
  unsigned char	e_ident[EI_NIDENT];	/* Magic number and other info */
  Elf64_Half	e_type;			/* Object file type */
  Elf64_Half	e_machine;		/* Architecture */
  Elf64_Word	e_version;		/* Object file version */
  Elf64_Addr	e_entry;		/* Entry point virtual address */
  Elf64_Off	e_phoff;		/* Program header table file offset */
  Elf64_Off	e_shoff;		/* Section header table file offset */
  Elf64_Word	e_flags;		/* Processor-specific flags */
  Elf64_Half	e_ehsize;		/* ELF header size in bytes */
  Elf64_Half	e_phentsize;		/* Program header table entry size */
  Elf64_Half	e_phnum;		/* Program header table entry count */
  Elf64_Half	e_shentsize;		/* Section header table entry size */
  Elf64_Half	e_shnum;		/* Section header table entry count */
  Elf64_Half	e_shstrndx;		/* Section header string table index */
} Elf64_Ehdr;

#ifdef __CYGWIN__
//ABSOFT_EXTENSIONS
extern int Min_Error_Severity;
#endif

	/*******************************************************
		Function: ipa_opt



	 *******************************************************/
static int
ipa_opt (char **argv )
{
    if (ipa_argc == 0) {
	ipa_argv = (string *) MALLOC (orig_iargc_size * sizeof (string));
	MALLOC_ASSERT (ipa_argv);
    }
    else if (ipa_argc >= orig_iargc_size) {
	orig_iargc_size *=2;
	ipa_argv = (string *) REALLOC (ipa_argv, (orig_iargc_size * sizeof(string)));
	MALLOC_ASSERT (ipa_argv);
    }

    ipa_argv[ipa_argc++] = ipa_copy_of(argv[0]);

    return 1;
} /* ipa_opt */

/* ====================================================================
 *
 * add_WB_opt
 *
 * We have an option -WB,... to be passed to the back end via ipacom.
 * If WB_flags is NULL, set it to this option with "-WB," stripped.
 * Otherwise append this option with "-WB" stripped, i.e. retaining the
 * comma separator.
 *
 * ====================================================================
 */

static void
add_WB_opt (char **argv)
{
    char *p = *argv;

    if ( WB_flags == NULL ) {
    	WB_flags = concat_names("-Wb,",&p[3]);
    } else {
    	char *flg = concat_names(WB_flags,&p[3] ); /* include the comma */
    	FREE(WB_flags);
    	WB_flags = flg;
  }

  return;
}


/* ====================================================================
 *
 * add_Y_opt
 *
 * We have an option -Y... to be passed to the back end via ipacom.
 * If Y_flags is NULL, set it to this option.  Otherwise append this
 * option with a space delimiter.
 *
 * ====================================================================
 */

static void
add_Y_opt (char **argv)
{
    char *p = *argv;

    if ( Y_flags == NULL ) {
    	Y_flags = ipa_copy_of(p);
    } else {
    	char *flg;
	
	flg = concat_names(Y_flags," ");
	FREE (Y_flags);
	Y_flags = flg;
	
	flg = concat_names(Y_flags,p);
	FREE (Y_flags);
	Y_flags = flg;
    }

    return;
}

	/*******************************************************
		Function: check_for_whirl

		Check to see if this is an ELF file and then
		if it is a WHIRL object.
		
		I need to expand this to check for archives.

	 *******************************************************/
#define ET_SGI_IR   (ET_LOPROC + 0)
static bfd_boolean
check_for_whirl(char *name)
{
    int fd = -1;
    char *raw_bits = NULL;
    int size,bufsize;
    Elf32_Ehdr *p_ehdr = NULL;
    struct stat statb;
    int test;
    
    fd = OPEN(name, O_RDONLY, 0755);
    if (fd < 0)
	return FALSE;

    if ((test = fstat(fd, &statb) != 0)) {
    	CLOSE(fd);
	return FALSE;
    }

    if (statb.st_size < sizeof(Elf64_Ehdr)) {
    	CLOSE(fd);
    	return FALSE;
    }
    
    bufsize = sizeof(Elf64_Ehdr);
    
    raw_bits = (char *)MALLOC(bufsize*4);
    MALLOC_ASSERT(raw_bits);

    size = READ(fd, raw_bits, bufsize);
#if 0
    if (size != statb.st_size) {
    	CLOSE(fd);
    	FREE(raw_bits);
    	return FALSE;
    }
#endif
    
		/*
		 * Check that the file is an elf executable.
		 */
    p_ehdr = (Elf32_Ehdr *)raw_bits;
    if (p_ehdr->e_ident[EI_MAG0] != ELFMAG0 ||
	p_ehdr->e_ident[EI_MAG1] != ELFMAG1 ||
	p_ehdr->e_ident[EI_MAG2] != ELFMAG2 ||
	p_ehdr->e_ident[EI_MAG3] != ELFMAG3) {
	    CLOSE(fd);
	    FREE(raw_bits);
	    return(FALSE);
    }

    if(p_ehdr->e_ident[EI_CLASS] == ELFCLASS32){
    	Elf32_Ehdr *p32_ehdr = (Elf32_Ehdr *)raw_bits;
	if (p32_ehdr->e_type == ET_SGI_IR) {
	    CLOSE(fd);
	    FREE(raw_bits);
	    return TRUE;
	}
    }
    else {
	Elf64_Ehdr *p64_ehdr = (Elf64_Ehdr *)raw_bits;
	if (p64_ehdr->e_type == ET_SGI_IR) {
	    CLOSE(fd);
	    FREE(raw_bits);
	    return TRUE;
	}
     }

    CLOSE(fd);
    FREE(raw_bits);
    return FALSE;
    
 }

	/*******************************************************
		Function: needs_argument.

		Determine if this option needs an argument.
		This routine will need to change as the commandline
		arguments change or are augmented.

	 *******************************************************/
static bfd_boolean
needs_argument(char *string, bfd_boolean is_double_dash)
{

    int len = strlen(string);

    if (is_double_dash) {
    	if ((strcmp (string, "architecture") == 0)) {
    	    return TRUE;
    	}
    	if ((strcmp (string, "format") == 0)) {
    	    return TRUE;
    	}
    	if ((strcmp (string, "mri-script") == 0)) {
    	    return TRUE;
    	}
    	if ((strcmp (string, "entry") == 0)) {
    	    return TRUE;
    	}
    	if ((strcmp (string, "auxiliary") == 0)) {
    	    return TRUE;
    	}
    	if ((strcmp (string, "filter") == 0)) {
    	    return TRUE;
    	}
    	if ((strcmp (string, "gpsize") == 0)) {
    	    return TRUE;
    	}
    	if ((strcmp (string, "library") == 0)) {
    	    return TRUE;
    	}
    	if ((strcmp (string, "library-path") == 0)) {
    	    return TRUE;
    	}
    	if ((strcmp (string, "output") == 0)) {
    	    return TRUE;
    	}
    	if ((strcmp (string, "just-symbols") == 0)) {
    	    return TRUE;
    	}
    	if ((strcmp (string, "script") == 0)) {
    	    return TRUE;
    	}
    	if ((strcmp (string, "undefined") == 0)) {
    	    return TRUE;
    	}
    	if ((strcmp (string, "trace-symbol") == 0)) {
    	    return TRUE;
    	}
    	if ((strcmp (string, "assert") == 0)) {
    	    return TRUE;
    	}
    	if ((strcmp (string, "defsym") == 0)) {
    	    return TRUE;
    	}
    	if ((strcmp (string, "dynamic-linker") == 0)) {
    	    return TRUE;
    	}
    	if ((strcmp (string, "Map") == 0)) {
    	    return TRUE;
    	}
    	if ((strcmp (string, "oformat") == 0)) {
    	    return TRUE;
    	}
    	if ((strcmp (string, "retain-symbols-file") == 0)) {
    	    return TRUE;
    	}
    	if ((strcmp (string, "rpath-link") == 0)) {
    	    return TRUE;
    	}
    	if ((strcmp (string, "split-by-reloc") == 0)) {
    	    return TRUE;
    	}
    	if ((strcmp (string, "task-link") == 0)) {
    	    return TRUE;
    	}
    	if ((strcmp (string, "verbose") == 0)) {
    	    return TRUE;
    	}
    	if ((strcmp (string, "version-script") == 0)) {
    	    return TRUE;
    	}
    	if ((strcmp (string, "version-exports-section") == 0)) {
    	    return TRUE;
    	}
    	if ((strcmp (string, "wrap") == 0)) {
    	    return TRUE;
    	}
    }
    else {
    	if (len == 1) {
	    int i;
	    int size = strlen(char_opt);
	    for (i=0;i<size;i++) {
	    	if (char_opt[i] == *string)
		    return TRUE;
	    }
	    return FALSE;
	}
    	if ((strcmp (string, "soname") == 0)) {
    	    return TRUE;
    	}
    	if ((strcmp (string, "rpath") == 0)) {
    	    return TRUE;
    	}
    	if ((strcmp (string, "Tbss") == 0)) {
    	    return TRUE;
    	}
    	if ((strcmp (string, "Tdata") == 0)) {
    	    return TRUE;
    	}
    	if ((strcmp (string, "Ttext") == 0)) {
    	    return TRUE;
    	}
    }
    
    return FALSE;
}


	/*******************************************************
		Function: blank_arg.

		Blank out the given argument so other parts
		of the program that read the argv don't get
		confused.

	 *******************************************************/
static void
blank_arg(char **argv, int ndx)
{

    int j,len;

    len = strlen(argv[ndx]);

#if 1
    if (len >=3)
    	strcpy(argv[ndx],"-g"); /* ignored by the linker */
    else {
/*    	for(j=0;j<len;j++)
    	    argv[ndx][j] = ' ';*/
	/* ABSOFT_EXTENSIONS*/
	/* for Xlinker */    
	argv[ndx] = "-g";
    }
#else
    argv[ndx][0] = '\0';
#endif

}

#ifdef __CYGWIN__
// ABSOFT_EXTENSIONS
static const char * lbasename (const char *name)
{
  const char *base;

  /* Skip over a possible disk name.  */
  if (((name[0]>='A'&&name[0]<='Z')||(name[0]>='a'&&name[0]<='z')) && name[1] == ':') 
    name += 2;

  for (base = name; *name; name++)
    if ( (*name) == '/' || (*name) == '\\' )
      base = name + 1;

  return base;
}
#endif


	/*******************************************************
		Function: opt_search_command_line.

		Read through the command line looking at each
		option. If a linker commandfile is encountered
		it will be open'ed an it's file descriptor pushed
		on a stack of file descriptors. The contents of
		the file will be read like options on the command
		line.

		This routine will eventually rebuild the input
		command order to get rid of silly command order
		errors.

	 *******************************************************/
bfd_boolean
ipa_search_command_line(int argc,
			char **argv,
			char **envp
			)
{
    int i;
#ifdef __CYGWIN__
    static string working_dir = 0;
    int length;
    int j;
#endif

    	/*
    	 * First check if ipa is on.
    	 */
    for (i=1;i<argc;i++) {
    	char *string = argv[i];
    	if (*string == '-') {
	    if ((strncmp(string,"-IPA",4)) == 0) {
	    	is_ipa = TRUE;
#ifndef __CYGWIN__
	    	break;
#endif
	    }
	    else if ((strncmp(string,"--IPA",5)) == 0) {
	    	is_ipa = TRUE;
#ifndef __CYGWIN__
		break;
#endif
	    }
	    else if ((strcmp(string,"--ipa")) == 0) {
	    	is_ipa = TRUE;
#ifndef __CYGWIN__
		break;
#endif
	    }
 	    else if ((strcmp(string,"-ipa")) == 0) {
	    	is_ipa = TRUE;
#ifndef __CYGWIN__
		break;
#endif
	    }
    	}
#ifdef __CYGWIN__
        // ABSOFT_EXTENSIONS
        /* support /LIBPATH: or -LIBPATH: 
           convert it to -L
        */
        if( *string == '-' || *string == '/' ){
	    int found = FALSE;
	    if( (strncmp(string,"/LIBPATH:", 9 ) ) == 0 ){
		    found = TRUE;
	    }else if( (strncmp(string,"/LIBPATH:", 9 ) ) == 0 ){
		    found = TRUE;
	    }
	    
	    if( found == TRUE ){
		    string[0] = '-';
		    string[1] = 'L';
		    length = strlen( string );
		    for( j = 9; j <= length; j ++ ){
			    string[j-7] = string[j];
			    if( string[j-7] == '\\' ) string[j-7] = '/';
		    }
	    }
	}
#endif
    }

    if (!is_ipa)
    	return(FALSE);

    arg_count = argc;
    arg_vector = argv;
    environ_vars = envp;

    	/*
	 *  The ipa.so needs to be opened and entry
	 *  points need to be found with dlsym.
	 */
    ipa_set_syms();
#ifdef KEY
    (*p_Ipalink_Set_Error_Phase)("IPA Startup");
#endif

    	/*
    	 * We need to build up the commandline options
    	 * that will be passed to the linker/compiler during
         * the second pass
    	 */
    (*p_ipa_init_link_line) (0, NULL);
#ifdef __CYGWIN__
    //ABSOFT_EXTENSIONS
    int seeit = FALSE;
#endif

    for (i=1;i<argc;i++) {
    	char *string = argv[i];
	/* handle /STACK */
#ifdef __APPLE__
        if( *string == '-' ){
	     if( strncmp( string, "-Wl,", 4 ) == 0 ){
		 (*p_ipa_add_link_flag) ( concat_names( string, "" ) );
		 blank_arg(argv,i);
		 continue;		      
	     }
	     if( strcmp( string, "-Xlinker" ) == 0 ){
		 (*p_ipa_add_link_flag) ( concat_names( string, "" ) );
		 string = argv[i+1];
		 (*p_ipa_add_link_flag) ( concat_names( string, "" ) );
		 blank_arg(argv,i);
		 blank_arg(argv,i+1);
		 i++;
		 continue;
	     }
	}
        if( *string == '-' ){
	     if( strncmp( string, "-gcc,", 5 ) == 0 ){
		 (*p_ipa_add_link_flag) ( concat_names( string+5, "" ) );
		 blank_arg(argv,i);
		 continue;		      
	     }
	}
#endif
#ifdef __CYGWIN__
	if( *string == '/' ){
	    if( (strncmp(string, "/STACK:", 7 ) ) == 0 ){
		    string[0] = '-';
		    string[1] = 's';
		    string[2] = 't';
		    string[3] = 'a';
		    string[4] = 'c';
		    string[5] = 'k';
	    	    (*p_ipa_add_link_flag) ( concat_names( string, "" ) );
	    	    blank_arg(argv,i);
	    	    continue;
	    }else if( (strncmp(string, "/DEBUG", 6 ) ) == 0 ){
		    (*p_ipa_add_link_flag) ( "-g" );
	    	    blank_arg(argv,i);
	    	    continue;
	    }else if( (strncmp(string, "/INCREMENTAL:", 13 ) ) == 0 ){
	    	    blank_arg(argv,i);
	    	    continue;
	    }else if( (strncmp(string, "/LARGEADDRESSAWARE", 18 ) ) == 0 ){
	    	    if( (strncmp(string, "/LARGEADDRESSAWARE:NO", 21 ) ) == 0 ){
		    	// Do nothing
		    }else{
		    	(*p_ipa_add_link_flag) ( "-Xlinker /LARGEADDRESSAWARE" );
		    }
		    blank_arg(argv,i);
		    continue;
	    } 

	}
	if( *string == '-' ){
	    if( strncmp(string, "-stack:", 7 ) == 0 ){
		(*p_ipa_add_link_flag) ( concat_names( string, "" ) );
		blank_arg(argv,i);    
		continue;
	    }else if( strncmp(string, "-heap:", 6 ) == 0 ){
		(*p_ipa_add_link_flag) ( concat_names( string, "" ) );
		blank_arg(argv,i);    
		continue;	    
	    }else if( strncmp(string, "-cygwin:", 8 ) == 0 ){
	    	/* set cygwin path */
	        char *old_path;
                char *new_path;
		char *cygwin_path;
		
		cygwin_path = string + 8;
                old_path = getenv("PATH");
    		new_path = concat_names( cygwin_path, ":" );
    		new_path = concat_names( new_path, old_path );
	        setenv( "PATH", new_path, TRUE );	
		
		blank_arg(argv,i);
		continue;	
	    }
		    
	}
#endif
#ifdef __CYGWIN__
	/* -w suppress IPA warning*/
	if( *string == '-' ){
	     if( strncmp(string, "-nowarning", 10 ) == 0 ){
	         Min_Error_Severity = 4;
	         blank_arg(argv,i); 
	         continue; 
     	     }
	     if( strncmp(string, "-DLL", 4 ) == 0 ){
                (*p_ipa_add_link_flag) ( "-dll" );
		blank_arg(argv,i);
		continue;
             }
	     if( strncmp(string, "-subsystem:windows", 18 ) == 0 ){
                (*p_ipa_add_link_flag) ( "-subsystem:windows" );
		blank_arg(argv,i);
		continue;
             }	     	     
	}
	if( strlen( string ) > 4 ){
            // Check *.LIB
           char* ext = string + strlen( string ) - 3;
           if( strcasecmp( ext, "LIB" ) == 0 && string[0] != '-' && string[0] != '/' &&
               string[1] == ':' ){
    	       (*p_ipa_add_link_flag) ( concat_names( string, "" ) );
    	       blank_arg(argv,i);
    	       continue;
	   }	
        }
#endif
    	if (*string == '-' && string[1] == '-') {
	    if ((strncmp (&string[2], "ipa", strlen ("ipa")) == 0)) {
	    	continue;
	    }
	    if ((strncmp (&string[2], "IPA:", strlen ("IPA:")) == 0)) {
    	    	char *p = &argv[i][1];
	    	ipa_opt(&p);
		blank_arg(argv,i);
	    	continue;
	    }
	    if ((strcmp (&string[2], "keep") == 0)) {
    	    	ld_ipa_opt[LD_IPA_KEEP_TEMPS].flag = TRUE;
		    /* Blank out argument */
		blank_arg(argv,i);
	    	continue;
	    }
	    else if ((needs_argument(&string[2],TRUE) == TRUE)) {
	    	(*p_ipa_add_link_flag) (argv[i++]);
		(*p_ipa_add_link_flag) (argv[i]);
		continue;
	    }
	}   /* if "--" */
	else if (*string == '-') {
	    if ((strncmp(string,"-WB,",4)) == 0) {
	    	add_WB_opt (&argv[i]);

		    /* Blank out argument */
		blank_arg(argv,i);
		continue;
	    }
	    else if ((strncmp(string,"-Y",2)) == 0) {
	    	add_Y_opt (&argv[i]);

		    /* Blank out argument */
		blank_arg(argv,i);
		continue;
	    }
	    if ((strncmp (string, "-ipacom", strlen ("-ipacom")) == 0)) {
		blank_arg(argv,i);
	    	continue;
	    }
	    if ((strncmp (string, "-ipa", strlen ("-ipa")) == 0)) {
		blank_arg(argv,i);
	    	continue;
	    }
	    if ((strncmp (string, "-DEFAULT:", strlen ("-DEFAULT:")) == 0)) {
	    	ipa_opt(&argv[i]);
		blank_arg(argv,i);
	    	continue;
	    }
	    if ((strncmp (string, "-IPA:", strlen ("-IPA:")) == 0)) {
	    	ipa_opt(&argv[i]);
		blank_arg(argv,i);
	    	continue;
	    }
	    if ((strncmp (string, "-INLINE:", strlen ("-INLINE:")) == 0)) {
	    	ipa_opt(&argv[i]);
		blank_arg(argv,i);
	    	continue;
	    }
	    if ((strncmp (string, "-INTERNAL:", strlen ("-INTERNAL:")) == 0)) {
	    	ipa_opt(&argv[i]);
		blank_arg(argv,i);
	    	continue;
	    }
	    if ((strncmp (string, "-OPT:", strlen ("-OPT:")) == 0)) {
	    	ipa_opt(&argv[i]);
		blank_arg(argv,i);
	    	continue;
	    }
	    if ((strncmp (string, "-TENV:", strlen ("-TENV:")) == 0)) {
	    	ipa_opt(&argv[i]);
		blank_arg(argv,i);
	    	continue;
	    }
		if ((strcmp(string, "-77")) == 0) {
			ld_ipa_opt[LD_IPA_F77].flag = TRUE;
		blank_arg(argv,i);
			continue;
		}
		if ((strcmp(string, "-90")) == 0) {
			ld_ipa_opt[LD_IPA_F90].flag = TRUE;
		blank_arg(argv,i);
			continue;
		}
		if ((strcmp(string, "-95")) == 0) {
			ld_ipa_opt[LD_IPA_F95].flag = TRUE;
		blank_arg(argv,i);
			continue;
		}
		if ((strcmp(string, "-2k3")) == 0) {
			ld_ipa_opt[LD_IPA_F2K3].flag = TRUE;
		blank_arg(argv,i);
			continue;
		}
	    // PathScale subscription
	    if ((strcmp (string, "-psclp") == 0)) {
	    	psclp_arg = malloc(10 + strlen(argv[i+1]));
		sprintf (psclp_arg, "-psclp %s", argv[i+1]);
		blank_arg(argv,i);
		blank_arg(argv,i+1);
	    	continue;
	    }
	    else if ((strcmp(string,"-keep")) == 0) {
    	    	ld_ipa_opt[LD_IPA_KEEP_TEMPS].flag = TRUE;

		    /* Blank out argument */
		blank_arg(argv,i);
		continue;
	    }
	    else if ((strcmp(string,"-show")) == 0) {
    	    	ld_ipa_opt[LD_IPA_SHOW].flag = TRUE;

		    /* Blank out argument */
		blank_arg(argv,i);
		continue;
	    }
	    else if ((strcmp(string,"-demangle")) == 0) {
    	    	ld_ipa_opt[LD_IPA_DEMANGLE].flag = TRUE;

		    /* Blank out argument */
		blank_arg(argv,i);
		continue;
	    }
	    else if ((strcmp(string,"-o")) == 0) {
#ifdef __CYGWIN__
		seeit = TRUE;
#endif
    	    	outfilename = MALLOC(strlen(argv[i+1])+3);
    	    	MALLOC_ASSERT(outfilename);
		strcpy(outfilename,"");
		strcat(outfilename,argv[i+1]);
	    	(*p_ipa_add_link_flag) (argv[i++]);
#ifdef KEY
		{
		  // Remove the path component from the outfile name since we
		  // will be linking in the ipa temp dir.  After linking, we
		  // move the outfile to the temp dir's parent.  Bug 5876.
#if defined(__CYGWIN__) || defined(__APPLE__)
		  char *bname = lbasename(argv[i]);
#else
		  char *bname = basename(argv[i]);
#endif
		  // gnu basename() doesn't strip off multiple slashes.
		  while (*bname == '/')
		    bname++;
		  (*p_ipa_add_link_flag) (bname);
		}
#else
		(*p_ipa_add_link_flag) (argv[i]);
#endif
		continue;
	    }
	    else if ((strcmp(string,"-v")) == 0) {
    	    	ld_ipa_opt[LD_IPA_VERBOSE].flag = TRUE;
	    }
	    	    /* Check for sgi debug tracing */
	    else if (string[1] == 't' && strlen(string) > 3) {
	    	ipa_opt(&argv[i]);

		    /* Blank out argument */
		blank_arg(argv,i);
		continue;
	    }
	    else if (needs_argument(&string[1],FALSE)) {
	    	(*p_ipa_add_link_flag) (argv[i++]);
		(*p_ipa_add_link_flag) (argv[i]);
		continue;
	    }
	}
	/* This splits the post ipa commandline arguments */
	else if (check_for_whirl(argv[i])){
	    (*p_ipa_insert_whirl_marker)();
	    continue;
	}
	
#ifdef __CYGWIN__
	if( strlen( string ) > 4 ){
            // Check *.LIB
            char* ext = string + strlen( string ) - 3;
            if( strcasecmp( ext, "LIB" ) == 0 && string[0] != '-' && string[0] != '/' &&
                string[1] != ':' ){ // Not an absolute path
	        // change to -l*.LIB and add a searching path
	        if (working_dir == 0) {
		    working_dir = getcwd ((char *) NULL, PATH_MAX);
		    if (working_dir == NULL) {
			perror("getcwd(3)");
			exit(1);
	    	    }
	    	    if( strncmp(working_dir, "/cygdrive/", 10 ) == 0 ){
		    	// Convert back to the register path
		    	if( working_dir[11] == '/' ){
			    length  = strlen( working_dir );
			    for( j = 9; j <= length; j ++ ){
				 working_dir[j-9] = working_dir[j];
			    } 	
			    working_dir[0] = working_dir[1];
			    working_dir[1] = ':';
		    	}
	    	    }
	    	    char* ldpath = concat_names( "-L'", working_dir );
	    	    ldpath = concat_names( ldpath, "'" );
		    (*p_ipa_add_link_flag) (ldpath);
	       }
	       
	       char* ldname = concat_names( "-l", string );
	       (*p_ipa_add_link_flag) (ldname);	  
	       
	       continue;     
    	   }else if( strncmp( string, "-L", 2 ) == 0 ){
	    	 if( strchr( string, ' ' ) != NULL && strchr( string, '\"') == NULL ){
		     // Add ''
		     char* ext = string + 2;
		     char* ldpath = concat_names( "-L'", ext );
	    	    ldpath = concat_names( ldpath, "'" );
		    (*p_ipa_add_link_flag) (ldpath);
		    
		    continue;		     
	    	 }
    	   }
	}
#endif	
	
#ifdef KEY
	// Since we perform the final link in the ipa temp dir, get files from
	// the temp dir's parent.  Bug 6029.
	if (argv[i][0] != '-') {
	  (*p_ipa_add_link_flag)
	    ((*p_ipa_add_parent_dir_to_relative_pathname)(argv[i]));
	  continue;
	}
#endif

    	(*p_ipa_add_link_flag) (argv[i]);


    }	    /* for */
   
#ifdef __CYGWIN__
    if( seeit == FALSE ){
	    outfilename = MALLOC(7);	
	    MALLOC_ASSERT(outfilename);
	    strcpy(outfilename,"");
	    strcat(outfilename,"a.exe");
	    (*p_ipa_add_link_flag) ("-o a.exe");
    }
    
    // Setup ABSOFT/bin Path
    char *absoft_path;
    if ((absoft_path = getenv("ABSOFT")) != NULL) {    
	 absoft_path = concat_names ( absoft_path, "/bin");
	 if( strlen( absoft_path ) > 2 ){
	     if( absoft_path[1] == ':' ){
		 // convert to /cygdrive/..."
		 absoft_path[1] = NULL;
		 strlwr( absoft_path );
		 absoft_path[1] = '/';
		 absoft_path = concat_names( "/cygdrive/", absoft_path );
	     }
	 }	 
    }else{
	 absoft_path = concat_names ( "/cygdrive/c/absoft/bin", "" );
    }
    char *old_path;
    char *new_path;
    old_path = getenv("PATH");
/*    new_path = malloc( strlen(old_path) + strlen( absoft_path ) + 2 );*/
    new_path = concat_names( absoft_path, ":" );
    new_path = concat_names( new_path, old_path );
    setenv( "PATH", new_path, TRUE );
    
#endif

    return(TRUE);
}

	/*******************************************************
		Function: 

		

	 *******************************************************/

	/*******************************************************
		Function: 

		

	 *******************************************************/












