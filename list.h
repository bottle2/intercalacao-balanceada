typedef struct FileNode FileNode;
typedef struct FileList FileList;

FileList *FileCreate  (void);
void      FileDestroy (FileList *list);
FileNode *FilePush    (FileList *list);
FileNode *FileNext    (FileList *list);
FileNode *FileUpdate  (FileList *list);
FileNode *FileReset   (FileList *list);
