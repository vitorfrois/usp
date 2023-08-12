objects = main.o sorts.o

all: $(objects)
	gcc -o main $(objects) -g -Wall -Werror

run:
	./main

sorts.o: sorts.h
main.o: sorts.h 

clean:
	rm *.o main vgcore.*

valgrind:
	valgrind --leak-check=full ./main
