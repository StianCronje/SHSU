default: controlbreak

controlbreak.o: controlbreak.c
	gcc -c controlbreak.c -o controlbreak.o

controlbreak: controlbreak.o
	gcc controlbreak.o -o ControlBreak

run: default
	./ControlBreak