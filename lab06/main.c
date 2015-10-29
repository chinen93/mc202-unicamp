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
    /* Criar a Arvore AVL a partir do database binario 
       e o HEAP com o tamanho de operacoes que serao executadas
       pois nao sabemos de cara quantas remocoes ocorrerao */
    avl = createAvlFromBin(file, &qtdRecords);
    scanf("%d", &numOperations);
    heap = createHeap(numOperations);
    do{
	scanf("%c", &option);
	switch(option){
	case 'i':
	    /* Ao INSERIR um indentificador sera passado e uma string
	       Na string tratar para que o caracter '\n' nao apareca no banco de dados 
	       colocar na avl o no com os dados passados */
	    scanf("%d ", &indentifier);
	    fgets(data, 1000, stdin);
	    slashNPosition = strchr(data, '\n');
	    (*slashNPosition) = '\0';
	    record = createRecord(indentifier, data);
	    insertRecord(&avl, &heap, record, &qtdRecords, file);
	    numOperations--;
	    break;
	case 'r':
	    /* Ao REMOVER um indentificador sera passado
	       remover da avl o no com o indentificador */
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
    /* Mostrar os dados dos nos com o balanceamento pedido */
    showNodesWithBalance(avl, orderedBalance, file);

    
    /* Terminar programa desalocar memorias  */
    destroyRoot(&avl);
    destroyHeap(&heap);
    fclose(file);
    return 0;
}

Root *createAvlFromBin(FILE *file, int *qtdRecords){
    /* Localização == em qual byte começa o registro 
       Guardar a informacao de quantos registros o banco de dados tem */
    Root *node, *tree = NULL;
    Record *record;
    record = createRecord(0, "");
    (*qtdRecords) = 0;
    /* Ler os registros e colocar na AVL  */
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
    long int placeToInsert;

    /* Pega do Heap a menor posicao liberada do arquivo  */
    placeToInsert = removeLongIntHeap(heap);
    if(placeToInsert != -1){
	/* Se a posicao existe colocar no meio do arquivo */
	fseek(file, placeToInsert, SEEK_SET);
	node = createNode(record->id, placeToInsert);
    }else{
	/* Senao colocar no final do arquivo */
	fseek(file, (*numReg)*sizeof(Record), SEEK_SET);
	(*numReg)++;
	node = createNode(record->id, (*numReg)*sizeof(Record));
    }
    
    /* Escrever no arquivo com o fwrite 
       colocar o novo no na AVL */

    /* TODO: O endereço da porra toda esta errado 1 a mais
       Sr Qularque Quenti esta errado por 1 sizeof(Record)
     */
    
    fwrite(record, 1, sizeof(Record), file);
    insertNodeTree(root, node);
}

void removeRecord(Root **root, Heap **heap, int id){
    Root *node = NULL;
    /* Remove da Arvore o id do Record */
    node = removeNodeTree(root, id);
    /*  Coloca no Heap o id do Record */
    if(node != NULL){
	insertLongIntHeap(heap, node->indexReg);
	printf("[%d]\n", id); 
	printHeap((*heap));
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
