all:
	flex zinc.l
	bison -y -d zinc.y
	gcc y.tab.c lex.yy.c -ly -ll -o zinc

run: all
	./zinc input.znc > out.asm

test: all
	./zinc < test.znc > out.asm

if: all
	./zinc < if.znc > out.asm

clean:
	sudo rm y.tab.c lex.yy.c zinc