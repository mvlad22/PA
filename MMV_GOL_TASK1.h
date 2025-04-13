#ifndef MMV_GOL_TASK1_H
#define MMV_GOL_TASK1_H
#include <stdio.h>
#include <stdlib.h>

int gaseste_vecini(char ** grila, int i, int j, int n, int m);
void populare_grila(FILE * fis_in, char ** grila, int nr_linii, int nr_coloane);
void afisare_grila(FILE * fis_out, char ** grila, int nr_linii, int nr_coloane, int NR_TASK);

#endif