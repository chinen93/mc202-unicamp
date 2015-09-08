/* Nome: Pedro Hideaki Uiechi Chinen
 * RA: 175828
 * Laboratorio 03 - Sistema Único de Saúde */

#include "fila.h"
#include <stdio.h>
#include <stdlib.h>

void atendimento(List *list);
void emergencia(int num, List *list);

int main(){
    List *lista;
    char comando;
    int  numero, i;

    
    lista = createList();

    /*Le qual o numero de pacientes e cria a fila*/
    scanf("%d", &numero);
    for(i=0; i<numero; i++)
        insertFinalListInfo(i+1, lista);

    /* Mexe com a fila ate o comando 'F' ser pressionado  */
    do{
        scanf(" %c", &comando);
        switch(comando){
        case 'A':
            atendimento(lista);
            break;
        case 'E':
            /* Caso 'E' seja pressionado, um outro numero tem de ser especificado  */
            scanf("%d", &numero);
            emergencia(numero, lista);
            break;
        default:
            break;
        };

        /* printList((*lista));*/
    }while(comando != 'F');
    destroyList(lista);
    
    return 0;
}

/* Printa o primeiro da fila e coloca no final  */
void atendimento(List *lista){
    Node *n = NULL;
    n = removeBeginList(lista);
    if(n != NULL){
        printf("%d\n", n->info);
        insertFinalList(n, lista);
    }else{
        printf("erro atendimento\n");
    }
}

/* Procura o paciente num e o coloca no inicio da fila */
void emergencia(int num, List *lista){
    Node *n= NULL;
    n = removeInfo(num, lista);
    if(n != NULL){
        insertBeginList(n, lista);
    }else{
        printf("erro emergencia\n");
    }
}
