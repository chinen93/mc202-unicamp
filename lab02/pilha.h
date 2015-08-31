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

/* Type Queue:
   :Node* address of the head of Queue
   :Node* address of the tail of Queue
*/
typedef struct Queue{
    struct Node *head;
    struct Node *tail;
} Queue;

/* Functions to create types Node and Queue */
Queue* createQueue();
Node*  createNode(int info);
void   destroyQueue(Queue *queue);
void   destroyNode(Node *node);
char   isQueueEmpty(Queue *queue);


/* Functions to use Queue with type Node parameters */
void   pushNode(Node *new, Queue *queue);
Node*  popNode(Queue *queue);
Node*  peakNode(Queue *queue);

/* Functions to use Queue with type Int parameters */
void   pushInfo(int new, Queue *queue);
int    popInfo(Queue *queue);
int    peakInfo(Queue *queue);

#endif
