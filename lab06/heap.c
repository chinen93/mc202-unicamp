/* 
   Nome: Pedro Hideaki Uiechi Chinen
   RA  : 175828
*/

#include <stdlib.h>
#include <stdio.h>
#include "heap.h"

void swap(long int *vector, int indexTo, int indexFrom);

/*
int main(){
    int option, value;
    Heap *heap;

    heap = createHeap(10);
    insertIntHeap(&heap, 100);
    insertIntHeap(&heap, 30);
    insertIntHeap(&heap, 50);
    insertIntHeap(&heap, 7);
    insertIntHeap(&heap, 1);
    printHeap(heap);
    do{
	printf("1 - inserir\n");
	printf("2 - remove\n");
	printf("3 - mostrar heap\n");
	printf("0 - sair\n"); 
	scanf("%d", &option);
	printf("---\n");
	switch(option){
	case 1:
	    printf("Id a ser inserido: ");
	    scanf("%d", &value);
	    insertIntHeap(&heap, value);
	    break;
	case 2:
	    value = removeIntHeap(&heap);
	    printf("{%d}\n", value);
	    printHeap(heap);
	    break;
	case 3:
	    printHeap(heap);
	    break;
	}
	printf("-------------\n");
    }while(option != 0);

    
    destroyHeap(&heap);
    return 0;
}
*/

Heap *createHeap(int size){
    int i;
    Heap *heap = (Heap *)calloc(1, sizeof(Heap));
    heap->vector = (long int *)calloc(size, sizeof(long int));
    for(i=0; i<size; i++)
	heap->vector[i] = -1;
    heap->size = size;
    heap->last = 0;
}

void insertLongIntHeap(Heap **heap, long int value){
    if ((*heap)->last < (*heap)->size){
	(*heap)->vector[(*heap)->last] = value;
	moveUp(heap, (*heap)->last);
	(*heap)->last++;
	
    }
}

long int removeLongIntHeap(Heap **heap){
    long int ret;
    ret = (*heap)->vector[0];
    if((*heap)->last > 0){
	(*heap)->vector[0] = (*heap)->vector[(*heap)->last-1];
	(*heap)->vector[(*heap)->last-1] = -1;
	moveDown(heap, 0);
	(*heap)->last--;
    }else if((*heap)->last == 0){
	(*heap)->vector[0] = -1;
    }
    return ret;
}

void moveUp(Heap **heap, int index){
    int indexParent = (index-1)/2;
    
    /* Heap em que o menor vem primeiro */
    if((*heap)->vector[index] < (*heap)->vector[indexParent]){
	swap((*heap)->vector, index, indexParent);
	moveUp(heap, indexParent);
    }
}

void moveDown(Heap **heap, int index){
    int right, left;
    if(index < ((*heap)->last-1)/2){
	left  = 2*index+1;
	right = 2*index+2;
	/* Heap em que o menor vem primeiro */
	if((*heap)->vector[index] > (*heap)->vector[left] &&
	   (*heap)->vector[left]  < (*heap)->vector[right]){
	    /* filho "left" eh menor que o filho "right"
	       filho "left" eh menor que o pai; troca */
	    if((*heap)->vector[left] != -1){
		swap((*heap)->vector, left, index);
		moveDown(heap, left);
	    }
	}else 	if((*heap)->vector[index] > (*heap)->vector[right] &&
		   (*heap)->vector[left]  > (*heap)->vector[right]){
	    /* filho "right" eh menor que o filho "left"
	       filho "right" eh menor que o pai; troca */
	    if((*heap)->vector[right] != -1){
		swap((*heap)->vector, right, index);
		moveDown(heap, right);
	    }
	}
    }
}

void swap(long int *vector, int indexTo, int indexFrom){
    int intTrade;
    intTrade = vector[indexFrom];
    vector[indexFrom] = vector[indexTo];
    vector[indexTo] = intTrade;
}

void destroyHeap(Heap **heap){
    free((*heap)->vector);
    free((*heap));
    (*heap) = NULL;
}

void printHeap(Heap *heap){
    int i;
    printf("(%d/%d)", heap->size, heap->last);
    for(i=0; i<heap->size; i++){
	if(heap->vector[i] != -1)
	    printf("[%d]", heap->vector[i]);
	else
	    printf("[-]");
    }
    printf("\n");
}


