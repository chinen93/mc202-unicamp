/* Nome: Pedro Hideaki Uiechi Chinen
 * RA: 175828
 * Laboratorio 03 - Sistema Único de Saúde */

#include "fila.h"
#include <stdlib.h>

List* createList(){
    List *l = (List *)malloc(sizeof(List));
    l->head = NULL;
    l->tail = NULL;
    return l;
}

Node* createNode(){
    Node *n = (Node *)malloc(sizeof(Node));
    n->info = -1;
    n->next = NULL;
    return n;
}

void  destroyList(List *list){
    while(! isListEmpty(list))
}

void  destroyNode(Node *node){
    if(node != NULL)
        free(node);
}

char  isListEmpty(List *list);
Node* findInfo(int info, List list);
Node* removeInfo(int info, List *list);
Node* removeBeginList(List* list);

void  insertBeginList(Node *node, List *list);
void  insertFinalList(Node *node, list *list);
