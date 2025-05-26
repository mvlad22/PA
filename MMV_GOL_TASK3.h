#ifndef MMV_GOL_TASK3_H
#define MMV_GOL_TASK3_H
#include <stdio.h>
#include <stdlib.h>
#include "MMV_GOL_TASK1.h"  //pentru functia de cautat + numarat vecinii unei celule din grila
#include "MMV_GOL_TASK2.h"  //Utilizez structura si functiile pentru liste, 
                            //intrucat continutul fiecarui nod de arbore este o lista de celule.
                            //Celule sunt reprezentate prin coordonatele lor in grila

struct arbore
{
    Celula *data;
    struct arbore *left;    //pentru regula B
    struct arbore *right;   //pentru setul original de reguli
};
typedef struct arbore nod_arbore;


int gaseste_vecini_T3(char * grila, int i, int j, int n, int m);
void afisare_grila_T3(FILE * fis_out, char * grila, int nr_linii, int nr_coloane, int NR_TASK);

void construire_arbore(nod_arbore **root, char* grila_principala, int nivel, int adancime, int nr_linii, int nr_coloane);

char *copiaza_grila(char *grila_sursa, int nr_linii, int nr_coloane);

char *apply_rule_B(char *grid, int N, int M);
char *apply_classic_rule(char *grid, int N, int M);

Celula *furnizare_lista_celule_diferite(char *grila_parinte, char *grila_fiu, int nr_linii, int nr_coloane); 

void parcurgere_preordine(nod_arbore* root, char* grila_parinte, int nivel, int N, int M, FILE *fis_out);

void aplica_diferente(char *grila, Celula *diferente, int N, int M);

void eliberare_arbore(nod_arbore* root);



#endif