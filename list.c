#include <stdio.h>
#include <stdlib.h>

#include "list.h"

struct FileNode
{
    struct FileNode *next;
    FILE            *run;
};

struct FileList
{
    FileNode *first;
    FileNode *last;
    FileNode *atual;
    int       tamanho;
};


FileList * FileCreate(void)
{
    FileList *list = malloc(sizeof(FileList));

    list->first   = NULL;
    list->last    = NULL;
    list->atual   = NULL;
    list->tamanho = 0;

    return (list);
}

void FileDestroy(FileList *list)
{
    free(list);
}

FileNode *FileFirst(FileList *list)
{
}

FileNode *FilePush(FileList *list)
{
}
