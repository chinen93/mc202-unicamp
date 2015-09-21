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
    list->head = NULL;
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
    while(bucketList->num > 0){
        bucketList->bucket
        bucketList->num--;
    }
}

void insertAddressList(int *address, List *list);
