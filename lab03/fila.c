/* Nome: Pedro Hideaki Uiechi Chinen
 * RA: 175828
 * Laboratorio 03 - Sistema Único de Saúde */

#include "fila.h"
#include <stdlib.h>
#include <stdio.h>

#define TRUE 1
#define FALSE 0

/******** Basics Functions of a List ************/
List* createList(){
    List *l = (List *)malloc(sizeof(List));
    l->head = NULL;
    l->tail = NULL;
    return l;
}

Node* createNode(int info){
    Node *n = (Node *)malloc(sizeof(Node));
    n->info = info;
    n->next = NULL;
    return n;
}

void  destroyList(List *list){
    Node *n = NULL;
    while(! isListEmpty(list)){
        n = removeBeginList(list);
        destroyNode(n);
    }

    free(list);
}

void  destroyNode(Node *node){
    if(node != NULL)
        free(node);
}

void  printList(List list){
    Node *n = list.head;
    printf("{%d/%d}[" , list.head->info, list.tail->info);
    while(n != NULL){
        printf("[%p/%d/%p]", n, n->info, n->next);
        n = n->next;
    }
    printf("]\n");
}

char  isListEmpty(List *list){
    return(list->head == NULL);
}

/********************************************************/

char findInfo(int info, List *list, Node **current, Node **prev){
    if(! isListEmpty(list)){
        /* Prev NULL refers to the begin of list  */
        (*current) = list->head;
        (*prev)    = NULL;
        while(((*current) != NULL)  && ((*current)->info != info)){
            (*prev) = (*current);
            (*current) = (*current)->next;
        }
        /* Found the info  */
        if((*current)->info == info)
            return(TRUE);
    }
    return(FALSE);
}

Node* removeInfo(int info, List *list){
    Node *current, *prev = NULL;
    Node *node = NULL;
    if(findInfo(info, list, &current, &prev)){
        if(prev != NULL){
            /* Checks if the current is the tail of list */
            if(current == list->tail){
                list->tail = prev;
            }
            /* Skips current node  */
            prev->next = current->next;
        }else{
            /* Skips head of list */
            list->head = list->head->next;
        }

        /* Remove reference to list */
        node = current;
        node->next = NULL;
    }
    return(node);
}

Node* removeBeginList(List *list){
    Node *node = NULL;
    if(! isListEmpty(list)){
        node = list->head;
        list->head = list->head->next;
        node->next = NULL;
    }
    return(node);
}

void  insertBeginList(Node *node, List *list){
    if(! isListEmpty(list)){
        node->next = list->head;
        list->head = node;
    }else{
        list->head = node;
    }
}

void  insertFinalList(Node *node, List *list){
    if(! isListEmpty(list)){
        list->tail->next = node;
        list->tail = node;
    }else{
        list->head = node;
        list->tail = node;
    }
}

void  insertFinalListInfo(int info, List *list){
    Node *n;
    n = createNode(info);
    insertFinalList(n, list);
}
