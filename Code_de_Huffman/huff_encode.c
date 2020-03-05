
#include "arbrebin.h"
#include "bfile.h"
#include "fap.h"
#include "huffman_code.h"
#include <assert.h>
#include <stdio.h>

typedef struct {
    int tab[256];
} TableOcc_t;

struct code_char HuffmanCode[256];

void ConstruireTableOcc(FILE *fichier, TableOcc_t *TableOcc) {

    int c;

    for (int i=0; i<256; i++) {
        TableOcc->tab[i]=0;
    }

    c = fgetc(fichier);
    while (c != EOF) {
        TableOcc->tab[c]++;
        c = fgetc(fichier);
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
    int px,py;
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
    struct code_char c;
    c.lg = 0;
    worker(huff,c);
}

void Encoder(FILE *fic_in, FILE *fic_out, Arbre ArbreHuffman) {
        EcrireArbre(fic_out,ArbreHuffman);
        int c;
        BFILE *f = bstart(fic_out,"w");

        c = fgetc(fic_in);
        while (c != EOF) {
            for (int i=0; i<HuffmanCode[c].lg; i++) {
                bitwrite(f, HuffmanCode[c].code[i]);
            }
            c = fgetc(fic_in);
        }
        bstop(f);
}

int main(int argc, char *argv[]) {

    TableOcc_t TableOcc;
    FILE *fichier;
    FILE *fichier_encode;

    fichier = fopen(argv[1], "r");
    /* Construire la table d'occurences */
    ConstruireTableOcc(fichier, &TableOcc);
    fclose(fichier);

    /* Initialiser la FAP */
    fap file = InitHuffman(&TableOcc);

    /* Construire l'arbre d'Huffman */
    Arbre ArbreHuffman = ConstruireArbre(file);

    AfficherArbre(ArbreHuffman);

    /* Construire la table de codage */
    ConstruireCode(ArbreHuffman);

    /* Encodage */
    fichier = fopen(argv[1], "r");
    fichier_encode = fopen(argv[2], "w");

    Encoder(fichier, fichier_encode, ArbreHuffman);

    fclose(fichier_encode);
    fclose(fichier);

    return 0;
}
