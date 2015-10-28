/* 
   Nome: Pedro Hideaki Uiechi Chinen
   RA  : 175828
*/

#ifndef TREEAVL_H
#define TREEAVL_H

typedef struct Root {
    unsigned int id;
    int indexReg;
    int balance;
    struct Root *left;
    struct Root *right;
} Root;

void insertNodeTree(Root **root, Root *new);
struct Root* removeNodeTree(Root **root, int id);
struct Root* searchIdTree(Root **root, int id); 
void rotationRight(Root **root);
void rotationLeft(Root **root);
void checkNodeRight(Root **root, int *heightChanged, int isGrowing);
void checkNodeLeft(Root **root, int *heightChanged, int isGrowing);
void destroyRoot(Root **root);
Root *createNode(int id, long int indexReg);
void printTreeAVL(Root *root, int level);


#endif
