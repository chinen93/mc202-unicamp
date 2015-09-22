/*
  Nome: Pedro Hideaki Uiechi Chinen
  Ra  : 175828
  Laboratorio 04 - Os Caca Pixels
 */
#include <stdlib.h>
#include "bucketList.h"

BucketList *createBucketList(int num){
    BucketList *bucket;
    int i;

    /* Create num buckets of list  */
    bucket = (BucketList *)calloc(1, sizeof(BucketList));
    bucket->bucketList = (List **)calloc(num, sizeof(List *));
    for(i=0; i<num; i++){
        bucket->bucketList[i] = createList();
    }
    
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

Node *createNode(int info){
    Node *node;
    node = (Node *)calloc(1, sizeof(Node));
    node->info = info;
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

    free((*list));
    (*list) = NULL;
}

void destroyBucketList(BucketList **bucketList){
    int i;
    List *list;

    for(i=0; i<(*bucketList)->num; i++){
        list = (*bucketList)->bucketList[i];
        destroyList(&list);
    }
    
    free((*bucketList)->bucketList);
    free((*bucketList));
    
    (*bucketList) = NULL;
}

void insertInfoList(int info, List *list){
    Node *new = createNode(info);

    list->num++;
    if(list->head == NULL){
        list->head = new;
        list->tail = new;
    }else{
        list->tail->next = new;
        list->tail = new;
    }
}
