all: matrioshka.o pilha.o programa
	gcc matrioshka.c -c

matrioshka.o: matrioshka.c
	gcc matrioshka.c -c

pilha.o: pilha.c
	gcc pilha.c -c

programa: main.o
	gcc -o programa main.o matrioshka.o pilha.o

main.o: main.c
	gcc main.c -c

run:
	./programa
