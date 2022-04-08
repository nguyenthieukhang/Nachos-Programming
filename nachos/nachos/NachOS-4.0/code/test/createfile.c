#include "syscall.h"

int main()
{

    char file_name[255];
    int length;
    int res;

    PrintString("Enter the length of file name: ");
    length = ReadNum();
    PrintString("Enter the file name: ");
    ReadString(file_name, length);
    res = Create(file_name);
    if (res == -1)
        PrintString("File cannot be created\n");
    else
        PrintString("File created successfully\n");
    Halt();
    return 0;
}