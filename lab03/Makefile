# Makefile #
all: fila.o main.o
	gcc -o programa fila.o main.o

fila.o: fila.c
	gcc -o fila.o -c fila.c

main.o: main.c
	gcc -o main.o -c main.c

run:
	./programa
