#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "MMV_GOL_TASK3.h"

void construire_arbore(nod_arbore **root, char* grila_principala, int nivel, int adancime, int nr_linii, int nr_coloane)
{
    if(nivel == adancime || root == NULL || (*root) == NULL)
    {
        return;
    }

    char *grila_temp = grila_principala;   //o grila temporara, retin matricea(grila) principala, a parintelui

    char *copie_stanga = NULL;
    char *grila_stanga = NULL;

    char *grila_dreapta = NULL;
    char *copie_dreapta = NULL;




    //mergem in stanga, aplicam regula B:
    //grila_temp=list_to_grid(grila_principala,nr_linii,nr_coloane);     //reconstruiesc grila, pornind de la lista de noduri a radacinii
    copie_stanga = copiaza_grila(grila_temp, nr_linii, nr_coloane);
    grila_stanga = apply_rule_B(copie_stanga,nr_linii,nr_coloane);

    nod_arbore *left_child = (nod_arbore*)malloc(sizeof(nod_arbore));
    left_child->left = NULL;
    left_child->right = NULL;
    left_child->data = furnizare_lista_celule_diferite(grila_temp,grila_stanga,nr_linii,nr_coloane);
    //free(grila_temp);

    (*root)->left=left_child;
    construire_arbore(&left_child,grila_stanga,nivel+1,adancime,nr_linii,nr_coloane);
    free(grila_stanga);






    //si acum mergem in dreapta, aplicam regula clasica:
    //grila_temp=list_to_grid((*root)->data,nr_linii,nr_coloane);
    copie_dreapta = copiaza_grila(grila_temp, nr_linii, nr_coloane);
    grila_dreapta = apply_classic_rule(copie_dreapta,nr_linii,nr_coloane);

    nod_arbore *right_child = (nod_arbore*)malloc(sizeof(nod_arbore));
    right_child->left = NULL;
    right_child->right = NULL;
    right_child->data = furnizare_lista_celule_diferite(grila_temp,grila_dreapta,nr_linii,nr_coloane);
    //free(grila_temp);

    (*root)->right=right_child;
    construire_arbore(&right_child,grila_dreapta,nivel+1,adancime,nr_linii,nr_coloane);
    free(grila_dreapta);
}

char *copiaza_grila(char *grila_sursa, int nr_linii, int nr_coloane)
{
    int i,j;
    char *copie = (char*)malloc(nr_linii*nr_coloane*sizeof(char));

    for(i=0;i<nr_linii;i++)
    {
        for(j=0;j<nr_coloane;j++)
        {
            *(copie+i*nr_coloane+j) = *(grila_sursa+i*nr_coloane+j);
        }
    }

    return copie;
}

char *list_to_grid(Celula *lista_celule,int N, int M)
{
    char *grid_aux = (char*)malloc(N*M*sizeof(char));
    int i,j;

    for(i=0;i<N;i++)
    {
        for(j=0;j<M;j++)
        {
            *(grid_aux+i*M+j)='+';  //initializez cu celula moarta
            if((i == lista_celule->l) && (j == lista_celule->c))    //daca contorii ajung la coordonatele unei celule vii, modificarea se reflecta in grila auxiliara
            {
                *(grid_aux+i*M+j)='X';
                if(lista_celule->urmator != NULL)   //avansez cu lista celulelor pe masura ce populez grila auxiliara
                {
                    lista_celule=lista_celule->urmator;
                }
            }
        }
    }
    return grid_aux;    //NU UITA SA DAI FREE IN FUNCTIA DE ARBORE DUPA APEL
}

char *apply_rule_B(char *grid, int N, int M)
{   
    int i,j, numar_vecini;
    for(i=0;i<N;i++)
    {
        for(j=0;j<M;j++)
        {
            numar_vecini=gaseste_vecini(&grid,i,j,N,M);

            if(numar_vecini == 2)
            {
                *(grid+i*M+j) = 'X';     //regula B: orice celula cu exact 2 vecini devine vie
            }
        }
    }
    
    
    return grid;
}

char *apply_classic_rule(char *grid, int N, int M)
{
    int i,j, numar_vecini;
    for(i=0;i<N;i++)
    {
        for(j=0;j<M;j++)
        {
            numar_vecini=gaseste_vecini(&grid,i,j,N,M);

            if((*(grid+i*M+j) == 'X') && ((numar_vecini < 2) || (numar_vecini > 3))) 
            {                                           //daca celula e vie si are <2 sau <3 vecini, moare
                *(grid+i*M+j) = '+';
            }
            else if((*(grid+i*M+j) == '+') && (numar_vecini ==3)){ *(grid+i*M+j) = 'X'; } //celula moarta cu exact 3 vecini, invie
        }
    }
    
    return grid;
}

Celula *furnizare_lista_celule_diferite(char *grila_parinte, char *grila_fiu, int nr_linii, int nr_coloane)
{
    int i, j;
    Celula *lista_aux=NULL;

    for(i=0;i<nr_linii;i++)
    {
        for(j=0;j<nr_coloane;j++)
        {
            if(*(grila_fiu+i*nr_coloane+j) != *(grila_parinte+i*nr_coloane+j)) //se gasesc coordonatele celulei diferite si se actualizeaza lista
            {
                adaugare_celula(&lista_aux,i,j);
            }
        }
    }
    return lista_aux;   //NU UITA DE FREE (dar in main, pentru ca lista este informatia utila a arborelui)
}

void aplica_diferente(char *grila, Celula *diferente, int N, int M) {
    while (diferente != NULL) {
        int i = diferente->l;
        int j = diferente->c;
        int idx = i * M + j;
        if(*(grila+idx) == '+')
        {
            *(grila+idx) = 'X';
        }
        else if(*(grila + idx) == 'X'){ *(grila+idx) = '+'; }

        diferente = diferente->urmator;
    }
}

void parcurgere_preordine(nod_arbore* root, char* grila_parinte, int N, int M, FILE *fis_out) {
    if (root == NULL) return;

    // copiez grila parintelui ca sa o pot modifica independent
    char* grila_curenta = copiaza_grila(grila_parinte, N, M);
    aplica_diferente(grila_curenta, root->data, N, M);

    afisare_grila(fis_out,&grila_curenta, N, M, 1);

    // merg in stanga si in dreapta cu grila actualizata
    parcurgere_preordine(root->left, grila_curenta, N, M,fis_out);
    parcurgere_preordine(root->right, grila_curenta, N, M,fis_out);

    free(grila_curenta);
}

void eliberare_arbore(nod_arbore* root) {
    if (!root) return;

    eliberare_arbore(root->left);
    eliberare_arbore(root->right);

    eliberare_lista(root->data);
    free(root);
}