CC := gcc
#directories
SRC_DIR := src
INC_DIR := includes
OBJ_DIR := obj
BIN_DIR := bin

EXE := $(BIN_DIR)/main

SRC := $(wildcard $(SRC_DIR)/*.c)
OBJ := $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

CPPFLAGS := -Iinclude -MMD -MP
CFLAGS = -g -lm -Wall -Werror
LDFLAGS = -Llib
VALFLAGS = --show-leak-kinds=all --track-origins=yes --leak-check=full -s

all: $(EXE)
.PHONY: all clean zip

$(EXE): $(OBJ) | $(BIN_DIR)
	$(CC) $(LDFLAGS) $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS)	-c $< -o $@

$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@

clean:
	@$(RM) -rv $(BIN_DIR) $(OBJ_DIR)

run:
	$(EXE)

-include $(OBJ:.o=.d)

val:
	valgrind $(VFLAGS) $(EXE)

zip:
	zip Exercicio1.zip Makefile -r $(SRC_DIR) -r $(INC_DIR) -r binarios

refresh:
	rm binarios/* -f
	unzip binarios.zip
	mv binario*.bin binarios/
	