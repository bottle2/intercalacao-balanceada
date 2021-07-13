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
        FILE* f1 = filePop(queue);
        FILE* f2 = filePop(queue);
        FILE* ctr = NULL;
        rewind(f1);rewind(f2);
        char fname[100];
        sprintf(fname, "%s %c %d", PATH_FILES,'I', getQueueNewId(queue));
        FILE* aux = fopen(fname, "w+b"); 
        //mergeson
        
        int e1 = 0; 
        int e2 = 0;
        int* ex = NULL;
        while(fread(&e1, sizeof(e1), 1, f1) != 0 && fread(&e2, sizeof(e2), 1, f2) != 0)
        {
            if(e1 > e2)
            {
                ex = &e2;
                fseek(f1,-4,SEEK_CUR);
            }
            else
            {
                ex = &e1;
                fseek(f2,-4,SEEK_CUR);
            }
            fwrite(ex, sizeof(int), 1, aux);
            printf("%i %i %i\n", e1, e2 , *ex);
        }
        if(!feof(f1)) ctr = f1;else ctr = f2;

        int e = 0; 
        while(fread(&e, sizeof(e), 1, ctr) != 0)
        {
            printf("lele");
            fwrite(&e, sizeof(int), 1, aux);
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

    for (int run_i = 0; !feof(arquivo_original); run_i++)
    {
        int buffer[MAX_INTS] = {0};
        if (fread(&buffer, sizeof(*buffer), sizeof(buffer) / sizeof(*buffer), arquivo_original))
        {        
            qsort(&buffer, MAX_INTS, sizeof(*buffer), cmp);
            char fname[100];
            sprintf(fname, "%s %c %d", PATH_FILES,'A', run_i);
            FILE* fp = fopen(fname, "w+b");
            fwrite(&buffer, sizeof(*buffer), MAX_INTS, fp);
            filePush(file_queue, fp);
        }
    }

    fclose(arquivo_original);

    if(getQueueSize(file_queue) != 0)
    {
        merge_sort(file_queue);
    }

    queueDestroy(file_queue);

    return (EXIT_SUCCESS);
}
