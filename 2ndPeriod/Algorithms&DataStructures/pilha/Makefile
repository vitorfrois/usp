objects = pilha.o main.o

main : $(objects)
	gcc -o main $(objects)

pilha.o : pilha.h
main.o : pilha.h

clean : 
	rm *.o main
