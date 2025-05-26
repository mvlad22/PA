#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "MMV_GOL_TASK3.h"

int gaseste_vecini_T3(char * grila, int i, int j, int n, int m) //char* in loc de char**, singura diferenta intre versiunile celor 2 task-uri
{
        int k, l;   //contorii submatricei cautare, se ia o matrice de 3x3 in jurul elementului 
                    //trimis in apel, si se verifica starea celor 8 vecini din jur.
        int numar_vecini=0;
        for(l=-1;l<=1;l++)
        {
            for(k=-1;k<=1;k++)
            {
                if((i+l) < 0 || (j+k) < 0 || (i+l) >= n || (j+k) >= m || (l==0 && k==0)) /*exclud cazurile cu offset negativ, 
                                                                                            sa nu se iasa din matrice*/
                {
                    continue;
                }    
                    
                if(*((grila)+(i+l)*m+j+k)=='X')  //daca celula este vie, ('X'), se adauga la numarul de vecini  
                {
                    numar_vecini++;
                }

            }
        }
        return numar_vecini;
}

void afisare_grila_T3(FILE * fis_out, char * grila, int nr_linii, int nr_coloane, int NR_TASK) //vezi comentariu linie 6
{
    if(NR_TASK==1)
    {
        int contor_linii, contor_coloane;
    
        for(contor_linii=0;contor_linii<nr_linii;contor_linii++)
        {
            for(contor_coloane=0;contor_coloane<nr_coloane;contor_coloane++)
            {
                fputc(*((grila)+contor_linii*nr_coloane+contor_coloane),fis_out);
            }
            fputc('\n',fis_out); 

        }
    }

}

void construire_arbore(nod_arbore **root, char* grila_principala, int nivel, int adancime, int nr_linii, int nr_coloane)
{
    if(nivel == adancime || root == NULL || (*root) == NULL)
    {
        return;
    }

    char *grila_temp = copiaza_grila(grila_principala,nr_linii,nr_coloane);   //o grila temporara, retin matricea(grila) principala, a parintelui

    char *copie_stanga = NULL;
    char *grila_stanga = NULL;

    char *grila_dreapta = NULL;
    char *copie_dreapta = NULL;




    //mergem in stanga, aplicam regula B:
    copie_stanga = copiaza_grila(grila_temp, nr_linii, nr_coloane);
    grila_stanga = apply_rule_B(copie_stanga,nr_linii,nr_coloane);
    free(copie_stanga);

    nod_arbore *left_child = (nod_arbore*)malloc(sizeof(nod_arbore));
    left_child->left = NULL;
    left_child->right = NULL;
    left_child->data = furnizare_lista_celule_diferite(grila_temp,grila_stanga,nr_linii,nr_coloane);

    (*root)->left=left_child;
    construire_arbore(&left_child,grila_stanga,nivel+1,adancime,nr_linii,nr_coloane);
    free(grila_stanga);






    //si acum mergem in dreapta, aplicam regula clasica:
    copie_dreapta = copiaza_grila(grila_temp, nr_linii, nr_coloane);
    grila_dreapta = apply_classic_rule(copie_dreapta,nr_linii,nr_coloane);
    free(copie_dreapta);

    nod_arbore *right_child = (nod_arbore*)malloc(sizeof(nod_arbore));
    right_child->left = NULL;
    right_child->right = NULL;
    right_child->data = furnizare_lista_celule_diferite(grila_temp,grila_dreapta,nr_linii,nr_coloane);

    (*root)->right=right_child;
    construire_arbore(&right_child,grila_dreapta,nivel+1,adancime,nr_linii,nr_coloane);
    free(grila_dreapta);

    free(grila_temp);
}

char *copiaza_grila(char *grila_sursa, int nr_linii, int nr_coloane)
{
    int i,j;
    char *copie = (char*)malloc(nr_linii*nr_coloane*sizeof(char));

    if(copie == NULL)
    {
        perror("Malloc fail grid copy function");
        exit(1);
    }

    for(i=0;i<nr_linii;i++)
    {
        for(j=0;j<nr_coloane;j++)
        {
            *(copie+i*nr_coloane+j) = *(grila_sursa+i*nr_coloane+j);
        }
    }

    return copie;
}

char *apply_rule_B(char *grid, int N, int M)
{   
    int i,j, numar_vecini;
    char *grila_auxiliara_B = NULL;
    grila_auxiliara_B = copiaza_grila(grid,N,M);

    for(i=0;i<N;i++)
    {
        for(j=0;j<M;j++)
        {
            numar_vecini=gaseste_vecini_T3(grid,i,j,N,M);

            if(numar_vecini == 2)
            {
                *(grila_auxiliara_B+i*M+j) = 'X';     //regula B: orice celula cu exact 2 vecini devine vie
            }
        }
    }
    
    
    return grila_auxiliara_B;
}

char *apply_classic_rule(char *grid, int N, int M)
{
    int i,j, numar_vecini;
    char *grila_auxiliara_classic = NULL;
    grila_auxiliara_classic = copiaza_grila(grid,N,M);
    for(i=0;i<N;i++)
    {
        for(j=0;j<M;j++)
        {
            numar_vecini=gaseste_vecini_T3(grid,i,j,N,M);

            if((*(grid+i*M+j) == 'X') && ((numar_vecini < 2) || (numar_vecini > 3))) 
            {                                           //daca celula e vie si are <2 sau <3 vecini, moare
                *(grila_auxiliara_classic+i*M+j) = '+';
            }
            else if((*(grid+i*M+j) == '+') && (numar_vecini ==3)){ *(grila_auxiliara_classic+i*M+j) = 'X'; } //celula moarta cu exact 3 vecini, invie
        }
    }
    
    return grila_auxiliara_classic;
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
    return lista_aux;
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

void parcurgere_preordine(nod_arbore* root, char* grila_parinte, int nivel, int N, int M, FILE *fis_out) {
    if (root == NULL) return;

    // copiez grila parintelui ca sa o pot modifica independent
    char* grila_curenta = copiaza_grila(grila_parinte, N, M);

    if(nivel != 0)
    {
        aplica_diferente(grila_curenta, root->data, N, M);      //  ca sa nu imi afiseze grila moarta din prima,
    }                                                           //  lista de noduri a radacinii arborelui contine celulele initiate vii, 
                                                                //  daca am apela functia "aplica_diferente" pentru radacina arborelui, celulele ar muri!
    afisare_grila_T3(fis_out,grila_curenta, N, M, 1);
    fputc('\n', fis_out);

    // merg in stanga si in dreapta cu grila actualizata
    parcurgere_preordine(root->left, grila_curenta, nivel+1, N, M,fis_out);
    parcurgere_preordine(root->right, grila_curenta, nivel+1, N, M,fis_out);

    free(grila_curenta);
}

void eliberare_arbore(nod_arbore* root) {
    if (!root) return;

    eliberare_arbore(root->left);
    eliberare_arbore(root->right);

    eliberare_lista(root->data);
    free(root);
}