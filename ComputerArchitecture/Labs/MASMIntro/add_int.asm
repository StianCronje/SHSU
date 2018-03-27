.data
	number1: .word 5
	number2: .word 10
	
.text
	lw	$t0, number1	# loads number1 into register
	lw	$t1, number2	# loads number2 into register
	
	add	$t2, $t0, $t1	# adds $t0 and $t1 and stores result in $t2
	
	li	$v0, 1		# preps syscall to print_int 
	move	$a0, $t2	# moves value in $t2 to $a0
	syscall			# print value in $a0 to screen