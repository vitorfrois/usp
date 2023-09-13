libs:
	pacman -S glew mesa glfw-x11

compile:
	gcc main.c -lglfw -lGL -lGLEW -lm -o main

run:
	./main

all: compile run