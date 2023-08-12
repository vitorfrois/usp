objects = data.o readString.o main.o

all: $(objects)
	gcc -o main $(objects) -g

run:
	./main

data.o: data.h
readString.o: readString.h
main.o: data.h readString.h

valgrind:
	valgrind --track-origins=yes ./main

clean:
	rm *.o main vgcore.*

