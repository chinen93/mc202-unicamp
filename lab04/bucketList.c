#include <stdlib.h>

BucketList *createBucketList(int num){
    BucketList *bucket;
    int i;

    /* Create num buckets of list  */
    bucket->bucketList = (BucketList *)calloc(1, sizeof(BucketList));
    for(i=0; i<num; i++)
        bucket->bucketList[i] = createList();
    bucket->num = num;

    return bucket;
}

List *createList(){
    List *list;
    list = (List *)calloc(1, sizeof(List));
    list->num = 0;
    list->head = NULL;
    list->tail = NULL;
    return list;
}

Node *createNode(int *address){
    Node *node;
    node = (Node *)calloc(1, sizeof(Node));
    node->address = address;
    node->next = NULL;
    return node;
}

void destroyNode(Node **node){
    if((*node) != NULL)
        free((*node));
    (*node) = NULL;
}

void destroyList(List **list){
    Node *node;
    while((*list)->head != NULL){
        node = (*list)->head;
        (*list)->head = (*list)->head->next;
        free(node);
    }

    (*list) = NULL;
}

void destroyBucketList(BucketList **bucketList){
    int i;
    List *list;

    for(i=0; i<(*bucketList)->num; i++){
        list = (*bucketList)->bucket[i];
        destroyList(&list);
    }

    free((*bucketList));
}

void insertAddressList(int *address, List *list){
    Node *new = createNode(address);

    list->num++;
    if(list->head == NULL){
        list->head = new;
        list->tail = new;
    }else{
        list->tail->next = new;
        list->tail = new;
    }
}
