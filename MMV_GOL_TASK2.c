#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "MMV_GOL_TASK2.h"

        //Functiile pentru liste

Celula* creare_celula(int linie, int coloana)
{
    Celula *noua;
    if((noua = (Celula*)malloc(sizeof(Celula))) == NULL)
    {
        perror("Malloc fail element lista");
        exit(4);
    }

    noua->l = linie;
    noua->c = coloana;
    noua->urmator = NULL;
    return noua;
}

void adaugare_celula(Celula **cap, int linie, int coloana)
{
    Celula* noua = creare_celula(linie , coloana);

    if( ((*cap) == NULL) || (linie < (*cap)->l) || (linie == (*cap)->l && coloana < (*cap)->c) ) // daca lista e goala, celula adaugata devine capul listei
    {                                                                                            // daca celula noua trebuie sa apara inaintea primei celule deja existente
        noua->urmator = (*cap);                                                                  // (linie mai mica, sau linie egala dar coloana mai mica), o punem in fata
        *cap = noua;
        return;
    }

    Celula* aux = (*cap);       //memoram celula curenta
    while (aux->urmator != NULL && ((aux->urmator->l < linie ) || (aux->urmator->l == linie && aux->urmator->c < coloana) )) //parcurg lista pana in pozitia in care trebuie sa inserez
    {
        aux = aux->urmator;
    }

    noua->urmator = aux->urmator;
    aux->urmator = noua;

}

void eliberare_lista(Celula *cap)
{
    while(cap)
    {
        Celula *urm =cap->urmator;
        free(cap);
        cap = urm;
    }
}


        //Functiile pentru stive


Generatie* creare_generatie(Celula *modificari)
{
    Generatie *gen;
    if( (gen = (Generatie*)malloc(sizeof(Generatie))) == NULL )
    {
        perror("Malloc fail element stiva generatii");
        exit(5);
    }

    gen->modificari = modificari;
    gen->urm = NULL;
    return gen;
}

void adaugare_generatie(Generatie **stiva, Celula *modificari)
{
    Generatie *gen = creare_generatie(modificari);
    gen->urm = *stiva;
    (*stiva) = gen;
}

void inversare_stiva(Generatie **stiva)
{
    Generatie *anterior = NULL;
    Generatie *aux = *stiva;     //memoram generatia curenta
    while(aux)
    {
        Generatie *urm = aux->urm; //memoram generatia urmatoare
        aux->urm = anterior;        //interschimbare
        anterior = aux;
        aux = urm;
    }
    *stiva = anterior;
}

void eliberare_stiva(Generatie *stiva)
{
    while(stiva)
    {
        eliberare_lista(stiva->modificari);
        Generatie *urm = stiva->urm;
        free(stiva);
        stiva = urm;
    }
}