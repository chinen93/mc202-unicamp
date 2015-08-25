/* Nome: Pedro Hideaki Uiechi Chinen
* RA: 175828
* Laboratorio 01 - O problema do acesso à lista */

#include <stdio.h>
#include <stdlib.h>

/* STRUCS, DEFINIÇÕES E CABEÇALHOS DAS SUAS FUNÇÕES DA TAD */
typedef struct _No {
    int elem;
    struct  _No *prox;
} No;

int MTFadicionar(int num);
int MTFremover(int num);
int MTFprocurar(int num);
int TRadicionar(int num);
int TRremover(int num);
int TRprocurar(int num);

No*  criarNo(int num);
void destruirNo(No *no);
void printNo(No* p);
void listarLista(No* inicio);
void duplicarLista(No *inicio, No **inicioNovo);
void insereNoInicioLista(No *novo, No **inicio);
void insereNoFinalLista(No *novo, No *pos);
char procurarElemento(int elemProc, No *lista, No **antNoProc, No **noProc);
char procurarFinalLista(No *pos, No *lista);
char inserirNoAntesElemento(int elem, No *novo, No **lista);
char removeNoInicioLista(No **lista, No **retorno);
char removeNoFinalLista(No **lista, No **retorno);
char removeNo(int elem, No **lista, No **retorno);
void limpaLista(No *inicio);


/* SEU PROGRAMA - MAIN */
int main() {
    No *p = NULL, *inicio = NULL, *inicioDuplicado = NULL;
    No *retorno = NULL;

    
    p = criarNo(10);
    printNo(p);
    insereNoInicioLista(p, &inicio);
    p = criarNo(15);
    printNo(p);
    insereNoInicioLista(p, &inicio);
    p = criarNo(20);
    printNo(p);
    insereNoFinalLista(p, inicio);
    p = criarNo(50);
    printNo(p);
    insereNoFinalLista(p, inicio);
    
    p = criarNo(90);
    printNo(p);
    if(inserirNoAntesElemento(20, p, &inicio)){
        printf("Inseriu\n");
    }else{
        printf("Nao encontrou elemento\n");
    }

    duplicarLista(inicio, &inicioDuplicado);
    listarLista(inicio);

    if(removeNoInicioLista(&inicio, &retorno)){
        printf("Elemento removido  -> ");
        printNo(retorno);
    }else{
        printf("Nao encontrou elemento\n");
    }

    if(removeNoFinalLista(&inicio, &retorno)){
        printf("Elemento removido  -> ");
        printNo(retorno);
    }else{
        printf("Nao encontrou elemento\n");
    }

    if(removeNo(90, &inicio, &retorno)){
        printf("Elemento removido  -> ");
        printNo(retorno);
    }else{
        printf("Nao encontrou elemento\n");
    }

    printf("--------Lista 1---------------\n");
    listarLista(inicio);
    printf("--------Lista Duplicada ------\n");
    listarLista(inicioDuplicado);

    limpaLista(inicioDuplicado);
    limpaLista(inicio);
    return 0;
}

/* IMPLEMENTAÇÃO DAS FUNÇÕES DE SUA TAD */
int MTFadicionar(int num);
int MTFremover(int num);
int MTFprocurar(int num);
int TRadicionar(int num);
int TRremover(int num);
int TRprocurar(int num);

/* implementação de outras funções */
No* criarNo(int num){
    No* p;
    /* Cria um novo nó e aloca um pedaco de memoria para ele  */
    p = (No*) malloc(sizeof(No));
    (*p).elem = num;
    (*p).prox = NULL;
    return p;
}

void destruirNo(No *no){
    (*no).prox = NULL;
    free(no);
}

void listarLista(No* inicio){
    printf("{\n");
    while(inicio != NULL){
        printNo(inicio);
        inicio = (*inicio).prox;
    }
    printf("}\n");
}

void duplicarLista(No *inicio, No **inicioNovo){
    No *aux;
    if(inicio != NULL){
        /* Dando erro  */
        printf("--------------------------------------------------------------\n");
        while((*inicio).prox != NULL){
            aux = criarNo((*inicio).elem);
            printNo(aux);
            insereNoFinalLista(aux, (*inicioNovo));
            listarLista((*inicioNovo));
            inicio = (*inicio).prox;
        }
        printf("--------------------------------------------------------------\n");
    }        
}

