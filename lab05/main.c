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
    
    root = getTreeSTDIO();
    
    printTree(root, 0);
    
    ret = operation(root);

    printf("%d\n", ret);
    
    destroyRoot(&root);
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
    printf("[%d]", root->info-'0');
    return root->info-'0';
}


void printTree(Root *root, int level){
    int i;
    
    if(root->right != NULL)
        printTree(root->right, level+1);

    for(i=0; i<level; i++)
        printf("[..]");
    printf("%c\n", root->info);

    if(root->left != NULL)
        printTree(root->left, level+1);
}
