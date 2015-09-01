#include "pilha.h"
#include <stdio.h>

#define TRUE 1
#define FALSE 0

char isMatrioshka(Stack stack){
    Stack *stackNumber, *stackSumPartial;
    node *node, *nodeAux;
    int sum = 0, lastNumber, sumPartial;

    stackNumber = createStack();
    stackSumPartial = createStack();
    
    node = popNode(stack);
    lastNumber = node->info;
    sumPartial = node->info;
    pushNode(node, stack);
    
    while(!isStackEmpty(stack)){
        node = popNode(stack);
        sum += node->info;
        sumPartial += node->info;

        /* If the sum partial of this level is grater than the level
           return false
        */
        if(sumPartial > lastNumber)
            return FALSE;

        /* Positive numbers are stacked to know if the order is correct 
         */
        if(node->info > 0){
            pushNode(node, stackNumber);
            pushInt(sumPartial, stackSumPartial);
        }else{
            /* Negative numbers needs a pair in the stack 
               of positive numbers */
            nodeAux = popNode(stackNumber);
            if(node->info + nodeAux->info != 0)
                return FALSE;
        }
        
        lastNumber = node->info;
    }
    
    return TRUE;
}
