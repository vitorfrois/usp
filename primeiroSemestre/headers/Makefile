

all:
	gcc -Wall -Wextra -Werror -g -lm -c main.c -o main.o
	gcc -Wall -Wextra -Werror -g -lm -c str.c -o str.o

	gcc -g main.o str.o -o exec

clean:
	@rm -rf *.o exec

run:
	@./exec

zip:
	@zip -r trab.zip Makefile main.c *.c *.h
