#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#include "config.h"
#include "merge.h"
#include "queue.h"
#include "try.h"
#include "util.h"

static void merge_files   (char *files[], int n_file, char destination[]);
static int  get_smallest_i(int numbers[], int n_number);

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

        filePush(file_queue, fname);
    }
}

static void merge_files(char *file_names[], int n_file, char destination_name[])
{
    int    n_number = n_file;
    int   *numbers  = malloc(sizeof(*numbers) * n_number);
    FILE **files    = malloc(sizeof(*files) * n_number);

    for (int file_i = 0; file_i < n_file; file_i++)
    {
        files[file_i]   = TRY_OPEN(file_names[file_i], "rb");
        fread(numbers + file_i, sizeof(*numbers), 1, files[file_i]);
    }
    
    FILE *destination = TRY_OPEN(destination_name, "w+b");

    while(n_number > 0)
    {
        int smallest_i = get_smallest_i(numbers, n_number);

        fwrite(numbers + smallest_i, sizeof(*numbers), 1, destination);

        fread(numbers + smallest_i, sizeof(*numbers), 1, files[smallest_i]);

        if (feof(files[smallest_i]))
        {
            FILE *file_temp     = files[smallest_i];
            files[smallest_i]   = files[n_number - 1];
            files[n_number - 1] = file_temp;
            numbers[smallest_i] = numbers[n_number - 1];

            n_number--;
        }
    }

    for (int file_i = 0; file_i < n_file; file_i++)
    {
        fclose(files[file_i]);
    }

    fclose(destination);
    free(numbers);
    free(files);
#if 0
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
#endif
}

static int get_smallest_i(int numbers[], int n_number)
{
    int smallest_i = 0;

    for (int number_i = 0; number_i < n_number; number_i++)
    {
        if (numbers[number_i] < numbers[smallest_i])
        {
            smallest_i = number_i;
        }
    }

    return (smallest_i);
}
