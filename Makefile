# Makefile based on https://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/


#############################################
## Parameter definitions                   ##
## These definitions make it easier to     ##
## change settings for the compiler and    ##
## build process in the makefile rules.    ##
#############################################

## `CC` and `CFLAGS` are variables so that
## you can change compiler & compiler flags
## for multiple Makefile rules efficiently.
CC=cc

## -I. adds the current directory (.) to the
## list of paths the compiler should look in
## to find dependencies (header files).
CFLAGS=-I.

## DEPS is a list of header (.h) files that
## require compilation before compiling the
## main executable.
DEPS = printer.h

## OBJ is a list of .o files that should
## be linked together to make the main
## executable.
OBJ = printer.o main.o



#############################################
##  Make targets                           ##
#############################################

## This rule tells the compiler how to build
## the intermediate object (.o) files out of
## the source (.c) files. The rule says that
## if you need any .o file (%.o), you need to
## run the following compiler command. The right
## side of the rule says that we need to rebuild
## an .o file if the corresponding .c file or
## any of the .h files change since last build.
## Here are what the special variables mean:
#### $@: replaced with the name from the left
####     side of the rule, before the ':'
####     (e.g. `module.o`).
#### $<: replaced with the first item on the
####     right side of the rule (`module.c`).
%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

## This rule gives the process to build the
## final executable (named `gantteater`).
## It says that if any .o file changes, we
## should rebuid the executable. It should
## be the default command run when you
## run `make` without an argument.
## Special variables:
#### $@: replaced with left side of the rule
####     (in this case, 'gantteater').
#### $^: replaced with the right hand side
####     of the rule, i.e. the list of .o files.
gantteater: $(OBJ)
	mkdir -p out
	$(CC) -o out/$@ $^ $(CFLAGS)

## This rule describes how to remove
## the files created by the build process,
## including the intermediate .o files,
## backup files (ending in ~), and the
## build output directory.
clean:
	rm -rf *.o *~ out

