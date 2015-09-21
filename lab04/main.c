/*
  Nome: Pedro Hideaki Uiechi Chinen
  Ra  : 175828
  Laboratorio 04 - Os Caca Pixels
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "image.h"
#include "bucketList.h"

BucketList *sortIntensity(Image *image);
BucketList *equalize(BucketList *bucketSort, int maxEqual, int numGroups);
void printBucket(BucketList *bucket);


int main(){
    Image *image;
    BucketList *bucketEqual, *bucketSort;
    char *nameImage[81];
    int  maxEqual, beginGap, endGap, numGroups;
    int i, j;

    /* Get all the user input and make some validation */
    scanf("%s ", nameImage);
    image = readImageP5(nameImage);
    if(image != NULL){
        scanf("%d", &maxEqual);
        scanf("%d %d", &beginGap, &endGap);

        /* Sort Image by intensity */
        bucketSort = sortIntensity(image);
        
        /* Calculate number os groups, create these groups */
        numGroups = ceil(image->n/maxEqual);
        bucketEqual = equalize(bucketSort, maxEqual, numGroups);

        /* Free memory */
        destroyList(&bucketSort);
        destroyList(&bucketEqual);
        destroyImage(&image);
    }
    return 0;
}

BucketList *sortIntensity(Image *image){
    int i, j;
    BucketList *bucket;

    bucket = createBucketList(256);
    for(i=0; i<255; i++)
        for(j=0; j<image->n; j++)
            if(image->pixel[j] == i){
                insertAddressList(&image->pixel[j],
                                  bucket->bucketList[i]);
            }

    return bucket;
}

BucketList *equalize(BucketList *bucketSort, int maxEqual, int numGroups){
    int i, j, count;
    BucketList *bucket;
    Node *node;
    
    bucket = createBucketList(numGroups);
    node = bucketSort->bucketList[0]->head;
    i = 0;
    j = 0;
    count = 0;
    
    while(count < maxEqual && j < numGroups && i < bucketSort->num){
        while(node != NULL && count < maxEqual){
            inseertAddressList(node->address, bucket->bucketList[j]);
        
            count++;
            node = node->next;
        }
        if(node == NULL){
            i++;
            if(i < bucketSort->num)
                node = bucketSort->bucketList[i]->head;
        }
        if(count == maxEqual){
            j++;
            count = 0;
        }
    }
}

void printBucket(BucketList *bucket);
