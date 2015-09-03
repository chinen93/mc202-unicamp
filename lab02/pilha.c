
#include <stdlib.h>
#include <stdio.h>

#include "pilha.h"

/*  Creates an empty Stack */
Stack* createStack(){
    Stack* q = (Stack*)malloc(sizeof(Stack));
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

/* Runs through the list destroing all the nodes, before free the stack itself */
void   destroyStack(Stack *stack){
    Node* aux;
    
    while(! isStackEmpty(stack)){
        aux = stack->head;
        stack->head = aux->next;
        free(aux);
    }

    free(stack);
}

/* free the memory of Node */
void   destroyNode(Node *node){
    if(node != NULL)
        free(node);
}

char   isStackEmpty(Stack *stack){
    return (stack->head == NULL);
}

void   printStack(Stack *stack){
    Node *aux;
    printf("{");
    if(!isStackEmpty(stack)){
        aux = stack->head;
        do{
            printf("[%d] ",aux->info);
            aux = aux->next;
        }while(aux != NULL);
    }
    printf("}\n");
}

void   pushNode(Node *new, Stack *stack){
    /* Stack empty, new is the first node */
    if(isStackEmpty(stack))
        stack->head = new;
    /* Go to tail of the Stack, the next will be the new node */
    else{
        stack->tail->next = new;
        new->prev = stack->tail;
    }

    /* Anyway, the Stack tail is the new node  */
    stack->tail = new;
}

Node*  popNode(Stack *stack){
    Node *ret = NULL;
    if(!isStackEmpty(stack)){
        if(stack->head == stack->tail)
            stack->head = NULL;
        ret = stack->tail;
        stack->tail = stack->tail->prev;
        ret->prev = NULL;
    }else{
        printf("Stack is empty\n");
    }
    return ret;
}

void   pushInfo(int new, Stack *stack){
    Node* node = createNode(new);
    pushNode(node, stack);
}

int    popInfo(Stack *stack){
    Node *node;
    int ret = 0;
    node = popNode(stack);
    if(node != NULL){
        ret = node->info;
        destroyNode(node);
    }

    return ret;
}
