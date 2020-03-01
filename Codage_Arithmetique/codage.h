#ifndef _CODAGE_H_
#define _CODAGE_H_

float compression(char* message, char* symboles, float* intervalles, int nb_symb);
char* decompression(char* symboles, float* intervalles, float* probas, float vmess_entree, int nb_symb, int nb_mess);
int retrouve_index(char* symboles, int nb_symb, char caractere);
int retrouve_lettre(float Vmess, char* symboles, float* intervalles, int nb_symb);

#endif