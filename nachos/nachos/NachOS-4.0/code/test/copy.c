#include "syscall.h"

int main(){
    char file1_name[255],file2_name[255];
    int length1, length2;
    int res;
    PrintString("Enter the length of file name 1: ");
    length1 = ReadNum();
    PrintString("Enter the file name 1: ");
    ReadString(file1_name, length1);

    PrintString("Enter the length of file name 2: ");
    length2 = ReadNum();
    PrintString("Enter the file name 2: ");
    ReadString(file1_name, length2);

    //res = Copy(file1_name, file2_name);
}