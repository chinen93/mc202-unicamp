
#include "pilha.h"
#include "matrioshka.h"

#define TRUE 1
#define FALSE 0

char isMatrioshka(Stack *stack){
    Stack *stackNumPos, *stackSumPartial;
    int sumPartial;
    Node *node, *nodePos;

    stackNumPos = createStack();
    stackSumPartial = createStack();

    if(! isStackEmpty(stack)){
        node = popNode(stack);
        if(node->info < 0){
            destroyStack(stackNumPos);
            destroyStack(stackSumPartial);
            return FALSE;
        }

        pushInfo(node->info, stackSumPartial);
        pushNode(node, stackNumPos);
    }

    while(! isStackEmpty(stack)){
        node = popNode(stack);

        if(node->info > 0){
            sumPartial = popInfo(stackSumPartial);
            sumPartial -= node->info;
            if(sumPartial <= 0){
                destroyStack(stackNumPos);
                destroyStack(stackSumPartial);
                return FALSE;
            }

            pushInfo(sumPartial, stackSumPartial);
            pushInfo(node->info, stackSumPartial);
            pushInfo(node->info, stackNumPos);
        }else{
            nodePos = popNode(stackNumPos);
            sumPartial = nodePos->info + node->info;
            if(sumPartial != 0){
                destroyStack(stackNumPos);
                destroyStack(stackSumPartial);
                return FALSE;
            }
            popInfo(stackSumPartial);
        }
    }

    destroyStack(stackNumPos);
    destroyStack(stackSumPartial);
    return TRUE;
}
