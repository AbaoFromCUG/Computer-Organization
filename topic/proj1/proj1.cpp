#include "proj1.h"
#include "computer.h"
/*
 *  Return a string containing the disassembled version of the given
 *  instruction.  You absolutely MUST follow the formatting instructions
 *  given in the assignment.  Note that the string your return should
 *  not include a tab at the beginning or a newline at the end since
 *  those are added in computer.c where this function is called.
 *
 *  Finally you are responsible for managing the memory associated with
 *  any string you return.  If you use malloc, you will somehow need to
 *  free the memory later (note that you cannot modify computer.c).
 *  Hint: static or global variables.
 */
char * disassembled (unsigned int instr, unsigned int pc) {
    /* You replace this code by the right stuff. */
	//if (/*instruction isn't supported */) exit (0); // Your program must exit when an unsupported instruction is detected
  	return "";
}

/*
 *  Simulate the execution of the given instruction, updating the
 *  pc appropriately.
 *
 *  If the instruction modified a register--i.e. if it was lw,
 *  addu, addiu, subu, sll, srl, and, andi, or, ori, lui, or slt
 *  to list a few examples-- return the index of the modified
 *  register in *changedReg, otherwise return -1 in *changedReg.
 *  Note that you should never return 0 in *changedReg, since
 *  $0 cannot be changed!  Note that even if the instruction
 *  changes the register back to it's old value
 *  (e.g. addu $3, $3, $0) the destination register ($3 in the
 *  example) should be marked changed!
 *
 *  If the instruction was sw, return the address of the
 *  updated memory location in *changedMem, otherwise return -1
 *  in *changedMem.
 */
void simulateInstr (Computer mips, unsigned int instr, int *changedReg, int *changedMem) {
    /* You replace this code by the right stuff. */
    mips->pc = mips->pc + 4;
    *changedReg = -1;
    *changedMem = -1;	
}
