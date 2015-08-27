/* Nome: Pedro Hideaki Uiechi Chinen
   RA  : 175828
   Laboratorio 01
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int info;
    struct Node *next;
} Node;

typedef struct List{
    struct Node *head;
} List;


Node* createNode(int info);
void destroyNode(Node *node);
int searchNode(Node *node, List list, Node *prev, Node *current);
void insertNodeBeginList(Node *new, List *list);
void insertNodeFinalList(Node *new, List *list);
void removeNode(Node *node, List *list);
void moveToFront(Node *node, List *list);
void transpose(Node *node)

void main(){
    return(0);
}
    
Node* createNode(int info);
void destroyNode(Node *node);
/* Search costs 1 point for each node until the one searched */
int searchNode(Node *node, List list, Node *prev, Node *current);
void insertNodeBeginList(Node *new, List *list);
void insertNodeFinalList(Node *new, List *list);
/* Remove node costs 1 point  */
void removeNode(Node *node, List *list);
void moveToFront(Node *node, List *list);
void transpose(Node *node)
