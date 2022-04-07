// exception.cc
//	Entry point into the Nachos kernel from user programs.
//	There are two kinds of things that can cause control to
//	transfer back to here from user code:
//
//	syscall -- The user code explicitly requests to call a procedure
//	in the Nachos kernel.  Right now, the only function we support is
//	"Halt".
//
//	exceptions -- The user code does something that the CPU can't handle.
//	For instance, accessing memory that doesn't exist, arithmetic errors,
//	etc.
//
//	Interrupts (which can also cause control to transfer from user
//	code into the Nachos kernel) are handled elsewhere.
//
// For now, this only handles the Halt() system call.
// Everything else core dumps.
//
// Copyright (c) 1992-1996 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation
// of liability and disclaimer of warranty provisions.

#include "copyright.h"
#include "main.h"
#include "syscall.h"
#include "ksyscall.h"
//----------------------------------------------------------------------
// ExceptionHandler
// 	Entry point into the Nachos kernel.  Called when a user program
//	is executing, and either does a syscall, or generates an addressing
//	or arithmetic exception.
//
// 	For system calls, the following is the calling convention:
//
// 	system call code -- r2
//		arg1 -- r4
//		arg2 -- r5
//		arg3 -- r6
//		arg4 -- r7
//
//	The result of the system call, if any, must be put back into r2.
//
// If you are handling a system call, don't forget to increment the pc
// before returning. (Or else you'll loop making the same system call forever!)
//
//	"which" is the kind of exception.  The list of possible exceptions
//	is in machine.h.
//----------------------------------------------------------------------
#define MAX_LENGTH 128

void increasePC()
{
	/* set previous programm counter (debugging only)*/
	kernel->machine->WriteRegister(PrevPCReg, kernel->machine->ReadRegister(PCReg));

	/* set programm counter to next instruction (all Instructions are 4 byte wide)*/
	kernel->machine->WriteRegister(PCReg, kernel->machine->ReadRegister(PCReg) + 4);

	/* set next programm counter for brach execution */
	kernel->machine->WriteRegister(NextPCReg, kernel->machine->ReadRegister(PCReg) + 4);
}

void ExceptionHandler(ExceptionType which)
{
	int type = kernel->machine->ReadRegister(2);

	DEBUG(dbgSys, "Received Exception " << which << " type: " << type << "\n");

	switch (which)
	{
	case SyscallException:
		int resultInteger;
		char resultChar;
		switch (type)
		{
		case SC_Halt:
			DEBUG(dbgSys, "Shutdown, initiated by user program.\n");

			SysHalt();

			ASSERTNOTREACHED();
			break;

		case SC_Add:
			DEBUG(dbgSys, "Add " << kernel->machine->ReadRegister(4) << " + " << kernel->machine->ReadRegister(5) << "\n");

			/* Process SysAdd Systemcall*/
			// int resultAdd;
			resultInteger = SysAdd(/* int op1 */ (int)kernel->machine->ReadRegister(4),
							/* int op2 */ (int)kernel->machine->ReadRegister(5));

			DEBUG(dbgSys, "Add returning with " << resultInteger << "\n");
			/* Prepare Result */
			kernel->machine->WriteRegister(2, (int)resultInteger);

			/* Modify return point */
			increasePC();

			return;

			ASSERTNOTREACHED();

			break;
		case SC_ReadNum:
			DEBUG(dbgSys, "Read an integer (return 0 if not integer)\n");
			resultInteger = SysReadNum();
			DEBUG(dbgSys, "ReadNum returning with " << resultInteger << "\n");
			kernel->machine->WriteRegister(2, resultInteger);
			increasePC();
			return;

			ASSERTNOTREACHED();
			break;

		case SC_PrintNum:
			DEBUG(dbgSys, "Print out an integer\n");
			SysPrintNum(kernel->machine->ReadRegister(4));
			increasePC();
			return;

			ASSERTNOTREACHED();
			break;

		case SC_ReadChar:
			DEBUG(dbgSys, "Read a character\n");
			resultChar = SysReadChar();
			DEBUG(dbgSys, "ReadChar returning with " << resultChar << "\n");
			kernel->machine->WriteRegister(2, (int)resultChar);
			increasePC();
			return;

			ASSERTNOTREACHED();
			break;

		case SC_PrintChar:
			DEBUG(dbgSys, "Print out a character\n");
			SysPrintChar(kernel->machine->ReadRegister(4));
			increasePC();
			return;

			ASSERTNOTREACHED();
			break;
		case SC_RandomNum:
			resultInteger = RandomNum();
			kernel->machine->WriteRegister(2, (int)resultInteger);
			increasePC();
			return;
			ASSERTNOTREACHED();
			break;

		case SC_ReadString:
			int address;
			address = kernel->machine->ReadRegister(4);
			int length;
			length = kernel->machine->ReadRegister(5);
			if (address == 0 || length == 0)
			{
				DEBUG(dbgSys, "ReadString: address or length is 0\n");
				increasePC();
				return;
			}
			if (length > 255)
			{
				DEBUG(dbgSys, "ReadString: length is too long\n");
				increasePC();
				return;
			}
			char *buffer;
			buffer = ReadBuffer(length);


			for (int i = 0; i < length; i++)
			{
				kernel->machine->WriteMem(address + i, 1, buffer[i]);
			}
			kernel->machine->WriteMem(address + length, 1, '\0');
			delete[] buffer;
			increasePC();
			return;
			break;
			ASSERTNOTREACHED();

		case SC_PrintString:
			int bufferAddress;
			bufferAddress = kernel->machine->ReadRegister(4);
			length = 0;
			for (int i = 0;; i++)
			{
				int currentChar;
				kernel->machine->ReadMem(bufferAddress + i, 1, &currentChar);
				if (currentChar == 0)
					break;
				length++;
			}
			if(length > MAX_LENGTH) {
				DEBUG(dbgSys, "PrintString: length is too long\n");
				increasePC();
				return;
			}
			char *buffer2;
			buffer2 = new char[length + 1];
			for (int i = 0; i < length; i++)
			{
				int currentChar;
				kernel->machine->ReadMem(bufferAddress + i, 1, &currentChar);
				buffer2[i] = (char)currentChar;
			}
			buffer2[length] = '\0';
			SysPrintString(buffer2, length);
			delete[] buffer2;
			increasePC();
			return;
			break;
			ASSERTNOTREACHED();
		case SC_Seek:
			int position;
			int id;
			int result;
			position = kernel->machine->ReadRegister(4);
			id = kernel->machine->ReadRegister(5);
			if (position<=1)
			{
				DEBUG(dbgSys, "Seek: Cannot seek to console input/output \n");
				increasePC();
			}
			result = kernel->fileSystem->Seek(id, position);
			kernel->machine->WriteRegister(2, result);
			increasePC();
			return;
			break;
		case SC_Remove:
			int filenameAddress;
			filenameAddress = kernel->machine->ReadRegister(4);
			char *filename;
			filename = User2System(filenameAddress);
		default:
			cerr << "Unexpected system call " << type << "\n";
			break;
		}
		break;
	case NoException:
		kernel->interrupt->setStatus(SystemMode);
		break;
	case PageFaultException:
	case ReadOnlyException:
	case BusErrorException:
	case AddressErrorException:
	case OverflowException:
	case IllegalInstrException:
	case NumExceptionTypes:
		cerr << "Exception occurred" << which << "\n";
		SysHalt();
		break;
		ASSERTNOTREACHED();

	default:
		cerr << "Unexpected user mode exception" << (int)which << "\n";
		// SysHalt();
		break;
	}
	// SysHalt();
	ASSERTNOTREACHED();
}