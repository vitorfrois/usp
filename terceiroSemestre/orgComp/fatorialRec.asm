.data 
	.align 2
	.text
	.globl main

main:

	li $v0, 5
	syscall
	
	add $a0, $zero, $v0
	jal fact
	
	add $a0, $zero, $v0
	li $v0, 1
	syscall
	
	li $v0, 10
	syscall	

L1:
	addi $a0, $a0, -1 #argument gets (n-1)
	jal fact #call fact with (n-1)
	lw $a0, 0($sp) #return from jal: restore argument n
	lw $ra, 4($sp) #restore the return adress
	addi $sp, $sp, 8 #adjust stack pointer to pop 2 items
	mul $v0, $a0, $v0 #return n * fact (n - 1)
	jr $ra #return to the caller

fact:
	addi $sp, $sp, -8 #adjust stack for 2 itens
	sw $ra, 4($sp) #save the return adress
	sw $a0, 0($sp) #save the argument n
	
	blt $t0, $a0, L1 #if n>=1, go to L1

	addi $v0, $zero, 1 #return 1
	addi $sp, $sp, 8 #pop 2 items off stack
	jr $ra #return to after jal
