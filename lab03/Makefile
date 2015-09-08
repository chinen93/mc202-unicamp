# Makefile #
all: fila.o main.o
	gcc -o programa fila.o main.o -g

fila.o: fila.c
	gcc -o fila.o -c fila.c -g

main.o: main.c
	gcc -o main.o -c main.c -g

run:
	./programa
