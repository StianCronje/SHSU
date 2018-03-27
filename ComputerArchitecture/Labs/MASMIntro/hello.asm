.data
	message: .asciiz "Hello World!\n"	# define message to print

.text
	li $v0, 4		# prep system for print_str
	la $a0, message		# load message into register
	syscall			# execute call 4 (print_str)