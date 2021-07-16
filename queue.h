#ifndef QUEUE_H
#define QUEUE_H

typedef struct FileNode FileNode;
typedef struct FileQueue FileQueue;

FileQueue *fileCreate  (void);
void      queueDestroy (FileQueue *queue);
void      filePush    (FileQueue *queue, char * file);
FileNode *fileNext    (FileQueue *queue);
FileNode *fileUpdate  (FileQueue *queue);
FileNode *fileReset   (FileQueue *queue);
FileNode *fileSmallest(FileQueue *queue);
FileNode *updateSmallest(FileQueue *queue);
char* filePop(FileQueue *queue);

int getQueueSize(FileQueue *queue);
int getQueueNewId(FileQueue *queue);

#endif /* QUEUE_H */
