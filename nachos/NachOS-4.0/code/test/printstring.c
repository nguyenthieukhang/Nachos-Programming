#include "syscall.h"

int
main()
{
  char str[] = "Hello, world!\n";
  PrintString(str);

  Halt();
  /* not reached */
}