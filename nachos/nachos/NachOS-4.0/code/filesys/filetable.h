#ifndef FILETABLE_H
#define FILETABLE_H

#include "syscall.h"
#include "openfile.h"

#define MAX_NUMBER_OF_FILES 100
#define MODE_READ 0
#define MODE_WRITE 1
#define MODE_RW 2

class FileTable
{
private:

    int *openMode;
    int fileCount;

public:
    OpenFile **files;
    FileTable();
    ~FileTable();

    /**
     * Inserts new file into file table
     *
     * @param fileName Buffer in system space of new file's name
     * @param openMode Open mode of this new file
     *
     * @returns File id in the table or -1 if this file already exists
     */
    OpenFileId Insert(char *fileName, int openMode);
    int Seek(int position, int id);
    int Remove(int id);
    int getSize();
    int getFileDescriptor(int id);
};

#endif // FILETABLE_H