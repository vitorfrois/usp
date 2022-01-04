objects = linkedList.h myString.h

all:
	gcc -o main *c -g

run: 
	./main

linkedList.o: linkedList.h
myString.o: myString.h

zip: 
	zip ex3.zip *.c *.h Makefile	

valgrind:
	valgrind --leak-check=full ./main