#include "syscall.h"

int main()
{
    char file1_name[255], file2_name[255];
    int length1, length2;
    int res;
    OpenFileId file1;
    OpenFileId file2;
    char file2_content[255];

    PrintString("Enter the length of file name 1: ");
    length1 = ReadNum();
    PrintString("Enter the file name 1: ");
    ReadString(file1_name, length1);

    PrintString("Enter the length of file name 2: ");
    length2 = ReadNum();
    PrintString("Enter the file name 2: ");
    ReadString(file1_name, length2);

    file1 = Open(file1_name);
    file2 = Open(file2_name);

    Seek(-1, file1);

    Read(file2_content, FileSize(file2), file2);
    Write(file2_content, FileSize(file2), file1);

    Close(file1);
    Close(file2);
}