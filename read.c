#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    FILE *fp;
    int   maior = INT_MIN;

    if(argc != 2) 
    {
        printf("Use %s <nome_arquivo>\n", argv[0]);
        exit(1);
    }

    fp = fopen(argv[1], "r");
    int n, count = 0;

    while (!feof(fp)) 
    {
        if(fread(&n,sizeof(int),1,fp))
        {
            printf("%d ", n);
            count++;
            //#if 0
            if (n > maior)
            {
                maior = n;
            }
            else if (n < maior)
            {
                fclose(fp);
                printf("\nLidos %i números.\n", count);
                printf("Arquivo não está em ordem!\n");
                return(EXIT_FAILURE);
            }
            //#endif
        }        
    }
    printf("\nLidos %i números.\n", count);
    printf("Arquivo ordenadíssimo\n");
    fclose(fp);
    return(EXIT_SUCCESS);
}
