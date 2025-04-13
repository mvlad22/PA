#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "MMV_GOL_TASK1.h"

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