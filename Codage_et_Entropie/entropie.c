#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main (int argc, char **argv) {
    if (argc != 2) {
        printf("Err :\n./entropie <fihier de donnees>\n");
        return 1;
    }

    FILE *f = fopen(argv[1],"r");
    if (f == NULL) {
        printf("Err :\nImpossible d'ouvrir le fichier\n");
        return 2;
    }
    int taille;
    fscanf(f,"%d\n",&taille);
    double resultat;

    for (int i=0; i<taille; i++) {
        double prob;
        fscanf(f,"%lf\n",&prob);
        resultat += prob * log(prob) / log(2);
    }
    fclose(f);
    printf("H(X) = %lf\n",-resultat);
}
