all: huffman huffmanMult

GCC_OPT= -Wall

arbrebin.o: arbrebin.c
	gcc -Wall -c -o arbrebin.o arbrebin.c

fap.o: fap.c arbrebin.h
	gcc -Wall -c -o fap.o fap.c

huffman.o: huffman.c fap.h arbrebin.h
	gcc -Wall -c -o huffman.o huffman.c

huffman: huffman.o fap.o arbrebin.o
	gcc -lm -o huffman huffman.o fap.o arbrebin.o

arbrebinMult.o: arbrebinMult.c
	gcc -Wall -c -o arbrebinMult.o arbrebinMult.c

fapMult.o: fapMult.c arbrebinMult.h
	gcc -Wall -c -o fapMult.o fapMult.c

huffmanMult.o: huffmanMult.c fapMult.h arbrebinMult.h
	gcc -Wall -c -o huffmanMult.o huffmanMult.c

huffmanMult: huffmanMult.o fapMult.o arbrebinMult.o
	gcc -lm -o huffmanMult huffmanMult.o fapMult.o arbrebinMult.o

clean:
	rm -f *.o huffman huffmanMult
