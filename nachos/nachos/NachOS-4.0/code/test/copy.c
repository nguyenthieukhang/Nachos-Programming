#include "syscall.h"

int main(){
    char file1_name[255],file2_name[255];
    int length1, length2;
    int res;
    int file1_id, file2_id;
    int byte_read;
    char file1_content[255];
    int file1_size, file2_size;

    PrintString("Enter the length of file name 1: ");
    length1 = ReadNum();
    PrintString("Enter the file name 1: ");
    ReadString(file1_name, length1 + 1);

    PrintString("Enter the length of file name 2: ");
    length2 = ReadNum();
    PrintString("Enter the file name 2: ");
    ReadString(file2_name, length2 + 1);

    file1_name[length1] = '\0';
    file2_name[length2] = '\0';

    file1_id = Open(file1_name);
    file2_id = Open(file2_name);

    file1_size = Seek(-1, file1_id);
    file2_size = Seek(-1, file2_id);
    if (file1_size < file2_size) {
        Close(file2_id);
        Remove(file2_name);
        Create(file2_name);
        file2_id = Open(file2_name);
    }
    Seek(0, file1_id);

    do {
        byte_read = Read(file1_content, 255, file1_id);
        Write(file1_content, byte_read, file2_id);
    } while (byte_read == 255);

    Halt();
    return 0;
}