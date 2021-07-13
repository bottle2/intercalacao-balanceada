typedef struct FileNode FileNode;
typedef struct FileList FileList;

FileList *fileCreate  (void);
void      fileDestroy (FileList *list);
FileNode *filePush    (FileList *list, FILE * file);
FileNode *fileNext    (FileList *list);
FileNode *fileUpdate  (FileList *list);
FileNode *fileReset   (FileList *list);
FileNode *fileSmallest(FileList *list);
FileNode *updateSmallest(FileList *list);
