objects = myString.c main.c

all: $(objects)
	gcc -o main $(objects) -g -lm

run:
	./main

valgrind:
	valgrind --leak-check=full ./main

myString.o: myString.h
main.o: myString.h

clean:
	rem *.o main

zip: 
	zip program.zip *.c *.h Makefile
