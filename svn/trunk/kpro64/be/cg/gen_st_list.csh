#!/bin/csh -f
### ======================================================================
### ======================================================================
###
### Module: gen_st_list.csh
### $Revision: 162 $
### $Date: 2005-08-09 15:23:30 -0400 (Tue, 09 Aug 2005) $
### $Author: aer $
### $Source$
### Revision history:
###   27-Feb-92 - Original version
###
### Usage:      gen_st_list MTP_BIN
###
###     Generate the st_list.[ch] module.  The argument is the MTP_BIN
###     directory.  We do this in a file so the make rule can depend on
###     and it can be rebuilt when the procedure changes
###
### ======================================================================
### ======================================================================



csh -f $1/gen_x_list.csh    'ST*'                                      \
                            'ST'                                       \
                            'defs.h'                                   \
			    'errors.h'				       \
                            'mempool.h'                                 \
                            'cgir.h'                                   \
                            'st_list.h'
