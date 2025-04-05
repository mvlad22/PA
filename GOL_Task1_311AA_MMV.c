#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int gaseste_vecini(char ** grila, int i, int j, int n, int m)
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
                    
                if(*((*grila)+(i+l)*m+j+k)=='X')  //daca celula este vie, ('X'), se adauga la numarul de vecini  
                {
                    numar_vecini++;
                }

            }
        }
        return numar_vecini;
}

void populare_grila(FILE * fis_in, char ** grila, int nr_linii, int nr_coloane)
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
                        *(((*grila)+contor_linii*nr_coloane)+contor_coloane)=ch;
                    }
                    
                }
            }
            
        }

}

void afisare_grila(FILE * fis_out, char ** grila, int nr_linii, int nr_coloane, int NR_TASK)
{
    if(NR_TASK==1)
    {
        int contor_linii, contor_coloane;
    
        for(contor_linii=0;contor_linii<nr_linii;contor_linii++)
        {
            for(contor_coloane=0;contor_coloane<nr_coloane;contor_coloane++)
            {
                fputc(*((*grila)+contor_linii*nr_coloane+contor_coloane),fis_out);
            }
            fputc('\n',fis_out); 

        }
    }

}


int main(int argc, const char *argv[])
{
    
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
    afisare_grila(fisier_output, &grila_initiala, N, M,T);
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

                if((*(grila_initiala+i*M+j)=='+') && (nr_vecini==3))//celula moarta cu exact 3 vecini invie
                {
                    *(grila_urmatoare+i*M+j)='X';
                    goto label2;
                }

                label2:
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
    


    fclose(fisier_input);
    fclose(fisier_output);
    free(grila_initiala);
    free(grila_urmatoare);
    return 0;
}