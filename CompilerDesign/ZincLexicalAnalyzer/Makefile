all:
	flex lexan.l
	gcc lex.yy.c -ll -o lexan

run: all
	./lexan input.txt
