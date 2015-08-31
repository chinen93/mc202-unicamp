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
    int size;
} List;

List* createList();
Node* createNode(int info);
void destroyNode(Node *node);
void destroyList(List *list);
void printList(List *list);
void printNode(Node *p);

int  searchInfo(int info, Node **prev, Node **current, List *list);
void insertNodeBeginList(Node *new, List *list);
void insertNodeFinalList(int info, List *list);
int  removeNode(int info, List *list, Node **result);
int  moveToFront(int info, List *list);
int  transpose(int info, List *list);

int  main(){
    Node *result;
    List *listMTF, *listTR;
    int size, numReq;
    char instruction;
    int infoToUse;
    int i, costsMTF = 0, costsTR = 0;
    int MTF, TR;

    listMTF = createList();
    listTR  = createList();

    /*
    infoToUse = 1;
    insertNodeFinalList(infoToUse, listMTF);
    insertNodeFinalList(infoToUse, listTR);
    infoToUse = 2;
    insertNodeFinalList(infoToUse, listMTF);
    insertNodeFinalList(infoToUse, listTR);
    infoToUse = 3;
    insertNodeFinalList(infoToUse, listMTF);
    insertNodeFinalList(infoToUse, listTR);
    infoToUse = 4;
    insertNodeFinalList(infoToUse, listMTF);
    insertNodeFinalList(infoToUse, listTR);
    infoToUse = 5;
    insertNodeFinalList(infoToUse, listMTF);
    insertNodeFinalList(infoToUse, listTR);

    infoToUse = 4;    
    MTF = moveToFront(infoToUse, listMTF);
    TR  = transpose(infoToUse, listTR);
    costsMTF += MTF;
    costsTR  += TR;
    printf("[%d %d]\n", MTF, TR);
    infoToUse = 2;    
    MTF = moveToFront(infoToUse, listMTF);
    TR  = transpose(infoToUse, listTR);
    costsMTF += MTF;
    costsTR  += TR;
    printf("[%d %d]\n", MTF, TR);
    infoToUse = 2;    
    MTF = moveToFront(infoToUse, listMTF);
    TR  = transpose(infoToUse, listTR);
    costsMTF += MTF;
    costsTR  += TR;
    printf("[%d %d]\n", MTF, TR);
    
    infoToUse = 6;
    insertNodeFinalList(infoToUse, listMTF);
    insertNodeFinalList(infoToUse, listTR);
    transpose(infoToUse, listTR);
    MTF = (*listMTF).size;
    TR =  (*listTR).size;
    costsMTF += MTF;
    costsTR  += TR;
    printf("[%d %d]\n", MTF, TR);

    infoToUse = 3;    
    MTF = moveToFront(infoToUse, listMTF);
    TR  = transpose(infoToUse, listTR);
    costsMTF += MTF;
    costsTR  += TR;
    printf("[%d %d]\n", MTF, TR);
    

    infoToUse = 2;
    MTF   = removeNode(infoToUse, listMTF, &result);
    costsMTF += MTF;
    destroyNode(result);
    TR = removeNode(infoToUse, listTR, &result);
    costsTR  += TR;
    destroyNode(result);
    printf("[%d %d]\n", MTF, TR);

    infoToUse = 3;    
    MTF = moveToFront(infoToUse, listMTF);
    TR  = transpose(infoToUse, listTR);
    costsMTF += MTF;
    costsTR  += TR;
    printf("[%d %d]\n", MTF, TR);
    infoToUse = 6;    
    MTF = moveToFront(infoToUse, listMTF);
    TR  = transpose(infoToUse, listTR);
    costsMTF += MTF;
    costsTR  += TR;
    printf("[%d %d]\n", MTF, TR);    

    infoToUse = 1;
    MTF   = removeNode(infoToUse, listMTF, &result);
    costsMTF += MTF;
    destroyNode(result);
    TR = removeNode(infoToUse, listTR, &result);
    costsTR  += TR;
    destroyNode(result);
    printf("[%d %d]\n", MTF, TR);
    */
    
    
    scanf("%d %d", &size, &numReq);
    for(i=0; i<size; i++){
        scanf("%d", &infoToUse);
        insertNodeFinalList(infoToUse, listMTF);
        insertNodeFinalList(infoToUse, listTR);
    }
    
    for(i=0; i<numReq; i++){
        scanf(" %c %d", &instruction, &infoToUse);
        switch(instruction){
        case 'a':
            MTF = moveToFront(infoToUse, listMTF);
            TR  = transpose(infoToUse, listTR);
            costsMTF += MTF;
            costsTR  += TR;
            break;
        case 'i':
            insertNodeFinalList(infoToUse, listMTF);
            insertNodeFinalList(infoToUse, listTR);
            transpose(infoToUse, listTR);
            MTF = (*listMTF).size;
            TR =  (*listTR).size;
            costsMTF += MTF;
            costsTR  += TR;
            break;
        case 'r':
            MTF   = removeNode(infoToUse, listMTF, &result);
            costsMTF += MTF;
            destroyNode(result);
            TR = removeNode(infoToUse, listTR, &result);
            costsTR  += TR;
            destroyNode(result);
            break;
        default:
            break;
        }
    }
    

    printf("%d\n", costsMTF);
    printList(listMTF);
    printf("%d\n", costsTR);
    printList(listTR);
    
    return(0);
}

