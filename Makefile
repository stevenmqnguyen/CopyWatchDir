 # Filename	Makefile
 # Date 	May 6, 2021
 # Author	Steven Nguyen
 # Email	steven.nguyen@utdallas.edu
 # Course	CS 3377.0W5 Spring 2021
 # Version 	1.0
 # Copyright	2021, All Rights Reserved
 #
 # Description
 # 	Makefile which includes magic to auto fetch dependencies and build.



# The compiler to use
CXX = g++

# C pre-processor flags
CPPFLAGS = -I ~/include

# compiler flags
CXXFLAGS = -Werror -Wall

# linker flags
LDFLAGS = -static -L /home/013/s/sq/sqn170000/lib

LDLIBS = -l rudeconfig

# Project name.  This is used in building the file name for the backup target
PROJECTNAME = 6_assign

# Enter the name for the executable to be created
EXEC = a.out

# ======================================================
SRCS = $(wildcard *.cc)
HEADERS = $(wildcard *.h)
OBJS := $(patsubst %.cc,%.o,$(SRCS))

.PHONY: all clean backup


all: $(EXEC)


clean:
	rm -f $(OBJS) *.d *~ $(EXEC)


%.d:%.cc
	@echo Updating .d Dependency File
	@set -e; rm -f $@; \
	$(CXX) -MM $(CPPFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$



$(EXEC): $(OBJS)
	$(CXX) -static -o $(EXEC) $(OBJS) $(LDFLAGS) $(LDLIBS)


Makefile: $(SRCS:.cc=.d)


backup:	clean
	@mkdir -p ~/backups; chmod 700 ~/backups
	@$(eval CURDIRNAME := $(shell basename `pwd`))
	@$(eval MKBKUPNAME := ~/backups/$(PROJECTNAME)-$(shell date +'%Y.%m.%d-%H:%M:%S').tar.gz)
	@echo
	@echo Writing Backup file to: $(MKBKUPNAME)
	@echo
	@-tar zcfv $(MKBKUPNAME) ../$(CURDIRNAME)
	@chmod 600 $(MKBKUPNAME)
	@echo
	@echo Done!


-include $(SRCS:.cc=.d)

