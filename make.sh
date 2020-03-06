#!/bin/sh

if [ $1 = 'all' ]
then
	cd ~/Documents/Polytech/Semestre6/CN/TP1CN/Codage_et_Entropie
	make
	cd ../Code_de_Huffman
	make
	cd ../Codage_Arithmetique
	make
elif [ $1 = 'clean' ]
then
	cd ~/Documents/Polytech/Semestre6/CN/TP1CN/Codage_et_Entropie
	make clean
	cd ../Code_de_Huffman
	make clean
	cd ../Codage_Arithmetique
	make clean
else
	echo "./make.sh <all/clean>"
fi
