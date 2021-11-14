objects = skipList.c myString.c main.c

all: $(objects)
	gcc -o main $(objects) -g -lm

run:
	./main

valLeak:
	valgrind --leak-check=full ./main

valgrind:
	valgrind ./main

skipList.o: skipList.h
myString.o: myString.h
main.o: skipList.h myString.h

clean:
	rm *.o main vgcore.*
