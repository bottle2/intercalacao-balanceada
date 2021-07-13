typedef struct FileNode FileNode;
typedef struct FileQueue FileQueue;

FileQueue *fileCreate  (void);
void      queueDestroy (FileQueue *queue);
FileNode *filePush    (FileQueue *queue, FILE * file);
FileNode *fileNext    (FileQueue *queue);
FileNode *fileUpdate  (FileQueue *queue);
FileNode *fileReset   (FileQueue *queue);
FileNode *fileSmallest(FileQueue *queue);
FileNode *updateSmallest(FileQueue *queue);
FILE* filePop(FileQueue *queue);

int getQueueSize(FileQueue *queue);
int getQueueNewId(FileQueue *queue);
