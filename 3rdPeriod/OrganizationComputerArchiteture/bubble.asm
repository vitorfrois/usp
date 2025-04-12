.data
	.align 2
	vec: .word 7, 5, 2, 1, 1, 3, 4
	string1: .asciiz "vetor ordenado"
	new_line: .asciiz "\n"

.text
	.globl main
	
main:
	addi $s1, $zero, 7 #MAX
	la $s0, vec
	addi $t0, $t0, 0 #i
	addi $t1, $t1, 0 #j
	
for0:
	bgt $t0, $s1, final #final if t0 > 7
for1:
	bgt $t1, $s1, end_for1 #endfor if t1 < t0
	lw $t3, 0($s0)
	lw $t4, 4($s0)
	blt $t3, $t4, swap
			
swapback:
	addi $s0, $s0, 4
	addi $t1, $t1, 1	
	
	j for1

end_for1:
	addi $s0, $s0, -28
	addi $t0, $t0, 1
	j for0
	
swap:
	sw $t3, 4($s0)
	sw $t4, 0($s0)
	j swapback
	
final:
	li $s0, 0
	la $s0, vec
	addi $t0, $t0, 0 #i
	
print_array:
	lw $a0, 0($s0)
	li $v0, 1
	syscall
	addi $s0, $s0, 4
	addi $t0, $t0, 1
	blt $t0, $s1, print_array

end: 
	li $v0, 10
	syscall
