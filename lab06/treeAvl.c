/* 
   Nome: Pedro Hideaki Uiechi Chinen
   RA  : 175828
*/

#include <stdlib.h>
#include <stdio.h>
#include "treeAvl.h"

#define TRUE 1
#define FALSE 0

/* Funcoes Internas de AVL  */
void findLowest(Root **root, Root **wanted, int *heightChanged);
void insertNode(Root **root, int *heightChanged, Root *new);
void removeNode(Root **root, int id, int *heightChanged, Root **remove);
void rotationLeft(Root **root);
void rotationRight(Root **root);
void checkNodeRight(Root **root, int *heightChanged, int isGrowing);
void checkNodeLeft(Root **root, int *heightChanged, int isGrowing);


int main(){
    int *heightChanged;
    int option, value;
    Root *node, *tree=NULL;
    int i, rand;
    
    printf("------------\n");
    node = createNode(99, 0);
    insertNodeTree(&tree, node);
    printTreeAVL(tree, 0);
    printf("------------\n");
    node = createNode(97, 0);
    insertNodeTree(&tree, node);
    printTreeAVL(tree, 0);
    printf("------------\n");
    node = createNode(103, 0);
    insertNodeTree(&tree, node);
    printTreeAVL(tree, 0);
    printf("------------\n");
    node = createNode(98, 0);
    insertNodeTree(&tree, node);
    printTreeAVL(tree, 0);
    printf("------------\n");
    node = createNode(102, 0);
    insertNodeTree(&tree, node);
    printTreeAVL(tree, 0);
    printf("------------\n");
    node = createNode(109, 0);
    insertNodeTree(&tree, node);
    printTreeAVL(tree, 0);
    printf("------------\n");
    
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
	    insertNodeTree(&tree, node);
	    break;
	case 2:
	    printTreeAVL(tree, 0);
	    printf("Id a ser removido: ");
	    scanf("%d", &value);
	    removeNodeTree(&tree, value);
	    break;
	case 3:
	    printTreeAVL(tree, 0);
	    break;
	}
    }while(option != 0);

    
    destroyRoot(&tree);
    return 0;
}

void insertNodeTree(Root **root, Root *new){
    int heightChanged;
    insertNode(root, &heightChanged, new);
    printf("=========================== I [%d]\n", new->id);
    printTreeAVL((*root), 0);
    printf("------------\n");
}

Root* removeNodeTree(Root **root, int id){
    int heightChanged;
    Root *node = NULL;
    removeNode(root, id, &heightChanged, &node);
    printf("=========================== R [%d]\n", id);
    printTreeAVL((*root), 0);
    printf("------------\n");
    return node;
}

