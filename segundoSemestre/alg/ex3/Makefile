objects = myString.o main.o

all: $(objects)
	gcc -o main $(objects) -g

run:
	./main

myString.o: myString.h
main.o: myString.h

clean:
	rm *.o main vgcore.*
