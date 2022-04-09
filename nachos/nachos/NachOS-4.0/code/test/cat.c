#include "syscall.h"
int main()
{
    char file_name[255],file_content[255];
    int length;
    int res;
    int file_id;
    int byte_read;

    PrintString("Enter the length of file name: ");
    length = ReadNum();
    PrintString("Enter the file name: ");
    ReadString(file_name, length);

    file_id = Open(file_name);
    if (file_id == -1) {
        PrintString("Unable to open file\n");
        return 0;
    }

    PrintString(file_name);
    PrintString("\n");

    do 
    {
        byte_read = Read(file_content, 255, file_id);
        PrintString(file_content);
    } while (byte_read == 255);
    
    Close(file_name);
    Halt();
    return 0;
}