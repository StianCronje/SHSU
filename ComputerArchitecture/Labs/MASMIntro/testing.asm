.data
	num2:	.word 6
	num1:	.word 9
	
.text
	li	$t0, 5
	sw	$t0, num1
	
	li	$v0, 1
	lw	$a0, num1
	syscall
	
	li	$v0, 10
	syscall