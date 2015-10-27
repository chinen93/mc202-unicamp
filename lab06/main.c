#include "treeAvl.h"
#include "heap.h"
#include <stdin.h>
#include <stdlib.h>

int main(){
    FILE *file;
    char filename[80];
    Root *avl;
    Heap *heap;
    char option;
    int  

    /* Ler o arquivo binario  */
    scanf("%s", filename);
    file = fopen(filename, "rwb");
    if(file == NULL){
	printf("File [%s] not found!", filename);
	exit(0);
    }
    avl = createAvlFromBin(file);

    /* Ler os comandos do usuario  */
    do{
	scanf("%c", &option);
	switch(option){
	case 'i':
	    
	    break;
	case 'r':
	    break;
	case 'e':
	    break;
	}
    }while(option != 'e');

    /* Terminar programa desalocar memorias  */
    fclose(file);
    return 0;
}


Root *createAvlFromBin(FILE *file){
}
