#include <assert.h>
#include <err.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#include "queue.h"

#define MAX_INTS 5
#define PATH_FILES "./files/"

static int cmp(const void* a, const void* b);
static void merge_sort(FileQueue* queue);

static int cmp(const void* a, const void* b){
    return( *((int*)a) - *((int*)b) );
}

static void merge_sort(FileQueue* queue){
    
    while(getQueueSize(queue) > 1)
    {
        printf("lala");

        char fname[10000];
        sprintf(fname, "%s %c %d", PATH_FILES,'I', getQueueNewId(queue));

        FILE* aux = fopen(fname, "w+b"); 
        FILE* f1  = filePop(queue);
        FILE* f2  = filePop(queue);

        rewind(f1); rewind(f2);

        //mergeson

        int e1 = 0; 
        int e2 = 0;
        int ex = 0;
        fread(&e1, sizeof(e1), 1, f1);
        fread(&e2, sizeof(e2), 1, f2);

        while (!feof(f1) || !feof(f2))
        {
            if (feof(f2) || (!feof(f1) && e1 <= e2))
            {
                ex = e1;
                fread(&e1, sizeof(e1), 1, f1);
            }
            else if(feof(f1) || (!feof(f2) && e2 < e1))
            {
                ex = e2;
                fread(&e2, sizeof(e2), 1, f2);
            }
            else
            {
                assert(!"Caso impossível");
            }

            fwrite(&ex, sizeof(int), 1, aux);
        }
        
        fclose(f1);
        fclose(f2);
        //DELETAR ARQUIVOS
        filePush(queue, aux);
    }    
}

int main(int argc, char *argv[])
{
    if(argc != 3) 
    {
        printf("Use %s <arquivo_original> <arquivo_ordenado>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    FILE     *arquivo_original;
    FileQueue *file_queue        = fileCreate();

    arquivo_original = fopen(argv[1], "rb");
    int buffer[MAX_INTS] = {0};

    while (fread(&buffer, sizeof(*buffer), sizeof(buffer) / sizeof(*buffer), arquivo_original))
    {
        if (ferror(arquivo_original))
        {
            printf("ERROR :: %d\n", ferror(arquivo_original));
            clearerr(arquivo_original);
        }
        qsort(&buffer, MAX_INTS, sizeof(*buffer), cmp);
        char fname[100000];
        sprintf(fname, "%s %c %d", PATH_FILES,'A', getQueueNewId(file_queue));
        FILE* fp = NULL;
	while (!(fp = fopen(fname, "w+b")))
        {
            printf("Dando pau: %d\n", errno);
        }
        fwrite(&buffer, sizeof(*buffer), MAX_INTS, fp);
        filePush(file_queue, fp);
    }

    fclose(arquivo_original);

    if(getQueueSize(file_queue) != 0)
    {
        merge_sort(file_queue);

        FILE *arquivo_ordenado  = filePop(file_queue);
        rewind(arquivo_ordenado);
        assert(arquivo_ordenado != NULL);
        FILE *arquivo_ordenado_final = fopen(argv[2], "wb");

        while (!feof(arquivo_ordenado))
        {
            int buffer[MAX_INTS] = {0};
            if (fread(&buffer, sizeof(*buffer), sizeof(buffer) / sizeof(*buffer), arquivo_ordenado))
            {
                    fwrite(&buffer, sizeof(*buffer), MAX_INTS, arquivo_ordenado_final);
            }
            printf("banana\n");
        }

        fclose(arquivo_ordenado);
        fclose(arquivo_ordenado_final);
    }


    queueDestroy(file_queue);

    return (EXIT_SUCCESS);
}
