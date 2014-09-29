BASE = /home/parallels/git/optpls
WISH = /usr/bin/wish


#### You probably don't need to change anything down here ###

A_APG = $(BASE)/search
A_OPT = $(BASE)/sampleopt
A_QUERY = $(BASE)/parser
A_TCL = $(BASE)/tclstuff

CC = g++ $(CPPFLAGS)
INCLUDES = -I$(A_APG) -I$(A_OPT) -I$(A_QUERY)
CPPFLAGS = -g $(INCLUDES) 
MAKE_DEPEND_FILE = Makefile.depend
MAKECMD = $(MAKE) 
TAGS = etags --c++ 
AR = ar
ARFLAGS = ruv
RANLIB = ranlib
LIB_QPROC = $(BASE)/libqproc.a

MAKE_DEPEND_COMMAND = $(CC) $(CFLAGS) -M $(SRCS) > $(MAKE_DEPEND_FILE)

