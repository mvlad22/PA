#include <stdio.h>
#include <stdlib.h>


int main(int argc, const char *argv[])
{
    
    FILE *fis_in, *fis_out;

    if((fis_in=(FILE*)fopen(argv[1],"rt"))==NULL)
    {
        perror("Read file error");
        exit(1);
    }

    if((fis_out=(FILE*)fopen(argv[2],"wt"))==NULL)
    {
        perror("Write file error");
        exit(2);
    }


    int nr_task;

    fscanf(fis_in, "%d", &nr_task);
    fprintf(fis_out, "Numarul task-ului este %d.\n", nr_task);


    fclose(fis_in);
    fclose(fis_out);

    printf("\n\n");
    return 0;
}