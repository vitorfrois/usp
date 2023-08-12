	.data
	.align 0

string.src: .asciiz "hey ayayayayay"
strin.dst: .space 100
		
	.text
	.globl main
	
main:
	#endereço do 1o byte de string.src
	la $t0, string.src
	lb $t1, 0($t0) #le o 1o byte
	li $t2, 0
	
loop_tam: beqz $t1, sailoop_tam
	addi $t2, $t2, 1 #incrementa variavel tamanho
	addi $t0, $t0, 1 #avança na string
	lb $t1, 0($t0) #le prox byte 
	#lb le $t0 a partir de 0 da string t1
	j loop_tam

sailoop_tam: 
	addi $t2, $t2, 1 #vai incluir o \0
	la $t0, string.src
	la $t6, string.dst
	
loop_copy: beqz $t2, sailoop_copy
	lb $t1, 0($t0) #le o byte
	sb $t1, 0($t6)
	addi $t0, $t0, 1 #avança na string origem 
	addi $t6, $t6, 1 #avança na string dst
	addi $t2, $t2, -1 #decrementa o tamanho
	j loop_copy
	
sailoop_copy:
	li $v0, 4
	la $a0, strins.dst
	syscall
	li $v0, 10
	syscall
	
	
	
	
	
	
	
	
	
	
	
	
	