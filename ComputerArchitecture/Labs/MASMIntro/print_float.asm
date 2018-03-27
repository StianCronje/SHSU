.data
	pi: .float 3.14159

.text
	li $v0, 2	# prepares syscall to print_float
	lwc1 $f12, pi	# loads float into float coprocessor
	syscall		# executes print_float(code 2)