/* Pedro hideaki Uiechi Chinen
   175828
   Lab05 - Calculadora pseudocientifica
*/

#include <stdio.h>
#include <stdlib.h>
#include "root.h"

Root *getTreeSTDIO(){
    Root *root = NULL;
    char  info;
    scanf("%c", &info);
    if(info == '('){
        root = createRoot();
        root->left = getTreeSTDIO();
        scanf("%c", &info);
        if(info == ')')
            scanf("%c", &info);
        if(info == '-'){
            scanf("%c", &info);
            switch(info){
            case '1':
                info = '+';
                break;
            case '2':
                info = '-';
                break;
            case '3':
                info = '*';
                break;
            case '4':
                info = '/';
                break;
            }
        }

        root->info = info;
        scanf("%c", &info);
        root->right = getTreeSTDIO();
    }

    return root;
}

Root *createRoot(){
    Root *root;
    root = (Root *)calloc(1, sizeof(Root));
    root->info = 0;
    root->left = NULL;
    root->right = NULL;
    return root;
}

void destroyRoot(Root **root){
    if((*root)->left != NULL)
        destroyRoot(&(*root)->left);
    
    if((*root)->right != NULL)
        destroyRoot(&(*root)->right);

    free(*root);
    (*root) = NULL;
}
