#include <assert.h>
#include <stdio.h>

#include "config.h"
#include "merge.h"
#include "queue.h"
#include "try.h"

static void merge_files(char **files, int n_file, char destination[]);

void merge_queue(FileQueue *file_queue)
{
    while(getQueueSize(file_queue) > 1)
    {
        char * f1_name = filePop(file_queue);
        char * f2_name = filePop(file_queue);
        char fname[TAM_NOME_MAX];
        sprintf(fname, "%s%c %d", PATH_FILES,'I', getQueueNewId(file_queue));

        merge_files((char *[]){f1_name, f2_name}, 2, fname);

        filePush(file_queue, fname);
    }    
}

static void merge_files(char **files, int n_file, char destination[])
{
	FILE *f1  = TRY_OPEN(files[0], "rb");
	FILE *f2  = TRY_OPEN(files[1], "rb");
        FILE *aux = TRY_OPEN(destination  , "w+b");
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
}