void printNo(No* p){
    if(p != NULL)
        printf("[%p/%d/%p]", (void *)p, (*p).elem, (void *)(*p).prox);
    else
        printf("[nil]");
    printf("\n");
}


void insereNoInicioLista(No *novo, No **inicio){
    /*Caso a lista esteja vazia*/
    if((*inicio) == NULL){
        *inicio = novo;
    }else{
        /*Coloca no primeira posicao da lista*/
        (*novo).prox = (*inicio);
        (*inicio) = novo;
    }
}

void insereNoFinalLista(No *novo, No *pos){
    /*Caso a lista eseja vazia*/
    if(pos == NULL){
        insereNoInicioLista(novo, &pos);
    }else{
        /* Percorre a lista ate o ultimo No*/
        while((*pos).prox != NULL)
            pos = (*pos).prox;

        (*pos).prox = novo;
    }
}

char procurarElemento(int elemProc, No *lista,
                      No **antNoProc, No **noProc){
    *noProc    = lista;
    *antNoProc = NULL;

    /* Lista vazia  */
    if((*noProc) == NULL){
        return(0);
    }
    
    while(((**noProc).prox != NULL) && (**noProc).elem != elemProc){
        (*antNoProc) = (*noProc);
        (*noProc) = (**noProc).prox;
    }

    if((**noProc).elem == elemProc){
        /*Achou o elemento e os ponteiros ja estao certos, para ele e o anterior*/
        return(1);
    }
    /*Nao achou o elemento*/
    return(0);
}

char procurarFinalLista(No *pos, No *lista){
    pos = lista;
    /* Lista vazia nao tem final  */
    if(pos == NULL){
        return(0);
    }
    
    /* percorre a lista  */
    while((*pos).prox != NULL){
        pos = (*pos).prox;
    }
    return(1);
}

char inserirNoAntesElemento(int elem, No *novo, No **lista){
    No *ant = NULL, *pos = NULL;
    if(procurarElemento(elem, (*lista), &ant, &pos)){
        (*novo).prox = pos;
        (*ant).prox  = novo;
        return(1);
    }
    
    return(0);
}

char removeNoInicioLista(No **lista, No **retorno){
    (*retorno) = NULL;

    /* Lista vazia */
    if(lista == NULL){
        return(0);
    }

    /* Separar No da lista retirando */
    (*retorno) = (*lista); 
    (*lista)   = (**lista).prox;
    (**retorno).prox = NULL;
    
    return(1);
}

char removeNoFinalLista(No **lista, No **retorno){
    No *ant = NULL, *pos = (*lista);
    (*retorno) = NULL;
    
    /* Lista vazia  */
    if((*lista) == NULL){
        return(0);
    }
    
    /* Percorrer lista ate o final  */
    while((*pos).prox != NULL){
        ant   = pos;
        pos = (*pos).prox;
    }

    /* O retorno pega o end do ultimo No
       o proximo do retorno eh NULL (tirar ligacao com a lista)
       Poe NULL no proximo do penultimo No
     */
    (*retorno) = pos;
    (**retorno).prox = NULL;
    (*ant).prox = NULL;
    
    return(1);
}
    
char removeNo(int elem, No **lista, No **retorno){
    No *ant; No *pos;
    (*retorno) = NULL;
    
    if(procurarElemento(elem, (*lista), &ant, &pos)){
        /* Elemento no inicio da lista */
        if(ant == NULL){
            removeNoInicioLista(lista, retorno);
        }else{
            /* Elemento em qualquer outro lugar */
            (*ant).prox = (*pos).prox;
            (*retorno) = pos;
            (**retorno).prox = NULL;
        }
        return(1);
    }
    return(0);
}

void limpaLista(No *inicio){
    No *aux = inicio;
    /* Percorre a lista liberando todos as alocacoes de memoria*/
    while(aux != NULL){
        aux = (*inicio).prox;
        free(inicio);
        inicio = aux;
    }
}
