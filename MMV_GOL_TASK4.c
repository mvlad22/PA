#include <stdio.h>
#include <stdlib.h>
#include "MMV_GOL_TASK3.h"
#include "MMV_GOL_TASK4.h"

int dfs_calls = 0;
//int found_full_path = 0;


void parcurgere_preordine_T4(nod_arbore* root, char* grila_parinte, int nivel, int N, int M, FILE *fis_out)
{
    //FILE* fp;
    //fp = fopen("debugT4.txt","wt");
    //static int nr_nod = 0;


    int i,j;
    int nr_celule_vii=0;    //util pentru aflarea dimensiunii matricei de adiacenta
    int dimensiune_matrice;
    int* matrice_de_adiacenta;

    CELL* vector_celule_vii;    //vector ce retine pozitia in grila a celulelor vii, index-ul reprezinta a cata celula vie este, practic indicele din matricea de adiacenta....
    int contor = 0;     //contorul vectorului, creste pe masura ce se populeaza elementele, practic o stiva....

    CELL* vector_aux;
    int contor_aux = 0;

    if (root == NULL) return;

    // copiez grila parintelui ca sa o pot modifica independent
    char* grila_curenta = copiaza_grila(grila_parinte, N, M);

    if(nivel != 0)
    {
        aplica_diferente(grila_curenta, root->data, N, M);      //  ca sa nu imi afiseze grila moarta din prima,
    }                                                           //  lista de noduri a radacinii arborelui contine celulele initiate vii, 
                                                                //  daca am apela functia "aplica_diferente" pentru radacina arborelui, celulele ar muri!
   
    //fputc('\n', fis_out);
    //fprintf(fp,"NODUL NR:%d\n",nr_nod);
    //nr_nod++;

    for(i=0;i<N;i++)
    {
        for(j=0;j<M;j++)
        {
          if(*(grila_curenta+i*M+j) == 'X')
          {
            nr_celule_vii++;
          }
        }
    }
    //fprintf(fp,"Numar celule vii:%d\n",nr_celule_vii);

    
    if((vector_celule_vii = (CELL*)malloc(nr_celule_vii*sizeof(CELL))) == NULL)
    {
        perror("Malloc fail vector celule");
        exit(8);
    }

    if((vector_aux = (CELL*)malloc(nr_celule_vii*sizeof(CELL))) == NULL)
    {
        perror("Malloc fail vector celule");
        exit(9);
    }

    dimensiune_matrice = nr_celule_vii * nr_celule_vii;
    if((matrice_de_adiacenta = (int*)calloc(dimensiune_matrice,sizeof(int))) == NULL)
    {
        perror("Calloc fail matrice adiacenta");
        exit(10);
    }

    for(i=0;i<N;i++)
    {
        for(j=0;j<M;j++)
        {
            if(*(grila_curenta+i*M+j) == 'X')   //daca celula este vie, se introduc coordonatele celulei in cei 2 vectori
            {                                   //sunt necesari 2 vectori pentru popularea matricei de adiacenta
               (*(vector_celule_vii+contor)).l = i;
               (*(vector_celule_vii+contor)).c = j;
               //fprintf(fp,"%d (%d,%d) \n",contor,(*(vector_celule_vii+contor)).l,(*(vector_celule_vii+contor)).c);
               contor++;

               (*(vector_aux+contor_aux)).l = i;
               (*(vector_aux+contor_aux)).c = j;
               contor_aux++;

            }
        }
    }

    for(contor=0;contor<nr_celule_vii;contor++)
    {
        for(contor_aux=0;contor_aux<nr_celule_vii;contor_aux++)
        {
            if(contor_aux != contor) //sa evit cazul de self loop in matricea de adiacenta
            {
                int poz_lin = (*(vector_celule_vii+contor)).l;
                int poz_col = (*(vector_celule_vii+contor)).c;

                int poz_lin_aux = (*(vector_aux+contor_aux)).l;
                int poz_col_aux = (*(vector_aux+contor_aux)).c;
                //urmeaza un if kilometric, imi pare rau

                if(((poz_lin_aux == poz_lin -1) && (poz_col_aux == poz_col -1)) || 
                    ((poz_lin_aux == poz_lin -1) && (poz_col_aux == poz_col)) ||
                    ((poz_lin_aux == poz_lin -1) && (poz_col_aux == poz_col +1)) ||
                    ((poz_lin_aux == poz_lin) && (poz_col_aux == poz_col -1)) ||
                    ((poz_lin_aux == poz_lin) && (poz_col_aux == poz_col +1)) ||
                    ((poz_lin_aux == poz_lin +1) && (poz_col_aux == poz_col -1)) ||
                    ((poz_lin_aux == poz_lin +1) && (poz_col_aux == poz_col)) ||
                    ((poz_lin_aux == poz_lin +1) && (poz_col_aux == poz_col +1)))
                    {
                        *(matrice_de_adiacenta+contor*nr_celule_vii+contor_aux) = 1;
                        *(matrice_de_adiacenta+contor_aux*nr_celule_vii+contor) = 1;
                    }
            }
        }
    }
   /* if(nivel == 0)                        //DEBUGGING (verific daca se genereaza corect matricea de adiacenta)
    for(i=0;i<nr_celule_vii;i++)
    {
        for(j=0;j<nr_celule_vii;j++)
        {
            fprintf(fp,"%d ",*(matrice_de_adiacenta+i*nr_celule_vii+j));
        }
        printf("\n");
    }
    fclose(fp);*/

    gaseste_lant_hamiltonian(matrice_de_adiacenta,vector_celule_vii,nr_celule_vii,fis_out);

    // merg in stanga si in dreapta cu grila actualizata
    parcurgere_preordine_T4(root->left, grila_curenta, nivel+1, N, M,fis_out);
    parcurgere_preordine_T4(root->right, grila_curenta, nivel+1, N, M,fis_out);

    free(grila_curenta);
    free(matrice_de_adiacenta);
    free(vector_celule_vii);
    free(vector_aux);
}

