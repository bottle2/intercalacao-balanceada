#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    FILE *fp;
    if(argc != 2) 
    {
        printf("Use %s <nome_arquivo>\n", argv[0]);
        exit(1);
    }

    fp = fopen(argv[1], "r");
    int n;

    while (!feof(fp)) 
    {
        if(fread(&n,sizeof(int),1,fp))
        {
            printf("%i ",n);
        }        
    }
    
    printf("\n");
    fclose(fp);
}