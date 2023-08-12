objects = main.c ubersort.c

all: $(objects)
	gcc -o main $(objects) -g -Wall -Werror

run:
	./main

main.o: ubersort.h
quicksort.o: ubersort.h

clean:
	rm main *.o 

zip:
	zip ubersort.zip *.c *.h Makefile 

valgrind:
	valgrind ./main
