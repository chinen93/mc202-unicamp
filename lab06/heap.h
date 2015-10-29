/* 
   Nome: Pedro Hideaki Uiechi Chinen
   RA  : 175828
*/

#ifndef HEAP_H
#define HEAP_H

typedef struct Heap{
    long int *vector;
    int size;
    int last;
} Heap;


Heap *createHeap(int size);
void insertLongIntHeap(Heap **heap, long int value);
long int  removeLongIntHeap(Heap **heap);
void destroyHeap(Heap **heap);
void printHeap(Heap *heap);

#endif
