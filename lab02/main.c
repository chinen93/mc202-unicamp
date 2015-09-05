/* Nome: Pedro Hideaki Uiechi Chinen
* RA: 175828
* Laboratorio 02 - Matrioshkas Generalizadas */

#include <stdio.h>


#include "pilha.h"
#include "matrioshka.h"

int main(){
    Stack *stack;
    int size, number, i, sum;

    scanf("%d", &size);
    while(size != 0){
        stack = createStack();
        sum = 0;
        /* size is odd, a doll is open/closed without a fittible*/
        if(size % 2 != 0){
            printf ("Nao eh Matrioshka.\n");
        }else{
            /* Get the numbers  */
            for(i=0; i<size; i++){
                scanf("%d", &number);
                sum += number;
                pushInfo(number , stack);
            }
            /* If the sum is not equals to 0, 
               a doll is open/closed  without a fittible  */
            if(sum != 0){
                printf ("Nao eh Matrioshka.\n");
            }else{
                if(! isMatrioshka(stack)){
                    printf ("Nao eh Matrioshka.\n");
                }else{
                    printf ("Eh Matrioshka.\n");
                }
            }
        }
        /* Destroy the stack, because there might be some trash
           Read next stack
         */
        destroyStack(stack);
        scanf("%d", &size);
    }
    
    return 0;
}
