objects = linkedList.o myString.o main.o

all: $(objects)
	gcc -o main $(objects) -g

run:
	./main

valgrind:
	valgrind --leak-check=full ./main

linkedList.o: linkedList.h
myString.o: myString.h
main.o: linkedList.h myString.h

clean:
	rm *.o main vgcore.*
