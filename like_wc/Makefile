CC = gcc
STD = c11
CFLAGS = -Wall
GDB = -g
SETSTD = -std=$(STD)

.PHONY: clean all

# target
all: file

file: my_wc.o
	$(CC) my_wc.o -o file

my_wc.o: my_wc.c
	$(CC) $(GDB) $(SETSTD) $(CFLAGS) -I.colors.h -c my_wc.c -o my_wc.o -lc

clean:
	rm -f *.o file
