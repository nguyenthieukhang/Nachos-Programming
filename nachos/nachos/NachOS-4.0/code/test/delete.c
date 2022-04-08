#include "syscall.h"

int main(){
    char file_name[255];
    int length;
    int res;

    Create("myfile.txt");
    PrintString("Enter the length of file name: ");
    length = ReadNum();
    PrintString("Enter the file name: ");
    ReadString(file_name, length);

    res = Remove(file_name);
    if (res == -1)
        PrintString("File cannot be removed\n");
    else
        PrintString("File removed successfully\n");
    Halt();
}