#include "syscall.h"

int
main()
{
    // "Hello, This is group Gululu. There are three members in our group:\n 
    // 1. 19125051 - Nguyen Thieu Khang\n 
    // 2. 19125073 - Nguyen Quoc Khanh Tuyen\n 
    // 3. 19125011 - Khau Dang Nhat Minh\n 
    // Our group is very hard-working. We have been fixing this NachOS for many days.\n
    // We always face difficulty compiling the NachOS and dealing with Ubuntu.\n 
    // But we did not give up. We are very tired but we never give up. And now we could run the code.\n
    // When the code run we celebrate!\n";
    // "This is a description of the sort.c program.\n
    // The program initializes an array sorted in reverse order.\n
    // Then the program use a sorting algorithm to sort the numbers in ascending order.\n
    // The sorting algorithm tries all possible pairs of indexes and swaps the numbers at those position if there is a violation.\n";
    // "This is a description of the ascii.c program.\n
    // The program goes through all 256 ascii chracters and prints out all of them.\n";

    PrintString("\n\n\nHello, This is group Gululu. There are three members in our group:\n");
    PrintString("1. 19125051 - Nguyen Thieu Khang\n");
    PrintString("2. 19125073 - Nguyen Quoc Khanh Tuyen\n");
    PrintString("3. 19125011 - Khau Dang Nhat Minh\n");
    PrintString("Our group is very hard-working. We have been fixing this NachOS for many days.\n");
    PrintString("We always face difficulty compiling the NachOS and dealing with Ubuntu.\n");
    PrintString("But we did not give up. We are very tired but we never give up. And now we could run the code.\n");
    PrintString("When the code run we celebrate!\n\n\n");
    PrintString("--------------------------------------------------------------------------------------\n");
    PrintString("This is a description of the sort.c program.\n");
    PrintString("The program initializes an array sorted in reverse order.\n");
    PrintString("Then the program use a sorting algorithm to sort the numbers in ascending order.\n");
    PrintString("The sorting algorithm tries all possible pairs of indexes and swaps the numbers at those position if there is a violation.\n");
    PrintString("--------------------------------------------------------------------------------------\n");
    PrintString("This is a description of the ascii.c program.\n");
    PrintString("The program goes through all 256 ascii chracters and prints out all of them.\n");

    Halt();
    /* not reached */
}
