objects = linkedList.c main.c

all: $(objects)
	gcc -o main $(objects) -g

run:
	./main

valgrind:
	valgrind --leak-check=full ./main

linkedList.o: linkedList.h
main.o: linkedList.h

clean:
	rem *.o main

zip: 
	zip program.zip *.c *.h Makefile
