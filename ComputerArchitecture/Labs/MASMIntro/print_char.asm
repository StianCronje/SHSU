.data
	myChar:	.byte 'a'

.text
	li $v0, 4	# prepares syscall to print_int
	la $a0, myChar	# loads address into register from given data
	syscall		# executes print_str(code 4)