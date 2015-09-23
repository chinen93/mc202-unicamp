/* Pedro hideaki Uiechi Chinen
   175828
   Lab05 - Calculadora pseudocientifica
*/

#include <stdio.h>
#include <stdlib.h>
#include "root.h"

int operation(Root *root);
void printTree(Root *root, int level);

int main(){
    Root *root;
    int ret;
    
    root = getTreeSTDIO( );
    if(root != NULL){
        printTree(root, 0);
        
        ret = operation(root);
        
        printf("%d\n", ret);
        destroyRoot(&root);
    }else{
        printf("Tree not found!\n");
        exit(1);
    }
    return 0;
}


int operation(Root *root){
    if(root->left != NULL && root->right != NULL){
        switch(root->info){
        case '+':
            return operation(root->left) + operation(root->right);
        case '-':
            return operation(root->left) - operation(root->right);
        case '*':
            return operation(root->left) * operation(root->right);
        case '/':
            return operation(root->left) / operation(root->right);
        }
    }
    printf("[%d]", root->number);
    return root->number;
}


void printTree(Root *root, int level){
    int i;
    
    if(root->right != NULL)
        printTree(root->right, level+1);

    for(i=0; i<level; i++)
        printf("[..]");
    if(root->number == 0)
        printf("%c\n", root->info);
    else
        printf("%d\n", root->number);

    if(root->left != NULL)
        printTree(root->left, level+1);
}
