#include "syscall.h"

int main()
{
    int res;
    res = Create("myfile.txt");
    if (res == 0)
    {
        PrintString("Sucess\n");
    }
    else
    {
        PrintString("Fail\n");
    }
    Halt();
    return 0;
}