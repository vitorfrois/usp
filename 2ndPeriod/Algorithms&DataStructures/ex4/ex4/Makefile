objects = main.o queue.o myString.o data.o

all: $(objects)
	gcc -o main $(objects) -g

run:
	./main

data.o: data.h queue.h
queue.o: queue.h myString.h data.o
myString.o: myString.h
main.o: queue.h myString.h data.o

clean:
	rm *.o main vgcore.*
