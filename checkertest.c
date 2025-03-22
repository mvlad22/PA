#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    FILE *fin, *fout;

    if((fin=(FILE*)fopen("fisier1.txt","rt"))==NULL)
    {
        perror("Reading file error");
        exit(1);
    }
    if((fout=(FILE*)fopen("fisier2.txt","wt"))==NULL)
    {
        perror("Writing file error");
        exit(2);
    }

    int x;

    fscanf(fin, "%d", &x);
    fprintf(fout, "Valoarea lui x este %d.\n", x);

    printf("Program executat cu succes.\n");

    fclose(fin);
    fclose(fout);

    return 0;
}