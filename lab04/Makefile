# Makefile #
all: image.o bucketList.o main.o 
	gcc -o programa bucketList.o image.o main.o -g

image.o: image.c
	gcc -o image.o -c image.c -g 

bucketList.o: bucketList.c
	gcc -o bucketList.o -c bucketList.c -g 

main.o: main.c
	gcc -o main.o -c main.c -g

run:
	./programa

