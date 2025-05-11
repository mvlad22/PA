#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "MMV_GOL_TASK1.h"
#include "MMV_GOL_TASK2.h"



int main(int argc, const char *argv[])
{
    if(argc != 3)
    {
        fprintf(stderr, "3 agrs needed");
        return 1;
    }
    
    
    FILE *fisier_input, *fisier_output;

    if((fisier_input=(FILE*)fopen(argv[1],"rt"))==NULL)
    {
        perror("Read file error");
        exit(1);
    }

    if((fisier_output=(FILE*)fopen(argv[2],"wt"))==NULL)
    {
        perror("Write file error");
        exit(2);
    }


    int T;      //T reprezinta numarul task-ului
    int N, M;   //N si M reprezinta dimensiunea grilei de joc
    int K;      //K reprezinta numarul generatiilor de calculat


    fscanf(fisier_input, "%d", &T);
    fscanf(fisier_input, "%d", &N);
    fscanf(fisier_input, "%d", &M);
    fscanf(fisier_input, "%d", &K);
    fgetc(fisier_input);

    char *grila_initiala;
    char *grila_urmatoare;
        
            if((grila_initiala=(char*)malloc(N*M*sizeof(char)))==NULL) 
            {
                perror("Malloc fail grila joc");
                exit(3);                                           
            }
        
            if((grila_urmatoare=(char*)malloc(N*M*sizeof(char)))==NULL) 
            {
                perror("Malloc fail grila joc");
                exit(3);                                           
            }                                                      /*Am alocat dinamic matricea
                                                                    pentru grila de joc, sub forma                            
                                                                    unui vector de dimensiune N*M,                                
                                                                    cu elemente de tip char. Functionalitatea
                                                                    de matrice se poate obtine prin mapare simpla.
                                                                   */
        
            int contor_generatii;       //contor pentru generatii
            int i,j;        //contorii pentru parcurgerea grilei
            int nr_vecini;
        
            populare_grila(fisier_input, &grila_initiala, N, M);

if(T==1)
{


    afisare_grila(fisier_output, &grila_initiala, N, M, T);
    fputc('\n', fisier_output);

    for(i=0;i<N;i++)
        {
            for(j=0;j<M;j++)
            {
                *((grila_urmatoare+i*M)+j)=*((grila_initiala+i*M)+j);   //initializez generatia urmatoare cu cea prezenta
                                                                        // pentru a nu pierde celulele originale in timpul operatiilor
            }
        }

    for(contor_generatii=0;contor_generatii<K;contor_generatii++)
    {
        
        for(i=0;i<N;i++)
        {
            for(j=0;j<M;j++)
            {
                nr_vecini=gaseste_vecini(&grila_initiala,i,j,N,M);

                if((*(grila_initiala+i*M+j)=='X'))//daca celula este vie
                {
                    if(nr_vecini<2 || nr_vecini>3) //celula vie cu <2 sau >3 vecini moare
                    {
                        *(grila_urmatoare+i*M+j)='+';
                        continue;
                    }
                }
                 else if(*(grila_urmatoare+i*M+j)=='+')//celula moarta cu exact 3 vecini invie
                {
                    if(nr_vecini==3)
                        {
                            *(grila_urmatoare+i*M+j)='X';
                        }   
                    continue;
                }

                //label1:
            }
        }
        afisare_grila(fisier_output, &grila_urmatoare, N, M,T);
        fprintf(fisier_output,"\n");

        for(i=0;i<N;i++)
        {
            for(j=0;j<M;j++)
            {
                *(grila_initiala+i*M+j)=*(grila_urmatoare+i*M+j);//schimb matricele intre ele 
                                                                    // pentru a putea continua calculul
                                                                    // iteratiilor urmatoare
            }
        }
    }
}
else if(T==2)
    {
        afisare_grila(fisier_output, &grila_initiala, N, M, T);
        for(i=0;i<N;i++)
        {
            for(j=0;j<M;j++)
            {
                *((grila_urmatoare+i*M)+j)=*((grila_initiala+i*M)+j);   //initializez generatia urmatoare cu cea prezenta
                                                                        // pentru a nu pierde celulele originale in timpul operatiilor
            }
        }
        
        Generatie *stiva = NULL;    //initializez stiva generatiilor cu NULL
        
        for(contor_generatii = 0; contor_generatii < K; contor_generatii++)
        {
            Celula *modificari = NULL;  //initializez lista unei generatii de celule cu NULL

            for(i=0; i<N; i++)
            {
                for(j=0; j<M; j++)
                {
                    nr_vecini = gaseste_vecini(&grila_initiala, i, j, N, M);

                    if((*(grila_initiala+i*M+j)=='X'))//daca celula este vie
                    {
                        if(nr_vecini<2)//celula vie cu <2 vecini moare
                        {
                            *(grila_urmatoare+i*M+j)='+';
                            goto label2; //se realizeaza o singura operatie per celula
                        }

                        if(((nr_vecini == 2) || (nr_vecini == 3))) // celula vie cu exact 2 sau exact 3 vecini supravietuieste
                        {
                            goto label2;
                        }

                        if(nr_vecini>3)//celula vie cu >3 vecini moare
                        {
                            *(grila_urmatoare+i*M+j)='+';
                            goto label2;
                        }
                    }
                    else if((nr_vecini==3))//celula moarta cu exact 3 vecini invie
                    {
                        *(grila_urmatoare+i*M+j)='X';
                        goto label2;
                    }

                label2:

                    if( *(grila_urmatoare+i*M+j) != *(grila_initiala+i*M+j) )       //cu alte cuvinte, daca celula de coordonate i,j isi modifica starea,
                    {                                                               //este adaugata in lista celulelor modificare, corespunzatoare generatiei.
                        adaugare_celula(&modificari, i, j);
                    }
                }
            }

            adaugare_generatie(&stiva, modificari);
            //cand se gasesc toate celulele ce isi modifica starea, lista de modificari este introdusa in stiva

            for(i=0;i<N;i++)
            {
                for(j=0;j<M;j++)
                {
                    *(grila_initiala+i*M+j)=*(grila_urmatoare+i*M+j);//schimb matricele intre ele 
                                                                    // pentru a putea continua calculul
                                                                    // iteratiilor urmatoare
                }
            }
        }

        inversare_stiva(&stiva);

        int numar_generatie=1; //primul numar de pe linie din fisierele de referinta Test 06 - Test 10
        Generatie *gen = stiva; //memorez stiva
        while(gen != NULL)
        {
            Celula *cel = gen->modificari; //memorez lista, elementul stivei
            fprintf(fisier_output, "%d ", numar_generatie);

            while(cel != NULL)
            {
                fprintf(fisier_output, "%d ", cel->l);

                if(cel->urmator == NULL)
                {
                    fprintf(fisier_output, "%d\n", cel->c); //daca se afiseaza ultima cifra, trec la linie noua
                }
                else
                {
                    fprintf(fisier_output, "%d ", cel->c);
                }

                cel = cel->urmator;

            }

            gen = gen->urm;
            numar_generatie++;
        }

        eliberare_stiva(stiva);
        //free(grila_initiala);
        //free(grila_urmatoare);
        //fclose(fisier_input);
        //fclose(fisier_output);
        //break;
    //return 0;
    }

else if(T==3)
    {

    }

else if(T==4)
    {
    //fclose(fisier_input);
    //fclose(fisier_output);
    //return 0;
    }

    free(grila_initiala);
    free(grila_urmatoare);
    fclose(fisier_input);
    fclose(fisier_output);
   return 0;
}