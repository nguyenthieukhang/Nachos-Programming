#include "filetable.h"

FileTable::FileTable() {
    files = new OpenFile*[MAX_NUMBER_OF_FILES];
    openMode = new int[MAX_NUMBER_OF_FILES];

    // The default first two files are console in & out
    fileCount = 2;
    openMode[ConsoleInputMacro] = MODE_READ;
    openMode[ConsoleOutputMacro] = MODE_WRITE;

    // All other files are NULL
    for (int i = 2; i < MAX_NUMBER_OF_FILES; ++i)
        files[i] = NULL;
}

FileTable::~FileTable() {
    for (int i = 0; i < fileCount; ++i)
        delete files[i];
    delete[] files;
    delete[] openMode;
}

OpenFileId FileTable::Insert(char *fileName, int openMode) {
    int freeIndex = -1;
    int fileDescriptor = -1;

    for (int i = 2; i < MAX_NUMBER_OF_FILES; ++i)
        if (!files[i]) {
            freeIndex = i;
            break;
        }
    
    if  (freeIndex == -1) return -1;
    
    switch (openMode) {
    case MODE_READ:
        fileDescriptor = OpenForRead(fileName); // OpenForRead hasn't got definition
        break;
    
    case MODE_WRITE:
        fileDescriptor = OpenForWrite(fileName);
        break;

    case MODE_RW:
        fileDescriptor = OpenForReadWrite(fileName, false);
        break;

    default:
        // assert error
        break;
    }

    if (fileDescriptor == -1) return -1;

    files[freeIndex] = new OpenFile(fileDescriptor);
    this.openMode[freeIndex] = openMode;

    return freeIndex;
}