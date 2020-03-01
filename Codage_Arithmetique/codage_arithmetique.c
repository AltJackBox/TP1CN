#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "codage.h"

// message : message à coder
// symboles : tableau contenant la liste des symboles présents dans le message
// intervalles : tableau qui contient dans l'ordre croissant les bornes des intervalles correspondant aux symboles
// nb_symb : nombre de symboles différents dans la table

float compression(char* message, char* symboles, float* intervalles, int nb_symb){

    float binf = 0.0;
    float bsup = 1.0;
    float vmess = 1.0;
    float vecart = 1.0;

    int taille_message = strlen(message);

    for (int i = 0; i< taille_message; i++){
        char caractere = message[i];
        int index = retrouve_index(symboles, nb_symb, caractere);
        bsup = binf + vecart * intervalles[index+1]; // bsup = binf + vecart * bsup du symbole
        binf = binf + vecart * intervalles[index]; // binf = binf + vecart * binf du symbole
        vmess = (bsup + binf) / 2.0;
        vecart = bsup - binf;
    }
    return vmess;
}

// symboles : tableau contenant la liste des symboles présents dans le message
// intervalles : tableau qui contient dans l'ordre croissant les bornes des intervalles correspondant aux symboles
// probas : tableau contenant les probabilités d'apparition des différents symboles de la table
// nb_symb : nombre de symboles différents dans la table
// nb_mess : nombre de lettres dans le message 

char* decompression(char* symboles, float* intervalles, float* probas, float vmess_entree, int nb_symb, int nb_mess){
    char* chaine = malloc(sizeof(char)*nb_mess);
    float vmess = vmess_entree;
    int indice_lettre = retrouve_lettre(vmess, symboles, intervalles, nb_symb);
    chaine[0] = symboles[indice_lettre];

    for (int i=1; i<nb_mess; i++){
        vmess = (vmess - intervalles[indice_lettre]) / probas[indice_lettre]; 
        indice_lettre = retrouve_lettre(vmess, symboles, intervalles, nb_symb);
        chaine[i] = symboles[indice_lettre];
    }
    return chaine;
}



// Permet de retrouver l'indice qui correspond au caractère dans le tableau des symboles
// on peut par la suite retrouver les intervalles et les informations nécessaires
// à la poursuite de l'algorithme dans les autres tableaux grâçe à l'indice renvoyé

int retrouve_index(char* symboles, int nb_symb, char caractere){ 
    int index = 0;
    while ((index < nb_symb) && (caractere != symboles[index])){
        index++;
    }
    return index;
}

// On retrouve dans quel intervalle Vmess est inclus
// A partir de l'indice du tableau dans intervalles, on peut retrouver la lettre 
// Dans le tableau symboles

int retrouve_lettre(float Vmess, char* symboles, float* intervalles, int nb_symb){
    int index = 0;
    while ((index < nb_symb) && (Vmess > intervalles[index+1])){
        index++;
    }
    return index;
}