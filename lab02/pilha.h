#ifndef PILHA_H
#define PILHA_H

/* Type Node:
   :int information of node
   :Node* address to next node
 */
typedef struct Node{
    struct Node *prev;
    int info;
    struct Node *next;
} Node;

/* Type Stack:
   :Node* address of the head of Stack
   :Node* address of the tail of Stack
*/
typedef struct Stack{
    struct Node *head;
    struct Node *tail;
} Stack;

/* Functions to create types Node and Stack */
Stack* createStack();
Node*  createNode(int info);
void   destroyStack(Stack *stack);
void   destroyNode(Node *node);
char   isStackEmpty(Stack *stack);
void   printStack(Stack *stack);

/* Functions to use Stack with type Node parameters */
void   pushNode(Node *new, Stack *stack);
Node*  popNode(Stack *stack);

/* Functions to use Stack with type Int parameters */
void   pushInfo(int new, Stack *stack);
int    popInfo(Stack *stack);

#endif
