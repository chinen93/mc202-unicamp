
#include <pilha.h>;
#include <stdlib.h>;

/*  Creates an empty Queue */
Queue* createQueue(){
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->head = NULL;
    q->tail = NULL;
    return q;
}

/* Creates a Node with the attribute next equals to NULL */
Node*  createNode(int info){
    Node* n = (Node*)malloc(sizeof(Node));
    n->prev = NULL;
    n->info = info;
    n->next = NULL;
    return n;
}

/* Runs through the list destroing all the nodes, before free the queue itself */
void   destroyQueue(Queue *queue){
    Node* aux;
    
    if(isQueueEmpty(queue))
        free(queue);
    
    while(queue->head != NULL){
        aux = queue->head;
        queue->head = aux->next;
        free(aux);
    }
}

/* free the memory of Node */
void   destroyNode(Node *node){
    free(node);
}

char   isQueueEmpty(Queue *queue){
    return (queue->head == NULL);
}

void   pushNode(Node *new, Queue *queue){
    /* Queue empty, new is the first node */
    if(isQueueEmpty(queue))
        queue->head = new;
    /* Go to tail of the Queue, the next will be the new node */
    else{
        queue->tail->next = new;
        new->prev = queue->tail;
    }

    /* Anyway, the Queue tail is the new node  */
    queue->tail = new;
}

Node*  popNode(Queue *queue){
    Node *ret = NULL;
    if(!isQueueEmpty(queue)){
        ret = queue->tail;
        queue->tail = queue->tail->prev;
        ret->prev = NULL;
    }
    return ret;
}

Node*  peakNode(Queue *queue){
    Node *ret = NULL;
    if(!isQueueEmpty(queue)){
        ret = queue->tail;
    }
    return ret;
}

void   pushInfo(int new, Queue *queue);
int    popInfo(Queue *queue);
int    peakInfo(Queue *queue);
