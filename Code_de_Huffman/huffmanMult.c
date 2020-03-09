#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "fapMult.h"
#include "arbrebinMult.h"

struct code_char {
    char *str;
    double prob;
    int lg;
    int code[256]; /* ne contient que des 0 ou des 1 */
};

typedef struct {
    char *str;
    double prob;
} case_prob;

typedef struct {
    int size;
    case_prob *tab;
} TableOcc_t;

struct code_char *HuffmanCode;
int position = 0;

void ConstruireTableOcc(FILE *fichier, TableOcc_t *TableOcc) {

    int taille;
    fscanf(fichier,"%d\n",&taille);
    TableOcc->size = taille;
    TableOcc->tab = (case_prob *)malloc(sizeof(case_prob)*taille);

    for (int i=0; i<taille; i++) {
        char c;
        double prob;
        fscanf(fichier,"%c",&c);
        fscanf(fichier," %lf\n",&prob);
        TableOcc->tab[i].str = (char *)malloc(2);
        TableOcc->tab[i].str[0] = c;
        TableOcc->tab[i].str[1] = '\0';
        TableOcc->tab[i].prob = prob;
    }
}

void incrTab(int *compteur, int taille, int tailleTot) {
    if (taille > 0) {
        // printf(" %d ",compteur[taille-1]);
        compteur[taille-1]++;
        if (compteur[taille-1] == tailleTot) {
            compteur[taille-1] = 0;
            incrTab(compteur,taille-1, tailleTot);
        }
    }
}

void TableOccEvenementN(TableOcc_t *TableOcc, TableOcc_t *new, int n) {

    new->size = pow(TableOcc->size,n);
    new->tab = (case_prob *)malloc(sizeof(case_prob)*new->size);

    int compteur[n];
    for (int i=0; i<n; i++) {
        compteur[i] = 0;
    }

    for (int i=0; i<new->size; i++) {
        new->tab[i].str = (char *)malloc(n);
        new->tab[i].prob = 1;
        int j=0;
        for (; j<n; j++) {
            new->tab[i].str[j] = TableOcc->tab[compteur[j]].str[0];
            new->tab[i].prob = new->tab[i].prob * TableOcc->tab[compteur[j]].prob;
        }
        new->tab[i].str[j] = '\0';
        incrTab(compteur,n,TableOcc->size);
        // printf("\n");
    }
}

void AfficherTableOcc(TableOcc_t TableOcc) {
    for (int i=0; i<TableOcc.size; i++) {
        printf("%s : %lf\n",TableOcc.tab[i].str,TableOcc.tab[i].prob);
    }
}

fap InitHuffman(TableOcc_t *TableOcc) {
    fap file = creer_fap_vide();
    for (int i=0; i<TableOcc->size; i++) {
        Arbre a = ArbreVide();
        a = NouveauNoeud(ArbreVide(),TableOcc->tab[i].str,TableOcc->tab[i].prob,ArbreVide());
        file = inserer(file,a,TableOcc->tab[i].prob);
    }
    return file;
}

Arbre ConstruireArbre(fap file) {
    Arbre x,y,r;
    double px,py;
    file = extraire(file, &x, &px);
    while (!est_fap_vide(file)) {
        file = extraire(file, &y, &py);
        r = NouveauNoeud(x,"*",0,y);
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
        c.str = Etiq(huff);
        c.prob = probElem(huff);
        HuffmanCode[position] = c;
        position++;
    }

}

void ConstruireCode(Arbre huff, int size) {
    HuffmanCode = (struct code_char *)malloc(sizeof(struct code_char)*size);
    for (int i=0; i<size; i++) {
        HuffmanCode[i].lg = 0;
    }
    struct code_char c;
    c.lg = 0;
    worker(huff,c);
}

void AfficherCode() {
    for (int i=0; i<position; i++) {
            printf("%s : ",HuffmanCode[i].str);
            for (int j=0; j<HuffmanCode[i].lg; j++) {
                printf("%d",HuffmanCode[i].code[j]);
            }
            printf("\n");
    }
}

int equals(char *str1, char *str2) {
    int i=0;
    while (str1[i]!='\0' && str2[i]!='\0') {
        if (str1[i] != str2[i]) {
            return 0;
        }
        i++;
    }
    return 1;
}

double longueurMoyenne(int n) {
    double res = 0;
    for (int i=0; i<position; i++) {
        res += HuffmanCode[i].prob * HuffmanCode[i].lg / n;
    }
    return res;
}


int main (int argc, char **argv) {
    if (argc != 3) {
        printf("Err :\n./huffman <fichier de donnees> <taille evenements>\n");
        return 1;
    }

    FILE *fichier = fopen(argv[1], "r");
    if (fichier == NULL) {
        printf("Err :\nImpossible d'ouvrir le fichier\n");
        return 2;
    }
    int tailleEv = atoi(argv[2]);

    TableOcc_t TableOcc;
    /* Construire la table d'occurences */
    ConstruireTableOcc(fichier, &TableOcc);
    fclose(fichier);

    TableOcc_t new;

    printf("Construction du tableau d'occurences : ...\n");
    TableOccEvenementN(&TableOcc, &new, tailleEv);
    // AfficherTableOcc(TableOcc);
    // AfficherTableOcc(new);
    /* Initialiser la FAP */
    fap file = InitHuffman(&new);

    /* Construire l'arbre d'Huffman */
    printf("Construction de l'arbre de Huffman : ...\n");
    Arbre ArbreHuffman = ConstruireArbre(file);

    // AfficherArbre(ArbreHuffman);

    /* Construire la table de codage */
    printf("Construction code de Huffman : ...\n");
    ConstruireCode(ArbreHuffman,new.size);
    // AfficherCode();

    printf("Calcul de la longueur moyenne : ...\n");
    printf("\nLongueur moyenne : %.3lf\n",longueurMoyenne(tailleEv));

    /* Encodage */
    // fichier = fopen(argv[1], "r");
    //
    // fclose(fichier);

    return 0;

}
