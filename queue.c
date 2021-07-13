#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"

struct FileNode
{
    struct FileNode    *next;
    char               *fileName;
};

struct FileQueue
{
    FileNode *first;
    FileNode *last;
    FileNode *smallest;
    int       size;
    int       newId;
};

static void freeNode(FileNode* node);
static FileNode *createNode(char* file);

FileQueue * fileCreate(void)
{
    FileQueue *queue = malloc(sizeof(FileQueue));
    assert(queue);

    queue->first   = NULL;
    queue->last    = NULL;
    queue->smallest= NULL;
    queue->size = 0;
    queue->newId = 0;

    return (queue);
}

void queueDestroy(FileQueue *queue)
{
    FileNode* aux = NULL;
    FileNode* f = queue->first;
    while(f != NULL){
        aux = f->next;
        freeNode(f);
        f = aux;
    }
    free(queue);
}

static FileNode *createNode(char* fileName)
{
    FileNode* fn = (FileNode*) malloc(sizeof(FileNode));
    assert(fn);
    printf("\nTAMANHO FODA DOS ANIMES: %i do arquivo %s\n", strlen(fileName), fileName);
    fn->fileName = (char*) malloc(sizeof(char)*strlen(fileName));
    strcpy(fn->fileName, fileName);
    fn->next = NULL;
    return fn;
}

char* filePop(FileQueue *queue)
{
    if(queue->first == NULL) return NULL;
    if(queue->first == queue->last)queue->last = NULL;

    FileNode* aux = queue->first;
    char * str = aux->fileName;
    aux->fileName = NULL;
    queue->first = queue->first->next;
    queue->size -= 1;
    freeNode(aux);
    return str;//twice
}

void filePush(FileQueue *queue, char* file)
{
    FileNode* fn = createNode(file);
    if(queue->last == NULL)
    {
        queue->first = fn;
        queue->last = fn;
    }
    else
    {
        queue->last->next = fn;
        queue->last = fn;
    }
    queue->size += 1;
}

static void freeNode(FileNode* node)
{
    free(node);
}
int getQueueSize(FileQueue *queue)
{
    return queue->size;
}
int getQueueNewId(FileQueue *queue)
{
    int aux = queue->newId;
    queue->newId += 1;
    return aux;
}
