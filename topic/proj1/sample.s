#note:	 These instructions are provided
#	only to give you sample output.
#	This should not be considered
#	as a rigorous test file (you'll
#	have to do that yourself.			
	
main:
	addu $0, $2, $2
	addiu $3, $4, 5
tx:	addiu $6, $7, -8
	subu $8, $9, $10
	sll $11, $12, 14
	srl $15, $16, 17
	and $18, $19, $20
	andi $21, $22, 23
	andi $24, $25, 0xffe6
	or $27, $28, $29
	ori $30 $31 1
	ori $2 $3 0xfffc
	lui $5 6
	slt $7 $8 $9
	beq $10 $11 t1
	add $12 $13 $14
t1:	beq $10 $11 tz
tz:	bne $15 $16 t2
	bne $0 $0 tx 
t2:	addiu $sp $sp -24
	sw $20, 20($sp)
	sw $21, -20($sp)
	lw $22, 20($sp)
	lw $23, -20($sp)
	
		
	j temp1
temp0:	addiu $s1 $0 -1
	sw $s1 0($sp)
	jr $sp
	#should kill at sp non-instruction
		
temp1:	jal temp2
	ori $2 $3 4
temp2:	jal temp0
	
