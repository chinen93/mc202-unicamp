/* Pedro hideaki Uiechi Chinen
   175828
   Lab05 - Calculadora pseudocientifica
*/


#ifndef ROOT_H
#define ROOT_H

typedef struct Root{
    char info;
    struct Root *left;
    struct Root *right;    
} Root;

Root *getTreeSTDIO();
Root *createRoot();
void destroyRoot(Root **root);
#endif
