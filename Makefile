# $Id$
#
# example module makefile
#
# 
# WARNING: do not run this directly, it should be run by the master Makefile

include ../../Makefile.defs
auto_gen=
NAME=msilo.so
LIBS+= -lpthread

include ../../Makefile.modules
