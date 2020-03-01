#include <stdio.h>
#include <stdlib.h>
#include "codage.h"

int main (int argc, char * argv[]){

    if (argc == 3){

        char * nom_fichier = argv[1]; // Table des symboles
        char * message = argv[2]; // Mot à compresser

        FILE* fichier = NULL; 
        fichier = fopen(nom_fichier, "r");

        if (fichier != NULL){

            int nb_symb;
            fscanf(fichier, "%d\n", &nb_symb);
            
            char *symboles = malloc(sizeof(char)*(nb_symb));
            float *probas = malloc(sizeof(float)*(nb_symb));
            float *intervalles = malloc(sizeof(float)*(nb_symb+1));
            int i = 0;

            do
            {
                fscanf(fichier, "%c %f %f %f\n", &symboles[i], &probas[i], &intervalles[i], &intervalles[i+1]);
                i++;
                
            } while (i != nb_symb);

            float vmess = compression(message, symboles, intervalles, nb_symb);

            printf("\n");
            printf("Resultat de la compression du message : Vmess = %f\n", vmess);
            printf("\n");

            free(symboles);
            free(probas);
            free(intervalles);
        }
        return 1;

    }else{
        printf("\n");
        printf("Nombre incorrect d'arguments\n");
        printf("Entrez le fichier contenant la table de symboles et le message à coder\n");
        printf("Exemple : ./essai_codage table_symboles.txt KIWI\n");
        printf("\n");
        return 0;
    }
}