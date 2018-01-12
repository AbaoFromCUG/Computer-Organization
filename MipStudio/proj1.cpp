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
    //如果遇到不支持的寄存
    //首先，32位置的instr，切割int
    static char result[30];
    unsigned int opcode=instr>>26;
    if(opcode==0){
        //这里是R格式的
        //第一步得到各个段的值
        unsigned int rs=(instr>>21)&(31); //跟31* 2^(5+5+5+6)
        unsigned int rt=(instr>>16)&(31);    //跟31* 2^(5+5+6)
        unsigned int rd=(instr>>11)&(31);  //跟31* 2^(5+6)
        unsigned int shamt=(instr>>6)&(31); //跟31* 2^6
        unsigned int funct=instr&(63); //跟111111(unsig int)63做与运算
        //第二步，根据funct的值，判断
        if(funct==32){
            //add
            sprintf(result,"add    $%d, $%d $%d",rd,rs,rt);
        }else if (funct==33) {
            //addu
            sprintf(result,"addu\t$%d, $%d, $%d",rd,rs,rt);
        }else if(funct==34){
            //sub
            sprintf(result,"sub $%d $%d $%d",rd,rs,rt);
        }else if (funct==35) {
            //subu
            sprintf(result,"subu\t$%d, $%d, $%d",rd,rs,rt);
        }else if(funct==36){
            //and
            sprintf(result,"and\t$%d, $%d, $%d",rd,rs,rt);
        }else if (funct==37) {
            //or
            sprintf(result,"or\t$%d, $%d, $%d",rd,rs,rt);
        }else if(funct==38){
            //xor
            sprintf(result,"xor\t$%d,$%d,$%d",rd,rs,rt);
        }else if (funct==39) {
            //nor
            sprintf(result,"nor\t$%d,$%d,$%d",rd,rs,rt);
        }else if (funct==42) {
            //slt
            sprintf(result,"slt\t$%d, $%d, $%d",rd,rs,rt);
        }else if(funct==43){
            //sltu
            sprintf(result,"sltu\t$%d, $%d, $%d",rd,rs,rt);
        }else if(funct==0){
            //sll
            sprintf(result,"sll\t$%d, $%d, %d",rd,rt,shamt);
        }else if (funct==2) {
            //srl
            sprintf(result,"srl\t$%d, $%d, %d",rd,rt,shamt);
        }else if (funct==3) {
            //sra
            sprintf(result,"sra $%d $%d $%d",rd,rs,rt);
        }else if(funct==4){
            //sllv
            sprintf(result,"sllv $%d $%d $%d",rd,rs,rt);
        }else if(funct==6){
            //srlv
            sprintf(result,"srlv $%d $%d $%d",rd,rs,rt);
        }else if(funct==7){
            //srav
            sprintf(result,"srav $%d $%d $%d",rd,rs,rt);
        }else if(funct==8){
            //jr
            sprintf(result,"jr\t$%d",rs);
        }else {
            //如果还有其他的未知指令，那么就,终止
            system("pause");
            throw "error";
        }
    }else if (opcode==2) {
        //j
        unsigned int targetAddr=(instr<<6)>>4;//抹掉高六位,并把后两位为０恢复
        sprintf(result,"j\t0x%08X",targetAddr);
    }else if (opcode==3) {
        //jal
        unsigned int targetAddr=(instr<<6)>>4;//抹掉高六位,并把后两位为０恢复
        sprintf(result,"jal\t0x%08X",targetAddr);
    }else {
        //I格式
        //第一步得到各个段的值
        unsigned int rs=(instr>>21)&(31); //跟31* 2^(5+5+5+6)
        unsigned int rt=(instr>>16)&(31);    //跟31* 2^(5+5+6)
        int immediate=instr&65535;
        if(opcode==8){
            //addi
            int m=immediate;
            if(immediate>>15==1)
                m=immediate-65536; //符号扩展
            sprintf(result,"addi $%d $%d %xd",rt,rs,m);
        }else if (opcode==9) {
            //addiu
            int m=immediate;
            if(immediate>>15==1)
                m=immediate-65536; //符号扩展
            sprintf(result,"addiu\t$%d, $%d, %d",rt,rs,m);
        }else if (opcode==12) {
            //andi
//            int m=immediate;
//            if(immediate>>15==1)
//                m=immediate-65536; //符号扩展
            sprintf(result,"andi\t$%d, $%d, 0x%x",rt,rs,immediate);
        }else if (opcode==13) {
            //ori
            sprintf(result,"ori\t$%d, $%d, 0x%x",rt,rs,immediate);
        }else if (opcode==14) {
            //xori
        }else if(opcode==15){
            //lui
            sprintf(result,"lui\t$%d, 0x%x",rt,immediate);
        }else if (opcode==35) {
            //lw
            int m=immediate;
            if(immediate>>15==1)
                m=immediate-65536; //符号扩展
            sprintf(result,"lw\t$%d, %d($%d)",rt,m,rs);
        }else if(opcode==43){
            //sw
            int m=immediate;
            if(immediate>>15==1)
                m=immediate-65536; //符号扩展
            sprintf(result,"sw\t$%d, %d($%d)",rt,m,rs);
        }else if(opcode==4){
            //beq
            int m=immediate;
            if(immediate>>15==1)
                m=immediate-65536; //符号扩展
            m=m*4;
            m+=4;   //pc自增4

            sprintf(result,"beq\t$%d, $%d, 0x%08x",rs,rt,m+pc);
        }else if(opcode==5){
            //bne
            int m=immediate;
            if(immediate>>15==1)
                m=immediate-65536; //符号扩展
            m=m*4;
            m+=4;   //pc自增4
            sprintf(result,"bne\t$%d, $%d, 0x%08x",rs,rt,m+pc);

        }else if (opcode==10) {
            //slti
            int m=immediate;
            if(immediate>>15==1)
                m=immediate-65536; //符号扩展
        }else if (opcode==11) {
            //sltiu
        }

    }

    return result;
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
    *changedReg=-1;
    *changedMem=-1;
    //首先，32位置的instr，切割int，
    unsigned int opcode=instr>>26;
    if(opcode==0){
        //这里是R格式的
        //第一步得到各个段的值
        unsigned int rs=(instr>>21)&(31); //跟31* 2^(5+5+5+6)
        unsigned int rt=(instr>>16)&(31);    //跟31* 2^(5+5+6)
        unsigned int rd=(instr>>11)&(31);  //跟31* 2^(5+6)
        unsigned int shamt=(instr>>6)&(31); //跟31* 2^6
        unsigned int funct=instr&(63); //跟111111(unsig int)63做与运算

        //第二步，根据funct的值，判断
        if(funct==32){
            //add
            mips->registers[rd]=mips->registers[rs]+mips->registers[rt];
        }else if (funct==33) {
            //addu
            mips->registers[rd]=(unsigned int)mips->registers[rs]+(unsigned int)mips->registers[rt];
        }else if(funct==34){
            //sub
            mips->registers[rd]=mips->registers[rs]-mips->registers[rt];
        }else if (funct==35) {
            //subu
            mips->registers[rd]=(unsigned int)mips->registers[rs]-(unsigned int)mips->registers[rt];
        }else if(funct==36){
            //and
            mips->registers[rd]=mips->registers[rs]&mips->registers[rt];
        }else if (funct==37) {
            //or
            mips->registers[rd]=mips->registers[rs]|mips->registers[rt];
        }else if(funct==38){
            //xor
            mips->registers[rd]=mips->registers[rs]^mips->registers[rt];
        }else if (funct==39) {
            //nor
            mips->registers[rd]=~(mips->registers[rs]|mips->registers[rt]);
        }else if (funct==42) {
            //slt
            mips->registers[rd]=mips->registers[rs]>mips->registers[rt]?1:0;
//            cout<<"____\n\n"<<mips->registers[rd]<<"\n\n";
        }else if(funct==43){
            //sltu
            mips->registers[rd]=(unsigned int)mips->registers[rs]>(unsigned int)mips->registers[rt]?1:0;
        }else if(funct==0){
            //sll
            mips->registers[rd]=mips->registers[rs]<<shamt;
        }else if (funct==2) {
            //srl
            mips->registers[rd]=mips->registers[rs]>>shamt;
        }else if (funct==3) {
            //sra
            mips->registers[rd]=mips->registers[rs]>>shamt|(mips->registers[rs]>>31<<31);
        }else if(funct==4){
            //sllv
            mips->registers[rd]=mips->registers[rt]<<mips->registers[rs];
        }else if(funct==6){
            //srlv
            mips->registers[rd]=mips->registers[rt]>>mips->registers[rs];
        }else if(funct==7){
            //srav
            mips->registers[rd]=mips->registers[rt]>>mips->registers[rs]|(mips->registers[rt]>>31<<31);
        }else if(funct==8){
            //jr
            mips->pc=mips->registers[rs];
            return;
        }else {
            //如果还有其他的未知指令，那么就,终止
            system("pause");
            throw "error";
        }
        mips->pc+=4;
        if(rd!=0){
            *changedReg=rd;
        }else {
            mips->registers[rd]=0;
        }
    }else if (opcode==2) {
        //j
        unsigned int targetAddr=(instr<<6)>>4;//抹掉高六位,并把后两位为０恢复
        mips->pc=(unsigned int)((mips->pc>>28)<<28)+targetAddr;  //取pc的高４位，为pc的高四位
    }else if (opcode==3) {
        //jal
        unsigned int targetAddr=(instr<<6)>>4;//抹掉高六位,并把后两位为０恢复
        mips->registers[31]=mips->pc+4;           //保存返回地址
        *changedReg=31;
        mips->pc=(unsigned int)((mips->pc>>28)<<28)+targetAddr;//取pc的高４位，为pc的高四位
    }else {
        //I格式
        //第一步得到各个段的值
        unsigned int rs=(instr>>21)&(31); //跟31* 2^(5+5+5+6)
        unsigned int rt=(instr>>16)&(31);    //跟31* 2^(5+5+6)
        int immediate=instr&65535;
        if(opcode==8){
            //addi
            int m=immediate;
            if(immediate>>15==1)
                m=immediate-65536; //符号扩展
            mips->registers[rt]=mips->registers[rs]+m;
        }else if (opcode==9) {
            //addiu
            int m=immediate;
            if(immediate>>15==1)
                m=immediate-65536; //符号扩展
            mips->registers[rt]=mips->registers[rs]+m;
        }else if (opcode==12) {
            //andi
            mips->registers[rt]=mips->registers[rs]&immediate;
        }else if (opcode==13) {
            //ori
            mips->registers[rt]=mips->registers[rs]|immediate;
        }else if (opcode==14) {
            //xori
            mips->registers[rt]=mips->registers[rs]^immediate;
        }else if(opcode==15){
            //lui
            mips->registers[rt]=immediate<<16;
        }else if (opcode==35) {
            //lw
            int m=immediate;
            if(immediate>>15==1)
                m=immediate-65536; //符号扩展
            int add=mips->registers[rs]+m;
            mips->registers[rt]=mips->memory[(add-0x00400000)/4];
            *changedReg=rt;
            mips->pc+=4;
            return;
        }else if(opcode==43){
            //sw
            int m=immediate;
            if(immediate>>15==1)
                m=immediate-65536; //符号扩展
            int add=mips->registers[rs]+m;
            mips->memory[(add-0x00400000)/4]=mips->registers[rt];
            *changedMem=add;
            mips->pc+=4;
            return;
        }else if(opcode==4){
            //beq
            int m=immediate;
            if(immediate>>15==1)
                m=immediate-65536; //符号扩展
            if(mips->registers[rs]==mips->registers[rt]){
                mips->pc+=(m*4);
            }
            mips->pc+=4;
            return;
        }else if(opcode==5){
            //bne
            int m=immediate;
            if(immediate>>15==1)
                m=immediate-65536; //符号扩展
            if(mips->registers[rs]!=mips->registers[rt]){
                mips->pc+=(m*4);
            }
            mips->pc+=4;
            return;
        }else if (opcode==10) {
            //slti
            int m=immediate;
            if(immediate>>15==1)
                m=immediate-65536; //符号扩展
            if(mips->registers[rs]<m){
                mips->registers[rt]=1;
            }else{
                mips->registers[rt]=0;
            }
        }else if (opcode==11) {
            //sltiu
            if(mips->registers[rs]<immediate){
                mips->registers[rt]=1;
            }else {
                mips->registers[rt]=0;
            }
        }
        mips->pc+=4;
        *changedReg=rt;

    }


}
