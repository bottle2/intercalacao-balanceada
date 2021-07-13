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
    FileNode *smallest;
    int       size;
};

static FileNode *createNode(FILE* file);

FileList * fileCreate(void)
{
    FileList *list = malloc(sizeof(FileList));

    list->first   = NULL;
    list->last    = NULL;
    list->smallest= NULL;
    list->size = 0;

    return (list);
}

void fileDestroy(FileList *list)
{
    free(list);
}

static FileNode *createNode(FILE * file)
{
    FileNode* fn = (FileNode*) malloc(sizeof(FileNode));
    fn->run = file;
    fn->next = NULL;
    return fn;
}

FileNode *fileSmallest(FileList *list)
{

}

FileNode *updateSmallest(FileList *list)
{
    
}

FileNode *filePush(FileList *list, FILE * file)
{
    FileNode* fn = createNode(file);
    if(list->last == NULL)
    {
        list->first = fn;
        list->last = fn;
    }
    else
    {
        list->last->next = fn;
        list->last = fn;
    }
    list->size += 1;
}
