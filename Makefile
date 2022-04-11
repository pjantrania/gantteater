# Makefile based on https://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/

CC=cc
CFLAGS=-I.
DEPS = printer.h chart.h
OBJ = printer.o main.o chart.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

gantteater: $(OBJ)
	mkdir -p out
	$(CC) -o out/$@ $^ $(CFLAGS)

clean:
	rm -rf *.o *~ out

