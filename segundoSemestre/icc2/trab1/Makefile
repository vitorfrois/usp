objects = game.o matrix.o readString.o main.o

all: $(objects)
	gcc -o main $(objects) -g

run:
	./main

game.o: game.h
matrix.o: matrix.h
readString.o: readString.h
main.o: game.h matrix.h readString.h

clean:
	rm *.o main
