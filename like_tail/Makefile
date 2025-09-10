CC = gcc
STD = c11
CFLAGS = -Wall
GDB = -g
SETSTD = -std=$(STD)

.PHONY: clean all

# target
all: file

file: my_tl.o
	$(CC) my_tl.o -o file

my_tl.o: my_tl.c
	$(CC) $(GDB) $(SETSTD) $(CFLAGS) -c my_tl.c -o my_tl.o -lc

clean:
	rm -f *.o file
