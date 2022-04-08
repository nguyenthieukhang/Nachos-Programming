#include "syscall.h"

int main()
{
    OpenFileId id;
    int closeId;
    id = Open("myfile.txt");
    if (id == -1)
    {
        PrintString("Open failed\n");
    }
    else
    {
        PrintString("Open succeeded\n");
        PrintNum(id);
    }
    closeId = Close(id);
    if (closeId == -1)
    {
        PrintString("Close failed\n");
    }
    else
    {
        PrintString("Close succeeded\n");
        PrintNum(closeId);
    }
    Halt();
    return 0;
}