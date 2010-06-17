# -*- Makefile -*-
#
#  Copyright (C) 2006 Absoft, Corp.  All Rights Reserved.
#
#  This program is free software; you can redistribute it and/or modify it
#  under the terms of version 2 of the GNU General Public License as
#  published by the Free Software Foundation.
#
#  This program is distributed in the hope that it would be useful, but
#  WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  
#
#  Further, this software is distributed without any warranty that it is
#  free of the rightful claim of any third person regarding infringement 
#  or the like.  Any license provided herein, whether implied or 
#  otherwise, applies only to this software file.  Patent licenses, if 
#  any, provided herein do not apply to combinations of this program with 
#  other software, or any other product whatsoever.  
#
#  You should have received a copy of the GNU General Public License along
#  with this program; if not, write the Free Software Foundation, Inc., 59
#  Temple Place - Suite 330, Boston MA 02111-1307, USA.
#
#  Contact information:  Absoft corp., 2781 Bond St,
#  Rochester Hills, MI 48309, or:
#
#  http://www.absoft.com
#
#

ifndef NOUPDATE
NOUPDATE=0
endif

ifeq ($(APPLE),1)
LDINTELLIBS = /opt/intel/fc/current/lib/libifcore.a /opt/intel/fc/current/lib/libimf.a /opt/intel/fc/current/lib/libirc.a
endif

ifeq ($(PRODUCTION),1)
TARGET=atmod
OPTS=-O2
else
TARGET=atmod_x
OPTS=-g
endif
LOPTS+= -Wl,-Y,100 
OPTS += #-v

ifdef CYGWIN
CATGETSLIB = -lcatgets
else
CATGETSLIB = -lgfecc
endif

default:
ifeq ($(NOUPDATE), 0)
	svn update
endif
	#./build

	gcc $(OPTS) -DKEY -D_TARGET_OS_LINUX -m32 -c -I$(ADEV_ROOT)/svn/pathscale-trunk/kpro64/common/com/ -I$(ADEV_ROOT)/svn/pathscale-trunk/kpro64/crayf90/fe90/ setup_reader.c
	gcc $(OPTS) -DKEY -D_TARGET_OS_LINUX -m32 -c -I$(ADEV_ROOT)/svn/pathscale-trunk/kpro64/crayf90/fe90/ PDGCS_reader.c
	g++ $(OPTS) $(LOPTS) -D_TARGET_OS_LINUX -m32 PDGCS_reader.o setup_reader.o $(ADEV_ROOT)/pathscale_libs/compiler_build_date.o -o $(TARGET) -L$(ADEV_ROOT)/pathscale_libs/ -lfe90_sgi -lcomutil $(CATGETSLIB) -ldwarf -lfe90_sgi -lfe90 $(CATGETSLIB) -larith -lcif -lm  -lfortran -lffio $(LDINTELLIBS)  #-L/usr/lib -lefence

	@echo cp -f $(TARGET) $(ABSOFT)/bin
	cp -f $(TARGET) $(ABSOFT)/bin/


clobber: clean

clean:
	rm -rf $(TARGET) *.o


