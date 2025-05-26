#ifndef MMV_GOL_TASK4_H
#define MMV_GOL_TASK4_H

#include <stdio.h>
#include <stdlib.h>

struct cel
{
    int l;
    int c;
};
typedef struct cel CELL;

void parcurgere_preordine_T4(nod_arbore* root, char* grila_parinte, int nivel, int N, int M, FILE *fis_out);
void DFS(int nod, int* matrice_adiacenta, int nr_celule_vii, int* vizitat, CELL* vector_celule_vii, int* drum_curent, int lungime_drum, int* lungime_maxima, int* calea_cea_mai_lunga);
void gaseste_lant_hamiltonian(int* matrice_adiacenta, CELL* vector_celule_vii, int nr_celule_vii,FILE* fis_out);
void populare_grila_T4(FILE * fis_in, char *grila, int nr_linii, int nr_coloane); //char* in loc de char**

#endif