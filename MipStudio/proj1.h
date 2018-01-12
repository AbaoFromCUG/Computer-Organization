#include <stdio.h>
#include <stdlib.h>
#include "computer.h"
#undef mips                     /* gcc already has a def for mips */

#define MAXNUMINSTRS 1024       /* max # instrs in a program */
#define MAXNUMDATA 3072         /* max # data words */

struct SimulatedComputer {
    int memory [MAXNUMINSTRS+MAXNUMDATA];
    int registers [32];
    int pc;
    //打印寄存器，打印内存，可交互，ｄｅｂｕｇ
    int printingRegisters, printingMemory, interactive, debugging;
};

void printInfo (Computer, int changedReg, int changedMem);
void simulateInstr (Computer, unsigned int instr, int *changedReg, int *changedMem);
char * disassembled (unsigned int, unsigned int);
unsigned int contents (Computer, int);  //获得计算器某个地址内的数据
