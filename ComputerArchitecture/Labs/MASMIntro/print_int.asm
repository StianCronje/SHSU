.data
	age: .word 21

.text
	li $v0, 1	# prepares syscall to print_int
	lw $a0, age	# loads word into register from given data
	syscall		# executes print_int(code 1)