#include <time.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    FILE *fp;

    if(argc != 3) 
    {
        printf("Use %s <nome_arquivo> <qde_numeros>\n", argv[0]);
        exit(1);
    }

    fp = fopen(argv[1], "w+");
    srand(time(NULL));
    int n, max = atoi(argv[2]);

    for (int i=0;i<atoi(argv[2]);i++)
    {
        n = rand() % max + 1;
        fwrite(&n, sizeof(int), 1, fp);
        //printf("%i ", n);
    }

    printf("\n");
    fclose(fp);
}