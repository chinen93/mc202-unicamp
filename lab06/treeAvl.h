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
    struct Root *left;
    struct Root *right;
} Root;

void insertNode(Root **root, int *heightChanged, Root *new);
void removeNode(Root **root, int id, int *heightChanged);
void rotationRight(Root **root);
void rotationLeft(Root **root);
void checkNodeRight(Root **root, int *heightChanged, int isGrowing);
void checkNodeLeft(Root **root, int *heightChanged, int isGrowing);
void destroyRoot(Root **root);
Root *createNode(int id, int indexReg);
void printTreeAVL(Root *root, int level);


#endif
