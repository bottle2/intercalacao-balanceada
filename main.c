#include <assert.h>
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

        char fname[TAM_NOME_MAX];
        sprintf(fname, "%s %c %d", PATH_FILES,'I', getQueueNewId(queue));

        FILE* aux = fopen(fname, "w+b"); 
        char * f1_name = NULL;
        f1_name = filePop(queue);
        char * f2_name = NULL;
        f2_name = filePop(queue);
        FILE* f1  = fopen(f1_name, "rb");
        FILE* f2  = fopen(f2_name, "rb");
        printf("\nlala %s \n", f1_name);

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
        fclose(aux);
        //DELETAR ARQUIVOS
        filePush(queue, fname);
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
        char fname[TAM_NOME_MAX];
        sprintf(fname, "%s %c %d", PATH_FILES,'A', getQueueNewId(file_queue));
        FILE* fp = NULL;
	    while (!(fp = fopen(fname, "w+b")))
        {
            printf("Dando pau: %d\n", errno);
        }
        fwrite(&buffer, sizeof(*buffer), MAX_INTS, fp);
        fclose(fp);
        filePush(file_queue, fname);
    }

    fclose(arquivo_original);

    if(getQueueSize(file_queue) != 0)
    {
        merge_sort(file_queue);

        char * f_name = NULL;
        f_name = filePop(file_queue);
        rename(f_name, argv[2]);
    }


    queueDestroy(file_queue);

    return (EXIT_SUCCESS);
}
