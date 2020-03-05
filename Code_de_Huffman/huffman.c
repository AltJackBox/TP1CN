#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "fap.h"
#include "arbrebin.h"

struct code_char {
    int lg;
    int code[256]; /* ne contient que des 0 ou des 1 */
};

typedef struct {
    double tab[256];
} TableOcc_t;

struct code_char HuffmanCode[256];

void ConstruireTableOcc(FILE *fichier, TableOcc_t *TableOcc) {

    for (int i=0; i<256; i++) {
        TableOcc->tab[i]=0;
    }

    int taille;
    fscanf(fichier,"%d\n",&taille);
    for (int i=0; i<taille; i++) {
        char c;
        fscanf(fichier,"%c",&c);
        fscanf(fichier," %lf\n",TableOcc->tab+c);
    }
}

fap InitHuffman(TableOcc_t *TableOcc) {
    fap file = creer_fap_vide();
    for (int i=0; i<256; i++) {
        Arbre a = ArbreVide();
        if (TableOcc->tab[i] != 0) {
            a = NouveauNoeud(ArbreVide(),(unsigned char)i,ArbreVide());
            file = inserer(file,a,TableOcc->tab[i]);
        }
    }
    return file;
}

Arbre ConstruireArbre(fap file) {
    Arbre x,y,r;
    double px,py;
    file = extraire(file, &x, &px);
    while (!est_fap_vide(file)) {
        file = extraire(file, &y, &py);
        r = NouveauNoeud(x,'*',y);
        file = inserer(file,r,px+py);
        file = extraire(file, &x, &px);
    }
    return x;
}

void worker(Arbre huff, struct code_char c) {
    if (!EstVide(FilsGauche(huff)) && !EstVide(FilsDroit(huff))) {
        c.code[c.lg] = 0;
        c.lg++;
        worker(FilsGauche(huff), c);
        c.code[c.lg-1] = 1;
        worker(FilsDroit(huff), c);
    } else {
        HuffmanCode[Etiq(huff)] = c;
    }

}

void ConstruireCode(Arbre huff) {
    for (int i=0; i<256; i++) {
        HuffmanCode[i].lg = 0;
    }
    struct code_char c;
    c.lg = 0;
    worker(huff,c);
}

void AfficherCode() {
    for (int i=0; i<256; i++) {
        if (HuffmanCode[i].lg > 0) {
            printf("%c : ",(char)i);
            for (int j=0; j<HuffmanCode[i].lg; j++) {
                printf("%d",HuffmanCode[i].code[j]);
            }
            printf("\n");
        }
    }
}

double longueurMoyenne(TableOcc_t TableOcc) {
    double res = 0;
    for (int i=0; i<256; i++) {
        res += TableOcc.tab[i] * HuffmanCode[i].lg;
    }
    return res;
}


int main (int argc, char **argv) {
    if (argc != 2) {
        printf("Err :\n./huffman <fihier de donnees> \n");
        return 1;
    }

    FILE *fichier = fopen(argv[1], "r");
    if (fichier == NULL) {
        printf("Err :\nImpossible d'ouvrir le fichier\n");
        return 2;
    }

    TableOcc_t TableOcc;
    /* Construire la table d'occurences */
    ConstruireTableOcc(fichier, &TableOcc);
    fclose(fichier);

    /* Initialiser la FAP */
    fap file = InitHuffman(&TableOcc);

    /* Construire l'arbre d'Huffman */
    Arbre ArbreHuffman = ConstruireArbre(file);

    AfficherArbre(ArbreHuffman);
    printf("\n");

    /* Construire la table de codage */
    ConstruireCode(ArbreHuffman);
    AfficherCode();

    printf("\nLongueur moyenne : %.3lf\n",longueurMoyenne(TableOcc));

    /* Encodage */
    // fichier = fopen(argv[1], "r");
    //
    // fclose(fichier);

    return 0;

}
