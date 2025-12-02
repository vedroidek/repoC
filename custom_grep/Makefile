CC = gcc
CFLAGS = -Wall -Wextra -std=c11
TARGET = file
OBJECTS = like_grep.o kmp.o

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

like_grep.o: like_grep.c kmp.h colors.h
	$(CC) $(CFLAGS) -c like_grep.c -o like_grep.o

kmp.o: kmp.c kmp.h
	$(CC) $(CFLAGS) -c kmp.c -o kmp.o

clean:
	rm -f $(TARGET) $(OBJECTS)


.PHONY: all clean