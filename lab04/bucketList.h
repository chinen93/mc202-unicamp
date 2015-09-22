/*
  Nome: Pedro Hideaki Uiechi Chinen
  Ra  : 175828
  Laboratorio 04 - Os Caca Pixels
 */
#ifndef BUCKETLIST_H
#define BUCKETLIST_H

typedef struct Node{
    int info;
    struct Node *next;
} Node;

typedef struct List{
    int num;
    struct Node *head;
    struct Node *tail;
} List;

typedef struct BucktList{
    int num;
    struct List **bucketList;
} BucketList;

BucketList *createBucketList(int num);
List *createList();
Node *createNode(int info);
void destroyNode(Node **node);
void destroyList(List **list);
void destroyBucketList(BucketList **bucketList);

void insertInfoList(int info,  List *list);

#endif 
