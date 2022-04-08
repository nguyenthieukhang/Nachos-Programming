#include "syscall.h"

int main()
{
    int res = Open("myfile.txt");
    if (res == -1)
    {
        PrintString("Open failed\n");
    }
    else
    {
        PrintString("Open succeeded\n");
        PrintNum(res);
    }
    Halt();
    return 0;
}