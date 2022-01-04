# Arquivo Makefile para compilação e execução do programa
vpath %.c . sources
vpath %.o . sources
vpath %.h includes

CC=gcc
LD=gcc

INCLUDES_PATH=./includes/
CFLAGS=-Wall -Wextra -Werror -pedantic -g -O0 -std=c99 -I $(INCLUDES_PATH)
LFLAGS=-lm -g

VFLAGS=--leak-check=full --show-leak-kinds=all --track-origins=yes

OBJS=main.o skiplist.o
TARGET=programaTrab

.c.o:
	@$(CC) $(CFLAGS) -c $< -o $@

all: clean $(OBJS)
	@$(LD) $(LFLAGS) $(OBJS) -o $(TARGET)

clean:
	@rm -rf $(OBJS) $(TARGET)

run:
	@./$(TARGET)

val: clean all
	@valgrind $(VFLAGS) ./$(TARGET)

zip:
	@zip -r trab.zip Makefile main.c includes/ sources/ README.*