void printNode(Node *p){
    if(p != NULL)
        printf("%d ", (*p).info);
}

void printList(List *list){
    Node *p = (*list).head;
    while(p != NULL){
        printNode(p);
        p = (*p).next;
    }
    printf("\n");
}

List* createList(){
    List *l;
    l = (List *)malloc(sizeof(List));
    (*l).head = NULL;
    (*l).size = 0;
    return l;
}

/* Cria no com informacoes e prox == NULL */
Node* createNode(int info){
    Node *p;
    p = (Node *)malloc(sizeof(Node));
    (*p).info = info;
    (*p).next = NULL;
    return p;
}

/* Destroi todos os nos da lista */
void destroyList(List *list){
    Node *p = (*list).head;
    Node *next;
    
    while(p != NULL){
        next = (*p).next;
        destroyNode(p);
        p = next;
    }
}

/* Remove no da memoria  */
void destroyNode(Node *node){
    free(node);
}
/* Procurar custa 1 ponto ate chegar no desejado 
   -1 caso o elemento nao esteja na lista
*/
int searchInfo(int info, Node **prev, Node **current, List *list){
    int costs = 1;
    (*prev) = NULL;
    (*current) = (*list).head;

    if((*current) != NULL){
        while(((**current).next != NULL) && ((**current).info != info)){
            (*prev) = (*current);
            (*current) = (**current).next;
            costs++;
        }
    }

    if((**current).info == info)
        return costs;
    
    return -1;
}

/* Insere um no no comeco da lista  */
void insertNodeBeginList(Node *new, List *list){
    /* Empty List */
    if((*list).head == NULL)
        (*list).head = new;
    else{
        (*new).next  = (*list).head;
        (*list).head = new;
    }

    (*list).size++;
}

/* Insere um no no final da lista  */
void insertNodeFinalList(int info, List *list){
    Node *aux = (*list).head;
    Node *new = createNode(info);
    
    /* Lista vazia */
    if(aux == NULL)
        insertNodeBeginList(new, list);
    else{
        while((*aux).next != NULL)
            aux = (*aux).next;

        (*aux).next = new;
        (*list).size++;
    }
}

/* Remove um no da lista  */
int removeNode(int info, List *list, Node **result){
    Node *prev = NULL, *current;
    int costs = searchInfo(info, &prev, &current, list);

    /* Caso volte -1, nao achou o no */
    if(costs != -1){
        (*result) = current;
        /* Elemento a ser removido nao eh o primeiro  */
        if(costs != 1){
            (*prev).next = (**result).next;
        }else{
            /* Eh o inicio da lista  */
            (*list).head = (**result).next;
        }

        (**result).next = NULL;
        (*list).size--;
    }
    
    return costs;
}

/* Move um no para para a frente da lista  */
int moveToFront(int info, List *list){
    Node *result;
    int costs = removeNode(info, list, &result);
    
    if(costs != -1){
        insertNodeBeginList(result, list);
    }
    
    return costs;
}

/* Troca as informacoes de um no com seu anterior  */
int transpose(int info, List *list){
    Node *prev = NULL, *current;
    int aux;
    int costs = searchInfo(info, &prev, &current, list);
    
    /* Caso seja o primeiro elemento nao trocar */
    if(costs != -1){
        if(prev != NULL){
            aux             = (*prev).info;
            (*prev).info    = (*current).info;
            (*current).info = aux;
        }
    }

    return costs;
}
