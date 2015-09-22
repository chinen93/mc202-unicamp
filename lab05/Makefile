# Makefile #
all: root.o main.o 
	gcc -o programa root.o main.o -g

root.o: root.c
	gcc -o root.o -c root.c -g 

main.o: main.c
	gcc -o main.o -c main.c -g

run:
	./programa

