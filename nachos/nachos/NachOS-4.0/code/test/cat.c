#include "syscall.h"
int main()
{
    char file_name[255],file_content[255];
    int length;
    int res;
    PrintString("Enter the length of file name: ");
    length = ReadNum();
    PrintString("Enter the file name: ");
    ReadString(file_name, length);

    //res = Read(file_name);
    if (res == -1)
        PrintString("File cannot be read\n");
    else
        PrintString("File read successfully\n");
    // do 
    // {
        // PrintString(filecontent);
    // } while (True);//not EOF - depending on Read() implementation
    
    Halt();
    return 0;
}