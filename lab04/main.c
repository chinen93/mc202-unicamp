/*
  Nome: Pedro Hideaki Uiechi Chinen
  Ra  : 175828
  Laboratorio 04 - Os Caca Pixels
 */

#include <stdio.h>
#include <stdlib.h>
#include "image.h"
#include "bucketList.h"

BucketList *sortIntensity(Image *image);
BucketList *equalize(BucketList *bucketSort, int maxEqual, int numGroups);
void printBucket(BucketList *bucket, int begin, int end);
int cima(double number);

void printBucketAll(BucketList *bucket){
    Node *node;
    int i;
    for(i = 0; i<=bucket->num; i++){
        if(i < bucket->num){
            printf("[%d]      ",i);
            node = bucket->bucketList[i]->head;
            while(node != NULL){
                printf("%d ", node->info);
                node = node->next;
            }
            printf("\n");
        }
    }
    printf("\n");
}

int main(){
    Image *image;
    BucketList *bucketEqual, *bucketSort;
    char nameImage[81];
    int  maxEqual, beginGap, endGap, numGroups;

    /* Get all the user input and make some validation */
    scanf("%s ", nameImage);
    image = readImageP5(nameImage);
    if(image != NULL){
        scanf("%d", &maxEqual);
        scanf("%d %d", &beginGap, &endGap);

        /* Sort Image by intensity */
        bucketSort = sortIntensity(image);
        
        /* Calculate number os groups, create these groups */
        numGroups = cima((double)image->n/(double)maxEqual);

        bucketEqual = equalize(bucketSort, maxEqual, numGroups);
        printBucket(bucketEqual, beginGap, endGap);

        /* Free memory */
        destroyBucketList(&bucketSort);
        destroyBucketList(&bucketEqual);
        destroyImage(&image);
    }
    return 0;
}

BucketList *sortIntensity(Image *image){
    int i, j;
    BucketList *bucket;

    /* Put every position of pixel in their respective bucket sorted by intensity */
    bucket = createBucketList(256);
    for(i=0; i<256; i++)
        for(j=0; j<image->n; j++)
            if(image->pixel[j] == i){
                insertInfoList(j, bucket->bucketList[i]);
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

    /* Go throught every bucket in [bucketSort] and put into [bucket] [maxEqual] positions.
       in the end [bucket] will be equalizated 
     */
    while(count < maxEqual && j < numGroups && i < bucketSort->num){
        while(node != NULL && count < maxEqual){
            insertInfoList(node->info, bucket->bucketList[j]);
        
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

    return bucket;
}

void printBucket(BucketList *bucket, int begin, int end){
    Node *node;
    int i;
    for(i = begin; i<=end; i++){
        if(i < bucket->num){
            node = bucket->bucketList[i]->head;
            while(node != NULL){
                printf("%d ", node->info);
                node = node->next;
            }
        }
    }
    printf("\n");
}

int cima(double number){
    int rest, ret;
    double aux;
    
    aux  = (double)number*10;
    rest = (int) aux%10;
    ret  = (int) aux/10;
    
    if(rest > 0)
        ret++;
    
    return ret;
}
