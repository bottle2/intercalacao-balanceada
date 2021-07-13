#include <stdio.h>
#include <stdlib.h>

#include "queue.h"

struct FileNode
{
    struct FileNode *next;
    FILE            *run;
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
static FileNode *createNode(FILE* file);

FileQueue * fileCreate(void)
{
    FileQueue *queue = malloc(sizeof(FileQueue));

    queue->first   = NULL;
    queue->last    = NULL;
    queue->smallest= NULL;
    queue->size = 0;
    queue->newId = 0;

    return (queue);
}

void queueDestroy(FileQueue *queue)
{
    int count;
    FileNode* aux = NULL;
    FileNode* f = queue->first;
    while(f->run != NULL){
        aux = f->next;
        fclose(f->run);
        freeNode(f);
        f = aux;
    }
    free(queue);
}

static FileNode *createNode(FILE * file)
{
    FileNode* fn = (FileNode*) malloc(sizeof(FileNode));
    fn->run = file;
    fn->next = NULL;
    return fn;
}

FileNode *fileSmallest(FileQueue *queue)
{

}

FileNode *updateSmallest(FileQueue *queue)
{
    
}

FILE* filePop(FileQueue *queue)
{
    if(queue->first == NULL) return NULL;
    if(queue->first == queue->last)queue->last = NULL;

    FileNode* aux = queue->first;
    FILE* fl = aux->run;
    queue->first = queue->first->next;
    queue->size -= 1;
    freeNode(aux);
    return fl;
}

FileNode *filePush(FileQueue *queue, FILE * file)
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