#include "syscall.h"

int main()
{
    int id;
    char buffer[5];
    int res;
    id = Open("myfile.txt");

    if (id == -1)
    {
        PrintString("Error opening file\n");
    }
    else
    {
        PrintString("File opened successfully\n");
        res = Read(buffer, 5, id);
        if (res == -1)
        {
            PrintString("Error reading file\n");
        }
        else
        {
            PrintString("File read successfully\n");
            PrintString(buffer);
        }
    }
    Halt();
    return 0;
}