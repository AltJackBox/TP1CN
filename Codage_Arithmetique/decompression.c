#include <stdio.h>
#include <stdlib.h>
#include "codage.h"

int main (int argc, char * argv[]){

    if (argc == 4){

        char * nom_fichier = argv[1]; // Table des symboles
        float vmess_entree;
        int  nb_mess;
        sscanf(argv[2], "%f", &vmess_entree); // Vmessage donné par l'utilisateur
        sscanf(argv[3], "%d", &nb_mess); // Nombre de lettres du message

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

            char* chaine = decompression(symboles, intervalles, probas, vmess_entree, nb_symb, nb_mess);

            printf("\n");
            printf("Resultat de la decompression du message : %s\n", chaine);
            printf("\n");

            free(chaine);
            free(symboles);
            free(probas);
            free(intervalles);
        }
        return 1;

    }else{
        printf("Nombre incorrect d'arguments\n");
        printf("Entrez le fichier contenant la table de symboles, le vmess et le nombre de symboles du message à décompresser\n");
        printf("Exemple : ./test_decompression table_symboles.txt 0.171875 4\n");
        return 0;
    }
}