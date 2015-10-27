
#include <stdlib.h>
#include <stdio.h>
#include "treeAvl.h"

#define TRUE 1
#define FALSE 0

void findLowest(Root **root, Root **wanted);

/*
int main(){
    int *heightChanged;
    int option, value;
    Root *node, *tree=NULL;
    
    printf("--------\n");
    node = createNode(10, 0);
    insertNode(&tree, heightChanged, node);
    printTreeAVL(tree, 0);
    printf("--------\n");
    node = createNode(7, 0);
    insertNode(&tree, heightChanged, node);
    printTreeAVL(tree, 0);
    printf("--------\n");
    node = createNode(20, 0);
    insertNode(&tree, heightChanged, node);
    printTreeAVL(tree, 0);
    printf("--------\n");
    node = createNode(8, 0);
    insertNode(&tree, heightChanged, node);
    printTreeAVL(tree, 0);
    printf("--------\n");
    node = createNode(4, 0);
    insertNode(&tree, heightChanged, node);
    printTreeAVL(tree, 0);
    printf("--------\n");
    node = createNode(9, 0);
    insertNode(&tree, heightChanged, node);
    printTreeAVL(tree, 0);
    printf("--------\n");
    
    do{
	printf("1 - inserir\n");
	printf("2 - remove\n");
	printf("3 - mostrar arvore\n");
	printf("0 - sair\n"); 
	scanf("%d", &option);
	printf("---\n");
	switch(option){
	case 1:
	    printf("Id a ser inserido: ");
	    scanf("%d", &value);
	    node = createNode(value, 0);
	    insertNode(&tree, heightChanged, node);
	    break;
	case 2:
	    printTreeAVL(tree, 0);
	    printf("Id a ser removido: ");
	    scanf("%d", &value);
	    removeNode(&tree, value, heightChanged);
	    break;
	case 3:
	    printTreeAVL(tree, 0);
	    break;
	}
	printf("-------------\n");
    }while(option != 0);

    
    destroyRoot(&tree);
    return 0;
}
*/

void insertNode(Root **root, int *heightChanged, Root *new){
    /* A Arvore esta vazia  */
    if((*root) == NULL){
	(*root) = new;
	(*heightChanged) = TRUE;
	return;
    }
    if(new->id < (*root)->id){
	/* Inserir a esquerda e verificar balanceamento  */
	insertNode(&(*root)->left, heightChanged, new);
	if((*heightChanged))
	    checkNodeLeft(root, heightChanged, TRUE);
    }else if(new->id > (*root)->id){
	/* Inserir a direita e verificar balanceamento  */
	insertNode(&(*root)->right, heightChanged, new);
	if((*heightChanged))
	    checkNodeRight(root, heightChanged, TRUE);
    }
}

void removeNode(Root **root, int id, int *heightChanged){
    Root *remove, *aux, *prev;
    
    /* Procura o id na arvore  */
    if((*root) == NULL){
	(*heightChanged) = FALSE;
	return;
    }
    if(id < (*root)->id){
	/* Remover esquerda == Adicionar na direita */
	removeNode(&(*root)->left, id, heightChanged);
	if((*heightChanged))
	    checkNodeRight(root, heightChanged, FALSE);
    }else if((id > (*root)->id)){
	/* Remover direita == Adicionar na esquerda */
	removeNode(&(*root)->right, id, heightChanged);
	if((*heightChanged))
	    checkNodeLeft(root, heightChanged, FALSE);
    }else if((id == (*root)->id)){
	/* Ao remover o No, verificar se ele vai mudar a altura 
	   Trocar com o proximo valor in-order da arvore binaria
	 */
	remove = (*root);
	(*heightChanged) = TRUE;
	if(remove->left == NULL && remove->right == NULL){
	    /* No NAO tem filhos */
	    (*root) = NULL;
	}
	if(remove->left == NULL && remove->right != NULL){
	    /* No tem filho DIREITA */
	    (*root) = remove->right;
	    remove->right = NULL;
	}
	if(remove->left != NULL && remove->right == NULL){
	    /* No tem filho ESQUERDA */
	    (*root) = remove->left;
	    remove->left = NULL;
	}
	if(remove->left != NULL && remove->right != NULL){
	    /* No tem DOIS filhos */
	    findLowest(&(*root)->right, &aux);
	    
	    if(remove->right != NULL)
		aux->right = remove->right;
	    aux->left = remove->left;
	    aux->balance = remove->balance;
	    remove->right = NULL;
	    remove->left = NULL;
	    (*root) = aux;
	}
	free(remove);
    }
}

void findLowest(Root **root, Root **wanted){
    int *heightChanged;
    (*heightChanged) = TRUE;
    if((*root)->left == NULL){
	(*wanted) = (*root);
	(*root) = NULL;
	return;
    }
    findLowest(&(*root)->left, wanted);
    checkNodeRight(root, heightChanged, FALSE);
}

