.data
	myDouble: .double 1.234567890123456
	zeroDouble: .double 0.00
	
.text
	ldc1	$f2, myDouble	# loads double into $f2 and $f3
	ldc1	$f0, zeroDouble	# loads zero into coproc $f0 and $f1
	
	li	$v0, 3		# preps system to print_double
	add.d	$f12, $f2, $f0	# adds myDouble and zeroDouble, saves it in $f12
	syscall			# print_double, reads $f12 and prints it to screen