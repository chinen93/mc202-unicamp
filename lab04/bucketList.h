#ifndef BUCKETLIST_H
#define BUCKETLIST_H

typedef struct Node{
    int *address;
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
Node *createNode(int *address);
void destroyNode(Node **node);
void destroyList(List **list);
void destroyBucketList(BucketList **bucketList);

void insertAddressList(int *address, List *list);

#endif 