void insertNode(Root **root, int *heightChanged, Root *new){
    /* A Arvore esta vazia  */
    if((*root) == NULL){
	(*root) = new;
	(*heightChanged) = TRUE;
    }else if((*root)->id == new->id){
	/* Tentar colocar o mesmo ID na arvore  */
	(*heightChanged) = FALSE;
    }else if(new->id < (*root)->id){
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

void removeNode(Root **root, int id, int *heightChanged, Root **remove){
    Root *aux;
    
    /* Procura o id na arvore  */
    if((*root) == NULL){
	(*heightChanged) = FALSE;
	return NULL;
    }
    if(id < (*root)->id){
	/* Remover esquerda == Adicionar na direita */
	removeNode(&(*root)->left, id, heightChanged, remove);
	if((*heightChanged))
	    checkNodeRight(root, heightChanged, FALSE);
    }else if((id > (*root)->id)){
	/* Remover direita == Adicionar na esquerda */
	removeNode(&(*root)->right, id, heightChanged, remove);
	if((*heightChanged))
	    checkNodeLeft(root, heightChanged, FALSE);
    }else if((id == (*root)->id)){
	/* Ao remover o No, verificar se ele vai mudar a altura 
	   Trocar com o proximo valor in-order da arvore binaria
	 */
	(*remove) = (*root);
	(*heightChanged) = TRUE;
	if((*remove)->left == NULL && (*remove)->right == NULL){
	    /* No NAO tem filhos */
	    (*root) = NULL;
	}
	if((*remove)->left == NULL && (*remove)->right != NULL){
	    /* No tem filho DIREITA */
	    (*root) = (*remove)->right;
	    (*remove)->right = NULL;
	}
	if((*remove)->left != NULL && (*remove)->right == NULL){
	    /* No tem filho ESQUERDA */
	    (*root) = (*remove)->left;
	    (*remove)->left = NULL;
	}
	if((*remove)->left != NULL && (*remove)->right != NULL){
	    /* No tem DOIS filhos */
	    findLowest(&(*root)->right, &aux, heightChanged);
	    
	    if((*remove)->right != NULL)
		aux->right = (*remove)->right;
	    aux->left = (*remove)->left;
	    aux->balance = (*remove)->balance;
	    
	    /* TODO  Esse balanco esta dando errado quando retiro o no 103*/
	    if((*heightChanged))
		checkNodeRight(root, heightChanged, FALSE);

	    
	    (*remove)->right = NULL;
	    (*remove)->left = NULL;
	    (*root) = aux;
	}
    }
}

void findLowest(Root **root, Root **wanted, int *heightChanged){
    if((*root)->left == NULL){
	(*wanted) = (*root);
	(*root) = NULL;
	(*heightChanged) = TRUE;
    }else{
	findLowest(&(*root)->left, wanted, heightChanged);
	if((*wanted)->right != NULL){
	    (*root)->left = (*wanted)->right;
	    (*wanted)->right = NULL;
	}
	if((*heightChanged))
	    checkNodeRight(root, heightChanged, FALSE);
    }
}

Root *searchIdTree(Root **root, int id){
    if((*root) == NULL)
	return NULL;
    
    if((*root)->id == id)
	return (*root);

    if(id < (*root)->id)
	return searchIdTree(&(*root)->left, id);
    if(id > (*root)->id)
	return searchIdTree(&(*root)->right, id);
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

Root *createNode(int id, long int indexReg){
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
	case 0:
	    (*root)->balance = 1;
	    (*root)->right->balance = -1;
	    rotationLeft(root);
	    if(isGrowing)
		(*heightChanged) = TRUE; /*     */
	    else
		(*heightChanged) = FALSE;
	    break;
	case -1:
	    balanceRightLeft = (*root)->right->left->balance;
	    switch(balanceRightLeft){
	    case -1:
		/* Contrario de checkLeft [-1][1][1]  */
		if((*root)->left == NULL){
		    (*root)->balance = 1;
		    (*root)->right->balance = 0; 
		}else{
		    (*root)->balance = 0;
		    (*root)->right->balance = 1; 
		}
		(*root)->right->left->balance = 0;
		break;
	    case 0 :
		(*root)->balance = 0;
		(*root)->right->balance = 0;
		(*root)->right->left->balance = 0;
		break;
	    case 1:
		/* Contrario de checkLeft [-1][1][-1]  */
		if((*root)->left == NULL){
		    (*root)->balance = 0; 
		    (*root)->right->balance = 1;
		}else{
		    (*root)->balance = -1; 
		    (*root)->right->balance = 0;
		}
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
 	case 0:
	    (*root)->balance = -1;
	    (*root)->right->balance = 1;
	    rotationLeft(root);
	    if(isGrowing)
		(*heightChanged) = TRUE;
	    else
		(*heightChanged) = FALSE;
	    break;
	case 1:
	    balanceLeftRight = (*root)->left->right->balance;
	    switch(balanceLeftRight){
	    case -1:
		/* Contrario de checkRight [1][-1][1]  */
		if((*root)->right == NULL){
		    (*root)->balance = 0;
		    (*root)->left->balance = -1;
		}else{
		    (*root)->balance = 1;
		    (*root)->left->balance = 0;		    
		}
		(*root)->left->right->balance = 0; 
		break;
	    case 0 :
		(*root)->balance = 0;
		(*root)->left->balance = 0;
		(*root)->left->right ->balance = 0;
		break;
	    case 1:
		/* Contrario de checkRight [1][-1][-1]  */
		if((*root)->right == NULL){
		    (*root)->balance = -1;
		    (*root)->left->balance = 0;
		}else{
		    (*root)->balance = 0;
		    (*root)->left->balance = -1;
		}
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
