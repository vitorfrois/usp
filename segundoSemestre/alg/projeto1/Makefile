objects = skipList.c myString.c main.c

all: $(objects)
	@gcc -o main $(objects) -g -lm

run:
	@./main

zip:
	@zip program.zip *.c *.h Makefile

val: all
	@valgrind --show-leak-kinds=all --track-origins=yes --leak-check=full --log-file="val.log" ./main

valgrind:
	@valgrind ./main

skipList.o: skipList.h
myString.o: myString.h
main.o: skipList.h myString.h

clean:
	@rm *.o main vgcore.*

go: all run