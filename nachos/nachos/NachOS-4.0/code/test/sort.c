#include "syscall.h"

int a[100]; 

void swap(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}
  
// An optimized version of Bubble Sort
void bubbleSortAscending(int n)
{
   int i, j;
   int swapped;
   for (i = 0; i < n-1; i++)
   {
     swapped = 0;
     for (j = 0; j < n-i-1; j++)
     {
        if (a[j] > a[j+1])
        {
           swap(&a[j], &a[j+1]);
           swapped = 1;
        }
     }
  
     // IF no two elements were swapped by inner loop, then break
     if (swapped == 0)
        break;
   }
}

void bubbleSortDescending(int n)
{
   int i, j;
   int swapped;
   for (i = 0; i < n-1; i++)
   {
     swapped = 0;
     for (j = 0; j < n-i-1; j++)
     {
        if (a[j] < a[j+1])
        {
           swap(&a[j], &a[j+1]);
           swapped = 1;
        }
     }
  
     // IF no two elements were swapped by inner loop, then break
     if (swapped == 0)
        break;
   }
}

int 
main() {
    int n, i, order;
    PrintString("Please enter the size of the array (less than 100)?\n");
    n = ReadNum();
    if(n>=100) {
        Halt();
    }
    PrintString("The user input: ");
    PrintNum(n);
    PrintString("\nPlease enter the array elements (space seperated no endline!)?\n");

    for(i=0; i<n; i++) {
        a[i] = ReadNum();
    }
    PrintString("Please enter if you want to sort in ascending or descending order. 1 is for ascending and 0 otherwise\n");

    order = ReadNum();
    if(order == 1) {
        bubbleSortAscending(n);
    }
    else if(order == 0){
        bubbleSortDescending(n);
    }
    else {
        PrintString("Input only 1 and 0!\n");
        Halt();
    }
    
    PrintString("The array after sorting:\n");
    for(i=0; i<n; i++) {
        PrintNum(a[i]);
        PrintChar(' ');
    }

    Halt();
}