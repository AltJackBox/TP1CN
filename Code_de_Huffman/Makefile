all: huffman

GCC_OPT= -Wall

arbrebin.o: arbrebin.c
	gcc -Wall -c -o arbrebin.o arbrebin.c

fap.o: fap.c arbrebin.h
	gcc -Wall -c -o fap.o fap.c

huffman.o: huffman.c fap.h arbrebin.h
	gcc -Wall -c -o huffman.o huffman.c

huffman: huffman.o fap.o arbrebin.o
	gcc -lm -o huffman huffman.o fap.o arbrebin.o

clean:
	rm -f *.o huffman
