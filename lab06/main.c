/* 
   Nome: Pedro Hideaki Uiechi Chinen
   RA  : 175828
*/

#include "treeAvl.h"
#include "heap.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Record {
    unsigned int id;
    char data[1000];
} Record;

Root *createAvlFromBin(FILE *file, int *qtdRecords);
Record *createRecord(unsigned int id, char* data);
void destroyRecord(Record **record);
void insertRecord(Root **root, Heap **heap,
		  Record *record, int *numReg, FILE *file);
void removeRecord(Root **root, Heap **heap, int id);
void showNodesWithBalance(Root *root, int orderedBalance, FILE *file);

int main(){
    FILE *file;
    char filename[80];
    Root *avl;
    Heap *heap;
    char option;
    Record *record;
    char data[1000];
    int  numOperations = 0, orderedBalance, indentifier;
    int qtdRecords;
    char *slashNPosition;

    /* Ler o arquivo binario  */
    scanf("%s", filename);
    file = fopen(filename, "r+b");
    if(file == NULL){
	printf("File [%s] not found!", filename);
	exit(0);
    }
    avl = createAvlFromBin(file, &qtdRecords);
    scanf("%d", &numOperations);
    heap = createHeap(numOperations);

    printf("---\n");
    printTreeAVL(avl, 0);
    printf("------------\n");
    
    do{
	scanf("%c", &option);
	switch(option){
	case 'i':
	    scanf("%d", &indentifier);
	    fgets(data, 1000, stdin);
	    slashNPosition = strchr(data, '\n');
	    (*slashNPosition) = '\0';
	    record = createRecord(indentifier, data);
	    insertRecord(&avl, &heap, record, &qtdRecords, file);
	    numOperations--;
	    break;
	case 'r':
	    scanf("%d", &indentifier);
	    removeRecord(&avl, &heap, indentifier);
	    numOperations--;
	    break;
	}
    }while(numOperations > 0);

    printf("---\n");
    printTreeAVL(avl, 0);
    printf("------------\n");

    scanf("%d", &orderedBalance);
    showNodesWithBalance(avl, orderedBalance, file);
    /* Terminar programa desalocar memorias  */

    destroyRoot(&avl);
    destroyHeap(&heap);
    fclose(file);
    return 0;
}

Root *createAvlFromBin(FILE *file, int *qtdRecords){
    /* Localização == em qual byte começa o registro */
    Root *node, *tree = NULL;
    Record *record;
    record = createRecord(0, "");
    (*qtdRecords) = 0;
    while(fread(record, sizeof(Record), 1, file)){
	node = createNode(record->id, (*qtdRecords)*sizeof(Record));
	insertNodeTree(&tree, node);
	(*qtdRecords)++;
    }
    destroyRecord(&record);
    return tree;
}

Record *createRecord(unsigned int id, char* data){
    Record *record;
    record = (Record *)calloc(1, sizeof(Record));
    record->id = id;
    strncpy(record->data, data, 1000);
    return record;
}

void destroyRecord(Record **record){
    free(*record);
    (*record) = NULL;
}

void insertRecord(Root **root, Heap **heap,
		  Record *record, int *numReg, FILE *file){
    Root *node;
    long int placeToInsert = removeLongIntHeap(heap);

    if(placeToInsert != -1){
	/* Colocar no meio do arquivo */
	fseek(file, placeToInsert, SEEK_SET);
	node = createNode(record->id, placeToInsert);
    }else{
	/* Colocar no final do arquivo */
	/* incremente antes ou depois? */
	(*numReg)++;
	fseek(file, (*numReg)*sizeof(Record), SEEK_SET);
	node = createNode(record->id, (*numReg)*sizeof(Record));
    }
    /* Colocar no arquivo com o fwrite */
    fwrite(record, 1, sizeof(Record), file);
    insertNodeTree(root, node);
}

void removeRecord(Root **root, Heap **heap, int id){
    Root *node;
    /* Remove da Arvore o id do Record */
    node = removeNodeTree(root, id);
    /*  Coloca no Heap o id do Record */
    if(node != NULL){
	insertLongIntHeap(heap, node->indexReg);
	free(node);
    }
}

void showNodesWithBalance(Root *root, int orderedBalance, FILE *file){
    Record *record;
    record = createRecord(0, "");
    if(root != NULL){
	/* Ordem simetrica na final  */
        /* Percorre left */
	if(root->left != NULL)
	    showNodesWithBalance(root->left, orderedBalance, file);
	/* Verifica se o balanceamento eh o esperado */
	if(root->balance == orderedBalance){
	    /* da um fseek no arquivo com o indexReg do no atual */
	    fseek(file, root->indexReg, SEEK_SET);
	    /* imprime tudo do registro */
	    fread(record, sizeof(Record), 1, file);
	    printf("%s %ld\n", record->data, root->indexReg);
	}
	/* Percorre right */
	if(root->right != NULL)
	    showNodesWithBalance(root->right, orderedBalance, file);
	}
    destroyRecord(&record);
}
