#ifndef MMV_GOL_TASK2_H
#define MMV_GOL_TASK2_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct celula       //elemente de lista, reprezinta pozitia unei celule din grila cu doi intregi, valorile contorilor
{
    int l, c;
    struct celula *urmator;
}; 
typedef struct celula Celula;

struct generatie        //elemente de stiva, fiecare element de stiva reprezinta o colectie de elemente de lista
{
    Celula *modificari;
    struct generatie *urm;
};
typedef struct generatie Generatie;

//Functii pentru liste

Celula* creare_celula(int linie, int coloana);
void adaugare_celula(Celula **cap, int linie, int coloana);
void eliberare_lista(Celula* cap);

//Functii pentru stive

Generatie* creare_generatie(Celula *modificari);
void adaugare_generatie(Generatie **stiva, Celula *modificari);
void inversare_stiva(Generatie **stiva); //operatie necesara pentru a realiza corect afisarea, stivele functioneaza pe principiul LIFO (sau FILO, acelasi lucru)
                                         //(last in first out), deci prima generatie inserata o sa fie defapt ultima afisata, in cazul in care nu se face inversare.
void eliberare_stiva(Generatie *stiva);

#endif