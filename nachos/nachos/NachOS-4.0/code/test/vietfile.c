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
        res = Write("Destruction of the world is imminent", 20, id);
        if (res == -1)
        {
            PrintString("Error writing file\n");
        }
        else
        {
            PrintString("File write successfully\n");
        }
    }
    Halt();
    return 0;
}