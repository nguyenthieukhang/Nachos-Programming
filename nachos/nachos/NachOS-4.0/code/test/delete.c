#include "syscall.h"
#define FALSE 0

int main(){
    char file_name[255];
    int length;
    int res;

    PrintString("Enter the length of file name: ");
    length = ReadNum();
    PrintString("Enter the file name: ");
    ReadString(file_name, length);

    res = Remove(file_name);
    if (res == FALSE)
        PrintString("File cannot be removed\n");
    else
        PrintString("File removed successfully\n");
    Halt();
}