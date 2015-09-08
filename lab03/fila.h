/* Nome: Pedro Hideaki Uiechi Chinen
 * RA: 175828
 * Laboratorio 03 - Sistema Único de Saúde */

#ifndef FILA_H
#define FILA_H

typedef struct Node{
    int info;
    struct Node *next;
} Node;

/* First 
   In
   First
   Out
 */
typedef struct List{
    struct Node *head;
    struct Node *tail;
} List;

List* createList();
Node* createNode(int info);
void  destroyList(List *list);
void  destroyNode(Node *node);

void  printList(List list);

char  isListEmpty(List *list);
char findInfo(int info, List *list, Node **current, Node **prev);
Node* removeInfo(int info, List *list);
Node* removeBeginList(List *list);

void  insertBeginList(Node *node, List *list);
void  insertFinalList(Node *node, List *list);
void  insertFinalListInfo(int info, List *list);
#endif /* FILA_H */
