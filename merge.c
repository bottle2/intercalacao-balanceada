#include <assert.h>
#include <stdio.h>

#include "config.h"
#include "merge.h"
#include "queue.h"
#include "try.h"
#include "util.h"

static void merge_files(char *files[], int n_file, char destination[]);

void merge_queue(FileQueue *file_queue)
{
    while(getQueueSize(file_queue) > 1)
    {
        char *files[MAX_FILES_MERGING] = {0};

        char fname[TAM_NOME_MAX];
        sprintf(fname, "%s%c %d", PATH_FILES,'I', getQueueNewId(file_queue));

        int file_n = MIN(MAX_FILES_MERGING, getQueueSize(file_queue));

        for (int file_i = 0; file_i < file_n; file_i++)
        {
            files[file_i] = filePop(file_queue);
        }

        merge_files(files, file_n, fname);

        for (int file_i = 0; file_i < file_n; file_i++)
        {
#if DELETING_FILES
            remove(files[file_i]);
#endif
        }

        //DELETAR ARQUIVOS

        filePush(file_queue, fname);
    }
}

static void merge_files(char *files[], int n_file, char destination[])
{
	FILE *f1  = TRY_OPEN(files[0], "rb");
	FILE *f2  = TRY_OPEN(files[1], "rb");
        FILE *aux = TRY_OPEN(destination  , "w+b");

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
}
