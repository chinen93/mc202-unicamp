# Makefile #
all: treeAvl.o heap.o main.o 
	gcc -o programa treeAvl.o heap.o main.o -g

heap.o: heap.c
	gcc -o heap.o -c heap.c -g

treeAvl.o: treeAvl.c
	gcc -o treeAvl.o -c treeAvl.c -g 

main.o: main.c
	gcc -o main.o -c main.c -g

run:
	./programa

