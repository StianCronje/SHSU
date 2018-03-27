FILENAME=ArraysSorting

all:
	gcc -c -Wall PtrSortRecordsB.c
	ar -cru libPtrSort.a PtrSortRecordsB.o
	gcc -o ./$(FILENAME) ArraysSorting.cpp -L -lPtrSort

clean:
	rm -rf *.o *.a $(FILENAME)

run: all
	./$(FILENAME)

runIO: all
	./$(FILENAME) input.txt output.txt