void DFS(int nod, int* matrice_adiacenta, int nr_celule_vii, int* vizitat, CELL* vector_celule_vii, int* drum_curent, int lungime_drum, int* lungime_maxima, int* calea_cea_mai_lunga)
{
    int i;
    dfs_calls++;
    if(dfs_calls % 10000 == 0)
    {
        fprintf(stderr, "[DEBUG] DFS calls: %d\n", dfs_calls);
    }
   // FILE *fp = fopen("debugT4.txt","at");

   //if(found_full_path) return;

    *(vizitat+nod) = 1; //vizitez nodul si il adaug in drumul curent
    *(drum_curent+lungime_drum) = nod; 

    if(lungime_drum + 1 > *(lungime_maxima))    //daca drumul curent e mai lung, actualizam calea cea mai lunga
    {
        *(lungime_maxima) = lungime_drum +1;
        fprintf(stderr, "[DFS] New longest path: %d\n", *lungime_maxima);

        for(i=0; i<lungime_drum+1 ; i++)
        {
            *(calea_cea_mai_lunga+i) = *(drum_curent+i);
        }
    }

    if(*(lungime_maxima) == nr_celule_vii)
    {
        *(vizitat+nod) = 0;
        return;
    }

    for(i=0;i<nr_celule_vii;i++)    //tineti-va bine, urmeaza un apel de functie lung 
    {
        if( (*(matrice_adiacenta+nod*nr_celule_vii+i) == 1) && (!(*(vizitat+i))) )  //daca exista muchie intre nodurile grafului, si nodul nu este vizitat, continuam parcurgerea in adancime
        {
            DFS(i,matrice_adiacenta,nr_celule_vii,vizitat,vector_celule_vii,drum_curent,lungime_drum+1,lungime_maxima,calea_cea_mai_lunga);
        }
    }

    *(vizitat+nod) = 0;
}

void gaseste_lant_hamiltonian(int* matrice_adiacenta, CELL* vector_celule_vii, int nr_celule_vii,FILE* fis_out)
{   
    
    //FILE *fp = fopen("debugT4.txt","at");
    fprintf(stderr, "[INFO] Starting Hamiltonian search with %d live cells\n", nr_celule_vii);
    
    int *vizitat;
    if((vizitat = (int*)calloc(nr_celule_vii,sizeof(int))) == NULL)
    {
        perror("Calloc fail vector int vizitat");
        exit(11);
    }

    int* cale_curenta;  //drum curent
    if((cale_curenta = (int*)malloc(nr_celule_vii*sizeof(int))) == NULL)
    {
        perror("Malloc fail vector cale curenta");
        exit(12);
    }

    int* cel_mai_lung_drum;
    if((cel_mai_lung_drum = (int*)malloc(nr_celule_vii*sizeof(int))) == NULL)
    {
        perror("Malloc fail cel mai lung lant");
        exit(13);
    }    
    
    int lungime_maxima = 0;
    int i;

    fprintf(stderr, "[INFO] Trying all %d starting nodes...\n", nr_celule_vii);

    for(i=0;i<nr_celule_vii;i++)
    {
        DFS(i,matrice_adiacenta,nr_celule_vii,vizitat,vector_celule_vii,cale_curenta,0,&lungime_maxima,cel_mai_lung_drum);
    }
    //fprintf(fp,"\nLungime maxima %d\n",lungime_maxima);
    //fclose(fp);

    fprintf(fis_out, "%d\n", lungime_maxima-1);
    for(i=0;i<lungime_maxima;i++)
    {
        int index = *(cel_mai_lung_drum+i);
        fprintf(fis_out, "(%d,%d) ", (*(vector_celule_vii+index)).l, (*(vector_celule_vii+index)).c);
    }
    fputc('\n',fis_out);

    free(vizitat);
    free(cale_curenta);
    free(cel_mai_lung_drum);

    fprintf(stderr, "[INFO] Hamiltonian search finished. Max path length: %d\n", lungime_maxima);
    fprintf(stderr, "[INFO] Total DFS calls: %d\n", dfs_calls);
}

/*void populare_grila_T4(FILE * fis_in, char *grila, int nr_linii, int nr_coloane)
{
    
    int contor_linii, contor_coloane;
    char ch; // variabila ajutatoare pentru citire, operatia este realizata caracter cu caracter

    
        for(contor_linii=0;contor_linii<nr_linii;contor_linii++)
        {   
            for(contor_coloane=0;contor_coloane<nr_coloane;contor_coloane++)
            {
                
                if(!(feof(fis_in)))
                {   
                    ch=fgetc(fis_in);

                    if(ch == '\n')
                    {
                        contor_coloane--;
                        continue;
                    }

                    if(ch=='X'|| ch=='+')
                    {
                        *(((grila)+contor_linii*nr_coloane)+contor_coloane)=ch;
                    }
                    
                }
            }
            
        }

} */