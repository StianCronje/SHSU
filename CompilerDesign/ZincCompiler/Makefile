all:
	flex zinc.l
	bison -y -d zinc.y
	gcc y.tab.c lex.yy.c -ly -ll -o zinc

run: all
	./zinc input.znc

clean:
	sudo rm y.tab.c y.tab.h lex.yy.c zinc out.asm