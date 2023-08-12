objects = abb.h

all $(objects):
	gcc -o main *.c -g

run:
	./main

abb.o: abb.h
main.o: abb.h

zip:
	zip ex10.zip *.c *.h Makefile

valgrind:
	valgrind --leak-check=full ./main 