void rotationLeft(Root **root){
    Root *nodeTrade;
    nodeTrade = (*root);
    (*root) = (*root)->right;
    nodeTrade->right = (*root)->left;
    (*root)->left = nodeTrade;
}
void rotationRight(Root **root){
    Root *nodeTrade;
    nodeTrade = (*root);
    (*root) = (*root)->left;
    nodeTrade->left = (*root)->right;
    (*root)->right = nodeTrade;
}


void destroyRoot(Root **root){
    if((*root) != NULL){
	if((*root)->left != NULL)
	    destroyRoot(&(*root)->left);
	if((*root)->right != NULL)
	    destroyRoot(&(*root)->right);
	
	free((*root));
	(*root) = NULL;
    }
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
    
void printTreeAVL(Root *root, int level){
    int i;
    if(root != NULL){
	if(root->right != NULL)
	    printTreeAVL(root->right, level+1);
	
	for(i=0;i<level;i++)
	    printf("[..]");
	printf("{%d/%d}\n", root->id, root->balance);
	
	if(root->left != NULL)
	    printTreeAVL(root->left, level+1);
    }
}

void checkNodeRight(Root **root, int *heightChanged, int isGrowing){
    int balanceRoot = (*root)->balance;
    int balanceRight, balanceRightLeft;
    switch(balanceRoot){
    case -1:
	(*root)->balance = 0;
	if(isGrowing)
	    (*heightChanged) = FALSE;
	else
	    (*heightChanged) = TRUE;
	break;
    case 0:
	(*root)->balance = 1;
	if(isGrowing)
	    (*heightChanged) = TRUE;
	else
	    (*heightChanged) = FALSE;
	break;
	break;
    case 1:
	balanceRight = (*root)->right->balance;
	switch(balanceRight){
	case 1:
	    (*root)->balance = 0;
	    (*root)->right->balance = 0;
	    rotationLeft(root);
	    if(isGrowing)
		(*heightChanged) = FALSE;
	    else
		(*heightChanged) = TRUE;
	break;
	    break;
	case -1:
	    balanceRightLeft = (*root)->right->left->balance;
	    switch(balanceRightLeft){
	    case -1:
		if((*root)->left != NULL)
		    (*root)->right->balance = 1;
		else
		    (*root)->right->balance = 0;
		
		(*root)->balance = 0;
		(*root)->right->left->balance = 0;
		break;
	    case 0 :
		(*root)->balance = 0;
		(*root)->right->balance = 0;
		(*root)->right->left->balance = 0;
		break;
	    case 1:
		(*root)->balance = -1;
		(*root)->right->balance = -1;
		(*root)->right->left->balance = 0;
		break;
	    }
	    rotationRight(&(*root)->right);
	    rotationLeft(root);
	    if(isGrowing)
		(*heightChanged) = FALSE;
	    else
		(*heightChanged) = TRUE;
	    break;
	}
	break;
    }
}

void checkNodeLeft(Root **root, int *heightChanged, int isGrowing){
    int balanceRoot = (*root)->balance;
    int balanceLeft, balanceRight, balanceLeftRight;
    switch(balanceRoot){
    case 1:
	(*root)->balance = 0;
	if(isGrowing)
	    (*heightChanged) = FALSE;
	else
	    (*heightChanged) = TRUE;
	break;
    case 0:
	(*root)->balance = -1;
	if(isGrowing)
	    (*heightChanged) = TRUE;
	else
	    (*heightChanged) = FALSE;
	break;
    case -1:
	balanceLeft = (*root)->left->balance;
	switch(balanceLeft){
	case -1:
	    (*root)->balance = 0;
	    (*root)->left->balance = 0;
	    rotationRight(root);
	    if(isGrowing)
		(*heightChanged) = FALSE;
	    else
		(*heightChanged) = TRUE;
	    break;
	case 1:
	    balanceLeftRight = (*root)->left->right->balance;
	    switch(balanceLeftRight){
	    case -1:
		(*root)->balance = 0;
		(*root)->left->balance = 0;
		(*root)->left->right->balance = 1;
		break;
	    case 0 :
		(*root)->balance = 0;
		(*root)->left->balance = 0;
		(*root)->left->right->balance = 0;
		break;
	    case 1:
		if((*root)->right != NULL)
		    (*root)->left->balance = -1;
		else
		    (*root)->left->balance = 0;
		
		(*root)->balance = 0;
		(*root)->left->right->balance = 0;
		break;
	    }
	    rotationLeft(&(*root)->left);
	    rotationRight(root);
	    if(isGrowing)
		(*heightChanged) = FALSE;
	    else
		(*heightChanged) = TRUE;
	    break;
	}
	break;
    }
}
