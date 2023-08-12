objects = linkedList.o main.o myString.o

all: $(objects)
	gcc -o main $(objects) -g

run:
	./main

valgrind:
	valgrind ./main

zip:
	zip ex9.zip *.c *.h Makefile

linkedList.o: linkedList.h
main.o: linkedList.h
myString.o: myString.h

clean:
	rm *.o main
