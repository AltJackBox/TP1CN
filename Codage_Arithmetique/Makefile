CC = gcc
CFLAGS = -Wall -Werror
SRC = $(wildcard *.c)
HDR = $(wildcard *.h)
OBJECTS = $(patsubst %.c, %.o, $(wildcard *.c))
RM = rm -f

all: test_compression test_decompression

codage_arithmetique.o: codage_arithmetique.c codage.h 
	$(CC) $(CFLAGS) -c -g codage_arithmetique.c

compression.o: compression.c codage.h
	$(CC) $(CFLAGS) -c -g compression.c

decompression.o: decompression.c codage.h
	$(CC) $(CFLAGS) -c -g decompression.c

test_compression: compression.o codage_arithmetique.o
	$(CC) -o test_compression codage_arithmetique.o compression.o

test_decompression: decompression.o codage_arithmetique.o
	$(CC) -o test_decompression codage_arithmetique.o decompression.o

.PHONY: clean

clean:
	$(RM) $(OBJECTS) test_compression test_decompression