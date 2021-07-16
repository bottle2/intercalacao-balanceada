#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#include "config.h"
#include "try.h"

FILE * _try_open(char path[], char mode[], char source[], int line, char const function[])
{
    FILE *file  = NULL;
    int   try_i = 0;

    for (try_i = 0; !(file = fopen(path, mode)) && try_i < MAX_TRIES; try_i++)
    {
        fprintf(stderr
                , "fopen(\"%s\", \"%s\") set errno to %d at line %d of %s in %s(), attempt #%d.\n"
                , path, mode, errno, line, source, function, try_i + 1);
    }

    if (NULL == file)
    {
        exit(EXIT_FAILURE);
    }
    else
    {
        return file;
    }
}
