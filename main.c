#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "config.h"
#include "merge.h"
#include "queue.h"
#include "try.h"

#define MAX_INTS 10000

static int         cmp(const void* a, const void* b);
static FileQueue * run_queue (char filename[]);
static void        merge_sort(FileQueue* queue);

int main(int argc, char *argv[])
{
    if(argc != 3) 
    {
        printf("Use %s <arquivo_original> <arquivo_ordenado>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    FileQueue * file_queue = run_queue(argv[1]);

    if(getQueueSize(file_queue) != 0)
    {
#if 0
        merge_sort(file_queue);
#else
        merge_queue(file_queue);
#endif

        char * f_name = NULL;
        f_name = filePop(file_queue);
        rename(f_name, argv[2]);
    }

    queueDestroy(file_queue);

    return (EXIT_SUCCESS);
}

static int cmp(const void* a, const void* b){
    return( *((int*)a) - *((int*)b) );
}

static FileQueue * run_queue(char filename[])
{
    FILE     *arquivo_original;
    FileQueue *file_queue        = fileCreate();

    arquivo_original = TRY_OPEN(filename, "rb");
    //while (!(arquivo_original = fopen(filename, "rb")));
    int buffer[MAX_INTS] = {0};

    while (MAX_INTS == fread(&buffer, sizeof(*buffer), sizeof(buffer) / sizeof(*buffer), arquivo_original) && !feof(arquivo_original))
    {
        if (ferror(arquivo_original))
        {
            clearerr(arquivo_original);
        }
        qsort(&buffer, MAX_INTS, sizeof(*buffer), cmp);
        char fname[TAM_NOME_MAX];
        sprintf(fname, "%s%c %d", PATH_FILES,'A', getQueueNewId(file_queue));
        FILE* fp = NULL;
        
	fp = TRY_OPEN(fname, "w+b");
        //while (!(fp = fopen(fname, "w+b")));

        fwrite(&buffer, sizeof(*buffer), MAX_INTS, fp);
        fclose(fp);
        filePush(file_queue, fname);
    }

    fclose(arquivo_original);

    return file_queue;
}

#if 0
static void merge_sort(FileQueue* queue){
    
    while(getQueueSize(queue) > 1)
    {
        FILE* f1  = NULL;
        FILE* f2  = NULL;
        FILE* aux = NULL; 

        char * f1_name = filePop(queue);
        char * f2_name = filePop(queue);
        char fname[TAM_NOME_MAX];
        sprintf(fname, "%s%c %d", PATH_FILES,'I', getQueueNewId(queue));

	f1  = TRY_OPEN(f1_name, "rb");
	f2  = TRY_OPEN(f2_name, "rb");
        aux = TRY_OPEN(fname  , "w+b");
        //while (!(f1 = fopen(f1_name, "rb")));
        //while (!(f2 = fopen(f2_name, "rb")));
        //while (!(aux = fopen(fname, "w+b")));

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
#endif
