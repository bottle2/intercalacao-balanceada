#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "config.h"
#include "merge.h"
#include "queue.h"
#include "try.h"
#include "util.h"

static FileQueue * run_queue (char filename[]);

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
        merge_queue(file_queue);

        char * f_name = NULL;
        f_name = filePop(file_queue);
        rename(f_name, argv[2]);
    }

    queueDestroy(file_queue);

    return (EXIT_SUCCESS);
}

static FileQueue * run_queue(char filename[])
{
    FILE     *arquivo_original;
    FileQueue *file_queue        = fileCreate();

    arquivo_original = TRY_OPEN(filename, "rb");
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

        fwrite(&buffer, sizeof(*buffer), MAX_INTS, fp);
        fclose(fp);
        filePush(file_queue, fname);
    }

    fclose(arquivo_original);

    return file_queue;
}
