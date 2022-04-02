#include "syscall.h"

int
main()
{
  char str[] = "Hello\n";
  PrintString(str);

  Halt();
  /* not reached */
}