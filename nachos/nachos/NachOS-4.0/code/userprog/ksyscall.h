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
#include "synchconsole.h"
#include <stdlib.h>

#define MAX_NUM_LENGTH 11
char buffer[MAX_NUM_LENGTH + 1];
#define INT_MIN -2147483647 - 1

/*******HELPER******/

char SysReadChar() {
  return kernel->synchConsoleIn->GetChar();
}

void readString() {
  // input first character to check "null" input
  char c = kernel->synchConsoleIn->GetChar();
  if (c == EOF) {
    DEBUG(dbgSys, "Unexpected end of file - number expected");
    return;
  }
  if (c == char(9) || c == char(10) || c == char(13) || c == ' ') {
    DEBUG(dbgSys, "Unexpected white space - number expected");
    return;
  }

  // read number until splitting character met
  int bufferSize = 0;
  while (c != EOF && c != char(9) && c != char(10) && c != char(13) && c != ' ') {// not EOF or white space
    if (bufferSize == MAX_NUM_LENGTH) {
      DEBUG(dbgSys, "Number is too long - " << MAX_NUM_LENGTH << " characters long number expected");
      return;
    }
    buffer[bufferSize++] = c;
    c = kernel->synchConsoleIn->GetChar();
  }

  // assign end of string character
  buffer[bufferSize] = '\0';
}

bool isEqual(int num, const char* str) {
  if (num < 0 && str[0] != '-' || num > 0 && str[0] == '-' || num == 0) return false;
  if (num < 0) num = -num, ++str;
  for (int i = strlen(str) - 1; i >= 0 && str[i] != '-'; --i, num /= 10)
    if (num % 10 != str[i] - '0') return false;
  return true;
}
/*******HELPER******/

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
    buffer[i]=SysReadChar();
  }
  buffer[length]='\0';
  return buffer;
}

void SysPrintString(char* str, int length) {
  for(int i=0;i<length;i++)
  {
    kernel->synchConsoleOut->PutChar(str[i]);
  }
}

int SysReadNum() {
  readString();

  if (strlen(buffer) == 0) {
    DEBUG(dbgSys, "Expected number but no input read");
    return 0;
  }
  if (strcmp(buffer, "-2147483648") == 0) return INT_MIN;
  if (strcmp(buffer, "0") == 0) return 0;

  bool isNegative = buffer[0] == '-';
  bool isLeading = true;
  int nLeadingZero = 0;

  int num = 0;

  for (int i = isNegative; buffer[i]; ++i) {
    if (buffer[i] < '0' || '9' < buffer[i]) {
      DEBUG(dbgSys, "Expected number but " << buffer << " found");      
      return 0;
    }
    if (buffer[i] == '0' && isLeading) ++nLeadingZero;
    else if (buffer[i] != '0') isLeading = false;
    num = num * 10 + (buffer[i] - '0');
  }

  if (nLeadingZero > 0) {
    DEBUG(dbgSys, "Expected number but " << buffer << " found");
    return 0;
  }

  if (isNegative) num = -num;

  if (isEqual(num, buffer)) return num;
  else {
    DEBUG(dbgSys, "Expected int32 number but " << buffer << " found");
    return 0;
  }
}

void SysPrintNum(int number) {
  if (number == 0) {
    kernel->synchConsoleOut->PutChar('0');
    return;
  }
  if (number == INT_MIN) {
    for (int i = 0; i < 11; ++i)
      kernel->synchConsoleOut->PutChar("-2147483648"[i]);
    return;    
  }
  if (number < 0) {
    kernel->synchConsoleOut->PutChar('-');
    number = -number;
  }
  int bufferSize = 0;
  for (; number; number /= 10) buffer[bufferSize++] = number % 10 + '0';
  for (int i = bufferSize - 1; i >= 0; --i) kernel->synchConsoleOut->PutChar(buffer[i]);
}

void SysPrintChar(char character) {
  kernel->synchConsoleOut->PutChar(character);
}

char* User2System(char *buffer) {
  int len = strlen(buffer);
  char *sys_buffer = new char[len];
  strcpy(sys_buffer, buffer);
  return sys_buffer;
}

int Create(char *name) {
  char *sys_name = User2System(name);
  if (!kernel->fileSystem->Create(sys_name)) {
    DEBUG(dbgSys, "Create failed");
    return -1;
  }
  return 0;
}

OpenFileId Open(char *name) {
}

#endif /* ! __USERPROG_KSYSCALL_H__ */