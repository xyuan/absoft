ifeq ($(NO_TARG),1)
else
INCLUDE_SUBDIRS := include targ_info
endif

ifdef WITH_PATHF90
LIBRARY_SUBDIRS := arith libcif libcomutil libu libfortran
endif

LIBRARY_SUBDIRS += libcmplrs libelf libdwarf libelfutil libunwindP

ifdef WITH_PATHF90
TOOL_SUBDIRS := crayf90
endif

ifeq ($(CYGWIN),1)
TOOL_SUBDIRS +=	be cg driver ipa ipl lno wopt lw_inline anl prp ir_tools whirl2c whirl2f be_driver crayf90 
else
TOOL_SUBDIRS +=	be cg driver g++fe gccfe ipa ipl ir_tools lno lw_inline whirl2c whirl2f wopt be_driver
endif

ifeq ($(CYGWIN),1)
SUBDIRS := $(INCLUDE_SUBDIRS) $(TOOL_SUBDIRS)
else
SUBDIRS := $(INCLUDE_SUBDIRS) $(LIBRARY_SUBDIRS) $(TOOL_SUBDIRS)
endif

default clean clobber:
	@for DIR in $(SUBDIRS); do if ! $(MAKE) -C $$DIR $@; then exit; fi; done
