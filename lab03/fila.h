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
Node* createNode();
void  destroyList(List *list);
void  destroyNode(Node *node);

char  isListEmpty(List *list);
Node* findInfo(int info, List list);
Node* removeInfo(int info, List *list);
Node* removeBeginList(List* list);

void  insertBeginList(Node *node, List *list);
void  insertFinalList(Node *node, list *list);

#endif /* FILA_H */
