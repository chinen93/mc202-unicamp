#ifndef HEAP_H
#define HEAP_H

typedef struct Heap{
    int *vector;
    int size;
    int last;
} Heap;


Heap *createHeap(int size);
void insertIntHeap(Heap **heap, int value);
int  removeIntHeap(Heap **heap);
void moveUp(Heap **heap, int index);
void moveDown(Heap **heap, int index);
void destroyHeap(Heap **heap);
void printHeap(Heap *heap);

#endif
