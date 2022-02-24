/**************************************************************
 *
 * userprog/ksyscall.h
 *
 * Kernel interface for systemcalls 
 *
 * by Marcus Voelp  (c) Universitaet Karlsruhe
 *
 **************************************************************/

#ifndef __USERPROG_KSYSCALL_H__ 
#define __USERPROG_KSYSCALL_H__ 

#include "kernel.h"
#include <stdlib.h>




void SysHalt()
{
  kernel->interrupt->Halt();
}


int SysAdd(int op1, int op2)
{
  return op1 + op2;
}

int RandomNum()
{
  return rand();
}

char* ReadBuffer(int length)
{
  char* buffer = new char[length+1];
  for(int i=0;i<length;i++)
  {
    buffer[i]=ReadChar();
  }
  buffer[length]='\0';
  return buffer;
}

char ReadChar()
{
}



#endif /* ! __USERPROG_KSYSCALL_H__ */
