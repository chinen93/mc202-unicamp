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

void equalize(BuckeList *list, int **pixel);

int main(){
    Image *image;
    BucketList *list;
    char *nameImage[81];
    int  maxEqual, beginGap, endGap, numGroups;
    int i, j;

    /* Get all the user input and make some validation */
    scanf("%s ", nameImage);
    image = readImageP5(nameImage);
    if(image != NULL){
        scanf("%d", &maxEqual);
        scanf("%d %d", &beginGap, &endGap);

        /* Calculate number os groups, create these groups */
        numGroups = ceil(image->n/maxEqual);
        list = createBucketList(numGroups);

        /* Equalize and show results */
        equalize(list, &image->pixel);
        for(i=beginGap; i<endGap; i++){
            for(j=0, j<image->n ; j++){
                if(image->pixel[j] == i)
                    printf("%d ",j);
            }
        }
        printf("\n");

        /* Free memory */
        destroyList(&list);
        destroyImage(&image);
    }
    return 0;
}

void equalize(BuckeList *list, int **pixel){
    
}
