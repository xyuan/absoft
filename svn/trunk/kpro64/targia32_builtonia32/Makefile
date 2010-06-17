INCLUDE_SUBDIRS := include

ifdef WITH_PATHF90
LIBRARY_SUBDIRS := libfortran libu
endif

LIBRARY_SUBDIRS += libelf libdwarf libmv libinstr2

SUBDIRS := $(INCLUDE_SUBDIRS) $(LIBRARY_SUBDIRS)

default clean clobber:
	@for DIR in $(SUBDIRS); do if ! $(MAKE) -C $$DIR $@; then exit; fi; done
