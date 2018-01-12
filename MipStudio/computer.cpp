//#include "proj3.h"
#include "computer.h"
#include "proj1.h"
/*
 *  Return an initialized computer with the stack pointer set to the
 *  address of the end of data memory, the remaining registers initialized
 *  to zero, and the instructions read from the given file.
 *  The other arguments all govern how the program interacts with the user.
 */ 
Computer newComputer (FILE* filein, int printingRegisters, int printingMemory, int debugging, int interactive) {
    int k;
    unsigned int instr;
    Computer mips = (Computer) malloc (sizeof(struct SimulatedComputer));
    //把模拟硬件的每个寄存器初始化为０
    for (k=0; k<32; k++)
        mips->registers[k] = 0;
    
    /* stack pointer starts at end of data area and grows down */
    //将数据域和堆栈空间的指针初始化
    mips->registers[29] = 0x00400000 + (MAXNUMINSTRS+MAXNUMDATA)*4;

    k = 0;
    while (1) {
        instr = 0;
        unsigned char temp = 0;
        int i;
        for (i = 0; i < 4; i++) {
            if (!fread(&temp, 1, 1, filein)) {
                i = -1;
                break;
            }
            //这段代码有点意思，比如
            //当前文件中，四位是1010
            //inster|=(temp*2^(i*8))
            //1000
            instr |= temp << (i << 3);
        }
        if (i == -1)
            break;
        mips->memory[k] = instr;
        k++;
        if (k > MAXNUMINSTRS) {
            fprintf (stderr, "Program too big (%d instructions, only %d allowed).\n", k, MAXNUMINSTRS);
            exit (1);
        }
    }

    mips->printingRegisters = printingRegisters;
    mips->printingMemory = printingMemory;
    mips->interactive = interactive;
    mips->debugging = debugging;
    return mips;
}

/*
 *  Run the simulation.
 */
void simulate (Computer mips) {
    char s[10];  /* used for handling interactive input */
    unsigned int instr;
    int changedReg, changedMem;

    mips->pc = 0x00400000;
    while (1) {
        if (mips->interactive) {
            //i参数启动这个
            printf ("> ");
            fgets(s, 10, stdin);
            //如果输入的是q 那么就退出交互的shell
            if (s[0] == 'q')
                return;
        }

        //
        //得到指令,得到的是３２位的无符号int
        instr = contents (mips, mips->pc);
        printf ("Executing instruction at %8.8x: %8.8x\n", mips->pc, instr);
        printf ("\t%s\n", disassembled (instr, mips->pc));
        //执行指令
        simulateInstr (mips, instr, &changedReg, &changedMem);
        printInfo (mips, changedReg, changedMem);
    }
}

/*
 *  Print relevant information about the state of the computer.
 *  changedReg is the index of the register changed by the instruction
 *  being simulated.  If changedReg is -1, no register was updated by
 *  the simulated instruction, i.e. it was a branch, a jump, or a store).
 *  changedMem is the address of the memory location changed by the
 *  simulated instruction.  For anything but a store, changedMem will be -1.
 *  Previously initialized flags indicate whether to print all the
 *  registers or just the one that changed, and whether to print
 *  all the nonzero memory or just the memory location that changed.
 */
void printInfo (Computer mips, int changedReg, int changedMem) {
    int k, addr;
    printf ("New pc = %8.8x\n", mips->pc);
    if (!mips->printingRegisters && changedReg == -1) printf ("No register was updated.\n");
    else if (!mips->printingRegisters) printf ("Updated r%d to %8.8x\n", changedReg, mips->registers[changedReg]);
    else {
        for (k=0; k<32; k++) {
            printf ("r%2d: %8.8x  ", k, mips->registers[k]);
            if ((k+1)%4 == 0) printf ("\n");
        }
    }

    if (!mips->printingMemory && changedMem == -1) printf ("No memory location was updated.\n");
    else if (!mips->printingMemory) printf ("Updated memory at address %8.8x to %8.8x\n", changedMem, contents (mips, changedMem));
    else {
        printf ("Nonzero memory\n");
        printf ("ADDR     CONTENTS\n");

        for (addr = 0x00400000+(MAXNUMINSTRS << 2); addr < 0x00400000+((MAXNUMINSTRS+MAXNUMDATA) << 2); addr = addr+4) {
            if (contents (mips, addr) != 0) printf ("%8.8x  %8.8x\n", addr, contents (mips, addr));
        }
    }
    printf ("\n");
}

/*
 *  Return the contents of memory at the given address.
 */
unsigned int contents (Computer mips, int addr) {
    int index = (addr-0x00400000)/4;
    if (((addr & 0x3) != 0) || (index < 0) || (index >= (MAXNUMINSTRS+MAXNUMDATA))) {
        //非法访问，
        printf("Invalid Address: %8.8x", addr);
        exit(0);
    }
    //

    return mips->memory[index];
}
