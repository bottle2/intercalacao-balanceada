#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    FILE *fp;
    int   maior = -1;

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
            //printf("%i ",n);
	    if (n > maior)
	    {
		    maior = n;
	    }
            else if (n < maior)
	    {
                fclose(fp);
                printf("Não tá ordenado esse arquivo!\n");
                return(EXIT_FAILURE);
	    }
        }        
    }
    
    printf("Arquivo ordenadíssimo\n");
    fclose(fp);
    return(EXIT_SUCCESS);
}
