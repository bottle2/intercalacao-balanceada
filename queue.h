typedef struct FileNode FileNode;
typedef struct FileQueue FileQueue;
#define TAM_NOME_MAX 10000

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
