.data
	string: .asciiz "Hello World!"
	
.text
	.globl main
	
main:

	li $v0, 5
	syscall
	
	add $t1, $zero, $v0	
	mul $a0, $t1, 2
	li $v0, 1
	syscall
	
	li $v0, 10
	syscall