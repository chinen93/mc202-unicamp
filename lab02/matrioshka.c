/* Nome: Pedro Hideaki Uiechi Chinen
* RA: 175828
* Laboratorio 02 - Matrioshkas Generalizadas */

#include "pilha.h"
#include "matrioshka.h"

#define TRUE 1
#define FALSE 0

char isMatrioshka(Stack *stack){
    Stack *stackNumPos, *stackSumPartial;
    int sumPartial, number, numberPos;
    char ret = TRUE;
    
    stackNumPos = createStack();
    stackSumPartial = createStack();

    /* Check if the first number isn't less than 0  */
    if(! isStackEmpty(stack)){
        number = popInfo(stack);
        if(number < 0){
            ret = FALSE;
        }

        /* Put it into the aux stacks  */
        pushInfo(number, stackSumPartial);
        pushInfo(number, stackNumPos);
    }

    while(! isStackEmpty(stack) && ret){
        number = popInfo(stack);
        
        /* If the number is positive  */
        if(number > 0){
            /* Check if it fits in the last doll */
            sumPartial = popInfo(stackSumPartial);
            sumPartial -= number;

            /* Didn't fit */
            if(sumPartial <= 0){
                ret = FALSE;
            }

            /* Push into the aux stacks*/
            pushInfo(sumPartial, stackSumPartial);
            pushInfo(number, stackSumPartial);
            pushInfo(number, stackNumPos);
        }else{
            /* Number is negative  */
            numberPos = popInfo(stackNumPos);
            sumPartial = numberPos + number;
            /* Check if the last number in the stackNumPos 
               has the same absolute value  */
            if(sumPartial != 0){
                ret = FALSE;
            }
            popInfo(stackSumPartial);
        }
    }

    destroyStack(stackNumPos);
    destroyStack(stackSumPartial);
    return ret;
}
