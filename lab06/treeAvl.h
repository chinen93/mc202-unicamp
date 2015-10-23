#ifndef TREEAVL_H
#define TREEAVL_H

typedef struct Record {
    unsigned int id;
    char data[1000];
} Record;

typedef struct Root {
    unsigned int id;
    int indexReg;
    int balance;
    struct root *left;
    struct root *right;
} root;

void insertNode(Root **root, int *heightGrows, Root *new);
void removeNode(Root **root, int id, int *heightLowers);
void rotationRight(Root **root);
void rotationLeft(Root **root);
void checkNodeRight(Root **root, int *heightGrows);
void checkNodeLeft(Root **root, int *heightGrows);
void destroyRoot(Root **root);
Root *createNode(int id, int indexReg);


#endif
