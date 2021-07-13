#include <stdio.h>
#include <stdlib.h>

#include "list.h"

#define MAX_INTS 5

static int cmp(void* a, void* b){
    return( *((int*)a) - *((int*)b) );
}

int main(int argc, char *argv[])
{
    if(argc != 3) 
    {
        printf("Use %s <arquivo_original> <arquivo_ordenado>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    FILE     *arquivo_original;
    FileList *file_list        = fileCreate();

    arquivo_original = fopen(argv[1], "r");

    for (int run_i = 0; !feof(arquivo_original); run_i++)
    {
        int buffer[MAX_INTS] = {};
        if (fread(&buffer, sizeof(*buffer), sizeof(buffer) / sizeof(*buffer), arquivo_original))
        {        
            //qsort(&buffer, MAX_INTS, sizeof(*buffer), cmp);
            char fname[100];
            sprintf(fname, "%c %d", 'A', run_i);
            FILE* fp = fopen(fname, "w");
            fwrite(&buffer, sizeof(*buffer), MAX_INTS, fp);
            fclose(fp);
        }
    }

    fclose(arquivo_original);

    fileDestroy(file_list);

    return (EXIT_SUCCESS);
}
