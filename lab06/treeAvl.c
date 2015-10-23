
#include <stdlib.h>
#include "treeAvl.h"

#define TRUE 1
#define FALSE 0

void insertNode(Root **root, int *heightGrows, Root *new){
    /* A Arvore esta vazia  */
    if((*root) == NULL){
	(*root) = new;
	heightGrows = TRUE;
	return;
    }
    if(new->id < (*root)->id){
	/* Inserir a esquerda e verificar balanceamento  */
	insertNode((*root)->left, heightGrows, new);
	if(heightGrows)
	    checkNodeLeft(root, heightGrows);
    }else if(new->id > (*root)->id){
	/* Inserir a direita e verificar balanceamento  */
	insertNode((*root)->right, heightGrows, new);
	if(heightGrows)
	    checkNodeRight(root, heightGrows);
    }
}

void removeNode(Root **root, int id, int *heightLowers){
    Root *remove;
    /* Procura o id na arvore  */
    if((*root) == NULL)
	return;
    if(id < (*root)->id){
	/* Remover esquerda == Adicionar na direita */
	removeRoot(&(*root)->left, id, heightLowers);
	if(heightLowers)
	    checkNodeRight(root, heightLowers)
    }else if((id > (*root)->id)){
	/* Remover direita == Adicionar na esquerda */
	removeRoot(&(*root)->right, id, heightLowers);
	if(heightLowers)
	    checkNodeLeft(root, heightLowers)
    }else if((id == (*root)->id)){
	remove = (*root);
	heightLowers = TRUE;
	if((*root)->left != NULL || (*root)->right != NULL){
	    if((*root)->left == NULL){
		(*root) = (*root)->right;
	    }else if((*root)->right == NULL){
		(*root) = (*root)->left;
	    }else{
		
	    }
	}
	/* Casos  
	   No tem filhos
	      1 filho
	      2 filhos
	   Sem filhos

	   Balancear a arvore
	 */
    }

    /* 1 - in-order sucessor para o lugar do deletado
       2 - faça o no de 1 adotar os filhos do no deletado (girar)
       3 - Verificar os balanceamentos
       4 - Rodar para balancear
       5 - repita 3 e 4 ate estar balanceada

     */
	
}

void rotationLeft(Root **root){
    Root *aux;
    aux = (*root)->right;
    aux->left = (*root);
    (*root) = aux;
}
void rotationRight(Root **root){
    Root *aux;
    aux = (*root)->left;
    aux->right = (*root);
    (*root) = aux;  
}
void checkNodeRight(Root **root, int *heightGrows){
    int balanceRoot = (*root)->balance;
    int balanceRight, balanceRightLeft;
    switch(balanceRoot){
    case -1:
	(*root)->balance = 0;
	heightGrows = FALSE;
	break;
    case 0:
	(*root)->balance = 1;
	heightGrows = TRUE;
	break;
    case 1:
	balanceRight = (*root)->right->balance;
	switch(balanceRight){
	case 1:
	    (*root)->balance = 0;
	    (*root)->right->balance = 0;
	    rotationLeft(root);
	    heightGrows = FALSE;
	    break;
	case -1:
	    (*root)->balance = 0;
	    balanceRightLeft = (*root)->right->left->balance;
	    switch(balanceRightLeft){
	    case -1:
		(*root)->left->balance = 0;
		(*root)->right->left->balance = 1;
		break;
	    case 0 :
		(*root)->left->balance = 0;
		(*root)->right->left->balance = 0;
		break;
	    case 1:
		(*root)->left->balance = -1;
		(*root)->right->left->balance = 0;
		break;
	    }
	    rotationRight(&(*root)->right);
	    rotationLeft(root);
	    heightGrows = FALSE;
	    break;
	}
	break;
    }
}

void checkNodeLeft(Root **root, int *heightGrows){
    int balanceRoot = (*root)->balance;
    int balanceLeft, balanceLeftRight;
    switch(balanceRoot){
    case -1:
	(*root)->balance = 0;
	heightGrows = FALSE;
	break;
    case 0:
	(*root)->balance = 1;
	heightGrows = TRUE;
	break;
    case 1:
	balanceLeft = (*root)->left->balance;
	switch(balanceLeft){
	case -1:
	    (*root)->balance = 0;
	    (*root)->left->balance = 0;
	    rotationRight(root);
	    heightGrows = FALSE;
	    break;
	case 1:
	    (*root)->balance = 0;
	    balanceLeftRight = (*root)->left->left->balance;
	    switch(balanceLeftRight){
	    case -1:
		(*root)->left->balance = 0;
		(*root)->left->right->balance = 1;
		break;
	    case 0 :
		(*root)->left->balance = 0;
		(*root)->left->right->balance = 0;
		break;
	    case 1:
		(*root)->left->balance = -1;
		(*root)->left->right->balance = 0;
		break;
	    }
	    rotationLeft(&(*root)->left);
	    rotationRight(root);
	    heightGrows = FALSE;
	    break;
	}
	break;
    }
}

void destroyRoot(Root **root){
    if((*root)->left == NULL && (*root)->left == NULL){
	free((*root));
	(*root) = NULL;
    }

    if((*root)->left != NULL)
	destroyRoot(&(*root)->left);
    if((*root)->right != NULL)
	destroyRoot(&(*root)->right);
}

Root *createNode(int id, int indexReg){
    Root *root = (Root *)calloc(1, sizeof(Root));
    root->id = id;
    root->indexReg = indexReg;
    root->balance = 0;
    root->right = NULL;
    root->left  = NULL;
    return root;
}
    
