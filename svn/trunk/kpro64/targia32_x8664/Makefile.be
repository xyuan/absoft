###############################################################################
#
# macros
#
###############################################################################

ifeq ($(ABSOFT),"")
ABSOFT=~/absoft
ABS_WARNING=1
endif

ifeq ($(PRODUCTION),1)
OPT=
VAR=
SUFX=
else
OPT=BUILD_OPTIMIZE=DEBUG
ifdef APPLE
VAR=OPTIMIZER=-gdwarf-2
else
VAR=OPTIMIZER=-g
endif
SUFX=_x
endif
#OPTS+=-v

ifeq ($(CYGWIN),1)
OPT+= CYGWIN=1 ABSOFT_FC=1 BUILD_TARGET=X64
endif

ifeq ($(BUILD_COMPILER),"ACC")
COMPILER=BUILD_COMPILER=ACC
endif

ifeq ($(BUILD_COMPILER),"PSC)
COMPILER=BUILD_COMPILER=PSC PSC_ROOT_PREFIX=$PATHSCALE PSC_NAME_PREFIX=path
endif

ifdef APPLE
BE_OPTS+= BUILD_VARIANT=BEDRIVER
endif


ifdef CYGWIN
NEED_ANL=1
NEED_WHIRL=1
endif

ifdef APPLE
NEED_ANL=1
NEED_WHIRL=1
endif

###############################################################################
#
# build rules
#
###############################################################################
.PHONY: setup build_libunwindP build_cg build_be_so build_wopt build_lno build_anl build_prp build_whirl build_be build_targinfo

default: setup build_libunwindP build_cg build_be_so build_wopt build_lno build_anl build_prp build_whirl build_be build_targinfo



setup:
	@echo "##########***** making be *****##########"
ifeq ($(PRODUCTION),1)
	@echo "PRODUCTION=RELEASE"
else
	@echo "PRODUCTION=DEBUG"
endif
ifeq ($(ABS_WARNING),1)
	@echo "### WARNING: ABSOFT set to ~/absoft for Makefile.be"
endif
	mkdir -p $(ABSOFT)/shlib;
	mkdir -p $(ABSOFT)/bin;



build_libunwindP:
	#ifeq ($(BUILD_COMPILER),"ACC")
	#	export LD_LIBRARY_PATH=$(ABSOFT)/shlib:$(ABSOFT)/shlib64; \
	#endif
	#ifeq ($(BUILD_COMPILER),"PSC")
	#	export LD_LIBRARY_PATH=$(PATHSCALE)/lib/2.2.1:$(PATHSCALE)/lib/2.2.1/32; \
	#endif
	@echo "##########***** making libunwindP *****##########"
	#@echo $(COMPILER)
	# NOTE: fails for BUILD_VARIANT=NODEBUG
	cd libunwindP; \
	$(MAKE) V=1 $(OPT) $(VAR) ABSOFT_EXTENSIONS=1 $(COMPILER) ; \
	cd ..


build_cg:
	@echo "##########***** making cg base *****##########"
	cd cg; \
	$(MAKE) V=1 $(OPT) $(VAR) ABSOFT_EXTENSIONS=1 $(COMPILER) ; \
	echo "##########***** making cg.so *****##########"; \
	$(MAKE) V=1 $(OPT) $(VAR) ABSOFT_EXTENSIONS=1 cg.so $(COMPILER) ; \
	cp -f cg.so $(ABSOFT)/shlib/; \
	cd ..
	cd targ_info; cp -f opteron.so em64t.so core.so barcelona.so wolfdale.so $(ABSOFT)/shlib/;

build_be_so:
	@echo "##########***** making be.so *****##########"
	cd be; \
	$(MAKE) V=1 $(OPT) $(VAR) ABSOFT_EXTENSIONS=1 be.so $(COMPILER) ; \
	cd ../wopt; \
	ln -s ../be/be.so be.so; \
	ln -s ../targ_info/opteron.so opteron.so; \
	cd ..

build_wopt: build_be_so
	@echo "##########***** making wopt.so *****##########"
	# cd ../wopt
	cd wopt; \
	$(MAKE) V=1 $(OPT) $(VAR) ABSOFT_EXTENSIONS=1 wopt.so $(COMPILER) ; \
	cp -f wopt.so $(ABSOFT)/shlib/; \
	cd ..

build_lno:
	@echo "##########***** making lno.so *****##########"
	cd ipl; \
	$(MAKE) $(OPT) $(VAR) V=1 ABSOFT_EXTENSIONS=1 $(COMPILER) ; \
	cp -f ipl.so $(ABSOFT)/shlib/.; \
	cd ..
	cd lno; \
	$(MAKE) V=1 $(OPT) $(VAR) ABSOFT_EXTENSIONS=1 lno.so $(COMPILER) ; \
	cp -f lno.so $(ABSOFT)/shlib/; \
	cd ..

build_anl:
ifdef NEED_ANL 
	@echo "##########***** making anl.so *****##########"
	cd anl; \
	$(MAKE) $(OPT) $(VAR) V=1 ABSOFT_EXTENSIONS=1 $(COMPILER) ; \
	cp -f anl.so $(ABSOFT)/shlib/.; \
	cd ..
endif

build_prp:
ifdef CYGWIN
	@echo "##########***** making prp.so *****##########"
	cd prp; \
	$(MAKE) $(OPT) $(VAR) V=1 ABSOFT_EXTENSIONS=1 $(COMPILER) ; \
	cp -f prp.so $(ABSOFT)/shlib/.; \
	cd ..
endif

build_whirl:
ifdef NEED_WHIRL 
	@echo "##########***** making whirl2c.so *****##########"
	cd whirl2c; \
	$(MAKE) $(OPT) $(VAR) V=1 ABSOFT_EXTENSIONS=1 $(COMPILER) ; \
	cd ..
	@echo "##########***** making whirl2f.so *****##########"
	cd whirl2f; \
	$(MAKE) $(OPT) $(VAR) V=1 ABSOFT_EXTENSIONS=1 $(COMPILER) ; \
	cd ..
	@echo "##########***** making ir_b2a *****##########"
ifeq ($(PRODUCTION),1)
else
	cd ir_tools; \
	$(MAKE) $(OPT) $(VAR) V=1 ABSOFT_EXTENSIONS=1 $(COMPILER) ; \
	cp ir_b2a  $(ABSOFT)/bin/; \
	cd ..
	cp whirl2c/whirl2c.so $(ABSOFT)/shlib/; 
	cp whirl2f/whirl2f.so $(ABSOFT)/shlib/;
endif
endif

build_be:
	@echo "##########***** making be *****##########"
	cd be; \
	$(MAKE) V=1 $(OPT) $(VAR) ABSOFT_EXTENSIONS=1 $(BE_OPTS) $(COMPILER) ; \
	cp -f be.so $(ABSOFT)/shlib/; \
	cp -f be $(ABSOFT)/bin/be$(SUFX); \
	cd ..

build_targinfo:
ifndef APPLE
	cp -f targ_info/em64t.so $(ABSOFT)/shlib/
endif






###############################################################################
#
# clobber
#
###############################################################################

.PHONY: clobber_libunwindP clobber_cg clobber_be_so clobber_wopt clobber_lno clobber_anl clobber_prp clobber_whirl clobber_be clobber_targinfo

clobber: clobber_libunwindP clobber_cg clobber_be_so clobber_wopt clobber_lno clobber_anl clobber_prp clobber_whril clobber_be clobber_targinfo
	cd include; $(MAKE) clobber;


clobber_libunwindP:
	cd libunwindP; $(MAKE) clobber;

clobber_cg:
	cd cg; $(MAKE) clobber;

clobber_be_so: clobber_be

clobber_wopt:
	cd wopt; $(MAKE) clobber;

clobber_lno:
	cd lno; $(MAKE) clobber;

clobber_anl:
ifdef NEED_ANL 
	cd anl; $(MAKE) clobber;
endif

clobber_prp:
ifdef CYGWIN
	cd prp; $(MAKE) clobber;
endif

clobber_whril:
ifdef CYGWIN
	cd whirl2c; $(MAKE) clobber;
	cd whirl2f; $(MAKE) clobber;
endif

clobber_be:
	cd be; $(MAKE) clobber;

clobber_targinfo:
	cd targ_info; $(MAKE) clobber;







###############################################################################
#
# clean
#
###############################################################################

.PHONY: clean_libunwindP clean_cg clean_be_so clean_wopt clean_lno clean_anl clean_prp clean_whirl clean_be clean_targinfo

clean: clean_libunwindP clean_cg clean_be_so clean_wopt clean_lno clean_anl clean_prp clean_whirl clean_be clean_targinfo


clean_libunwindP:
	cd libunwindP; $(MAKE) clean;

clean_cg:
	cd cg; $(MAKE) clean;

clean_be_so: clean_be

clean_wopt:
	cd wopt; $(MAKE) clean;

clean_lno:
	cd lno; $(MAKE) clean;

clean_anl:
ifdef NEED_ANL
	cd anl; $(MAKE) clean;
endif

clean_prp:
ifdef CYGWIN
	cd prp; $(MAKE) clean;
endif

clean_whril:
ifdef CYGWIN
	cd whirl2c; $(MAKE) clean;
	cd whirl2f; $(MAKE) clean;
endif

clean_be:
	cd be; $(MAKE) clean;

clean_targinfo:
	cd targ_info; $(MAKE) clean;



