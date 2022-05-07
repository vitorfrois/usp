.data
	string1: .asciiz "Digite um inteiro"
	string2: .asciiz "O fatorial de "
	string3: .asciiz " é "

.text
	.globl main
	
main:
	#mensagens iniciais 
	li $v0, 4 #Integer reading service for syscall
	la $a0, string1
	syscall
	
	li $v0, 5
	syscall
	
	addi $t3, $zero, 1
	#result
	move $t2, $v0
	#n
	
	#o fatorial de n é 
	li $v0, 4
	la $a0, string2
	syscall
	li $v0, 1
	la $a0, ($t2)
	syscall
	li $v0, 4 
	la $a0, string3
	syscall
	
	addi $t1, $zero, 1
	j loopfat
	
loopfat:
	mul $t3, $t3, $t1
	addi $t1, $t1, 1
	ble $t1, $t2, loopfat
	
	li $v0, 1
	la $a0, ($t3)
	syscall
	
	li $v0, 10
	syscall
	
	
	
