objects = abb.h myString.h

all:
	gcc -o main *c -g

run: 
	./main

abb.o: abb.h
myString.o: myString.h

zip: 
	zip ex11.zip *.c *.h Makefile	

valgrind:
	valgrind --leak-check=full ./main