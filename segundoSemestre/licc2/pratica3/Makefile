objects = main.o huffman.o myString.o sorts.o

all: $(objects)
	gcc -o main $(objects) -g -Wall -Werror

run:
	./main

myString.o: myString.h
sorts.o: sorts.h huffman.h
huffman.o: sorts.h
main.o: huffman.h myString.h sorts.o

clean:
	rm *.o main vgcore.*

valgrind:
	valgrind --leak-check=full ./main

zip: 
	zip program.zip Makefile *.c *.h 
