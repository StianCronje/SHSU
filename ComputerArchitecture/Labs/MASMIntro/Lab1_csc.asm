.data
	progInstr:	.asciiz "This program will add the 2 largest of 3 numbers\n"
	prompt: 	.asciiz "Enter an integer to add: "
	result:		.asciiz "The sum is: "
	
	
.text
	li		$v0, 4			# prep to print string
	la		$a0, progInstr	# loads progInstr into address to print to screen
	syscall					# prints progInstr to screen
	
	# get input and store in register
	li		$v0, 4			# prep to print string
	la		$a0, prompt		# loads prompt into address to print to screen
	syscall					# prints prompt to screen
	
	li		$v0, 5			# prep to read_int
	syscall					# execute read_int
	move	$t0, $v0		# move user input to $t0 register
	
	# get input and store in register
	li		$v0, 4			# prep to print string
	la		$a0, prompt		# loads prompt into address to print to screen
	syscall					# prints prompt to screen
	
	li		$v0, 5			# prep to read_int
	syscall					# execute read_int
	move	$t1, $v0		# move user input to $t1 register
	
	# get input and store in register
	li		$v0, 4			# prep to print string
	la		$a0, prompt		# loads prompt into address to print to screen
	syscall					# prints prompt to screen
	
	li		$v0, 5			# prep to read_int
	syscall					# execute read_int
	move	$t2, $v0		# move user input to $t2 register
	
	# add 2 largest numers
	li		$t9, 0			# largest will be stored in $t9
	li		$t8, 0			# largest will be stored in $t8
	
	slt		$s0, $t0, $t1	# if $t1 > $t0, $s0 = 1
	bgtz	$s0, t1Big		# if $t1 > $t0 goto t1Big
	move	$t9, $t0		# t0 is largest, store in $t9
	move	$t8, $t1		# store 2nd largest, t1, in $t8
	j		exit1
	
	t1Big:
	move	$t9, $t1		# t1 is largest
	move	$t8, $t0		# t0 is 2nd largest
	exit1:
	
	slt		$s0, $t8, $t2	# if $t2 > $t8, $s0 = 1
	blez	$s0, exit2		# if $t2 < $t8, go to exit2
	move	$t8, $t2		# if t2 is larger, replace $t8
	exit2:					# else do nothing
	
	add		$t3, $t9, $t8	# add 2 largest (stored in t8 and t9) save to $a0 to print
	
	#print out sum of 2 largest
	li		$v0, 4			# prep to print string
	la		$a0, result		# loads result text into address to print to screen
	syscall					# prints result text to screen
	
	li		$v0, 1			# prep to print int that was read
	move	$a0, $t3
	syscall
	
	li		$v0, 10			# exit program
	syscall
