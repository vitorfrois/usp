objects = linkedList.o main.o

all: $(objects)
	gcc -o main $(objects) -g

run:
	./main

valgrind:
	valgrind ./main

linkedList.o: linkedList.h
main.o: linkedList.h

clean:
	rm *.o main vgcore.*
