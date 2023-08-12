objects = linkedList.c myString.c main.c

all: $(objects)
	gcc -o main $(objects) -g -lm

run:
	./main

valgrind:
	valgrind --leak-check=full ./main

linkedList.o: linkedList.h
myString.o: myString.h
main.o: linkedList.h myString.h

clean:
	rem *.o main

zip: 
	zip program.zip *.c *.h Makefile
