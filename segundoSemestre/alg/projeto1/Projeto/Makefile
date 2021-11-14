# Nome: Victor Henrique de Sa Silva
# Número USP: 11795759
TARGET = exe
CFILES = source/skiplist.c main.c
CFLAGS = -c -Wall -Werror -Wextra -O0 -g
OFILES = skiplist.o main.o
OFLAGS = -o 
VFLAGS = --show-leak-kinds=all --leak-check=full --track-origins=yes 
CC = gcc

all: $(OFILES)
	@$(CC) $(OFLAGS) $(TARGET) $(OFILES)
	@rm $(OFILES)

$(OFILES): $(CFILES)
	@$(CC) $(CFLAGS)  $(CFILES)

run:
	@./$(TARGET)

val: 
	@valgrind ./$(TARGET) $(VFLAGS)

clean:
	@rm $(TARGET)

zip: 
	@zip -r 11795759 includes main.c Makefile
