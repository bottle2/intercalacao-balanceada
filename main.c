#include <stdio.h>
#include <stdlib.h>

#include "list.h"

#define MAX_INTS 5

int main(int argc, char *argv[])
{
    if(argc != 3) 
    {
        printf("Use %s <arquivo_original> <arquivo_ordenado>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    FILE     *arquivo_original;
    FileList *file_list        = FileCreate();

    arquivo_original = fopen(argv[1], "r");

    for (int run_i = 0; !feof(arquivo_original); run_i++)
    {
        int buffer[MAX_INTS] = {};
        if (fread(&buffer, sizeof(*buffer), sizeof(buffer) / sizeof(*buffer), arquivo_original))
        {
        }
    }

    fclose(arquivo_original);

    FileDestroy(file_list);

    return (EXIT_SUCCESS);
}
