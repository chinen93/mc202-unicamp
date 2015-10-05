#include <stdlib.h>
#include <stdio.h>

#define TAM 9

typedef struct Root{
    int info;
    struct Root *left;
    struct Root *right;
}Root;

Root *createTree(int *vet, int i);
Root *createRoot();
void destroyRoot(Root **root);
void ImprimeArvoreBinaria(Root  *T, int h, int altura);
void inserirIntTree(int num, int *vet);
void goDown(int *vet, int index);
void removeIntTree(int *vet);
void heapSort(int *vet);

int main(){
    int vet[TAM];
    Root *tree;
    
    vet[0] = 100;
    vet[1] = 90;
    vet[2] = 80;
    vet[3] = 30;
    vet[4] = 40;
    vet[5] = 60;
    vet[6] = 30;
    vet[7] = 20;
    vet[8] = -1;

    tree = createTree(vet, 0);
    ImprimeArvoreBinaria(tree, 0, 3);
    destroyRoot(&tree);
    printf("-------------------------------------------\n");
    inserirIntTree(95, vet);
    tree = createTree(vet, 0);
    ImprimeArvoreBinaria(tree, 0, 3);
    destroyRoot(&tree);
    printf("-------------------------------------------\n");
    removeIntTree(vet);
    tree = createTree(vet, 0);
    ImprimeArvoreBinaria(tree, 0, 3);
    destroyRoot(&tree);
    
}

Root *createTree(int *vet, int i){
    Root *root = NULL;
    if(vet[i] != ' ' && i < TAM){
	root = createRoot();
	root->info = vet[i];
	root->left = createTree(vet, 2*i+1);
	root->right = createTree(vet, 2*i+2);
    }
    return root;
}

Root *createRoot(){
    Root *root;
    root = calloc(1, sizeof(Root));
    return root;
}

void destroyRoot(Root **root){
    if((*root)->left != NULL)
	destroyRoot(&(*root)->left);
    
    if((*root)->right != NULL)
	destroyRoot(&(*root)->right);

    free((*root));
    (*root) = NULL;
}

void ImprimeArvoreBinaria(Root *T, int h, int altura){
  int i;

  if (T != NULL) {
    ImprimeArvoreBinaria(T->right, h+1, altura);
    for (i=0; i < h; i++) 
      printf("   ");
    printf("%d",T->info);
    for (i=0; i < altura-h; i++) 
      printf("---");
    printf("\n");
    ImprimeArvoreBinaria(T->left, h+1,altura);    
  }
}

void inserirIntTree(int num, int *vet){
    int i, j, aux;
    j = 8;
    vet[j] = num;
    i = (j-1)/2;
    while(vet[i] < vet[j]){
	aux    = vet[i];
	vet[i] = vet[j];
	vet[j] = aux;
	j = i;
	i = (j-1)/2;
    }
}

void removeIntTree(int *vet){
    vet[0] = vet[8];
    vet[8] = -1;
    goDown(vet, 0);
}

void goDown(int *vet, int index){
    int i, j, aux;    
    if (index < (TAM-1)/2){
	i = 2*index+1;
	j = 2*index+2;

	if(vet[i] > vet[j] && vet[index] < vet[i]){
	    aux = vet[index];
	    vet[index] = vet[i];
	    vet[i] = aux;
	    goDown(vet, i);
	}else if(vet[i] < vet[j] && vet[index] < vet[j]){
	    aux = vet[index];
	    vet[index] = vet[j];
	    vet[j] = aux;
	    goDown(vet, j);
	}
	
    }
}

void heapSort(int *vet){
	
}
