#include "bTree.h"

int BuscaChaveNo(ArvB *arv, int chave, int *posicao);
void InsereNovoValorEFilhoNo(ArvB *arvore, ArvB *aux, int valor, int pos);
int VerificaUnderflow(ArvB *arv);
int VerificaOverflow(ArvB *arv);
int ArvBRemoveRec(ArvB **arv, int chave, int *underflow);
int ArvBRemoveRec(ArvB **arv, int chave, int *underflow);

int TrataOverflow(ArvB **arvore, ArvB **aux);
void TrataUnderflow(ArvB **arv, int pos);
void TrocaChaveAnterior(ArvB *arv, int pos);
void RemoveChaveNo(ArvB *arv, int pos);

ArvB *ArvBCria(int ordem)
/* Cria uma arvore B com a ordem passada pelo parametro. Devolve NULL
   Caso a ordem seja maior do que o tamanho maximo especificado, ou 
   se deu algum pau de memoria
*/
{
  ArvB *temp;
  if((ordem>TAMMAX)||(ordem<2))
    return NULL;
  if ((temp = (ArvB *) calloc(1,sizeof(ArvB)))==NULL)
    return NULL;
  temp->ordem = ordem;
  temp->elems = 0;
  memset(temp->info, 0, sizeof(temp->info)); /* zera o vetor todo de uma vez*/
  memset(temp->filhos, 0, sizeof(temp->filhos));
  return(temp);
}

int ArvBDestroi(ArvB **arvore)
/* Destroi a Arvore B. O apontador arvore deve retornar Nulo.
   int retorna 1 se tudo deu certo, ou 0 se deu algum tipo de pau.
*/
{
  int i;
  if (*arvore == NULL)
    return 0;
  else
    for(i=0; i<(TAMMAX+1); i++)
      if ((*arvore)->filhos[i]!=NULL)
	ArvBDestroi(&((*arvore)->filhos[i]));
  free(*arvore);
  *arvore = NULL;
  return 1;
}

/* BuscaChaveNo recebe um no' da arvore B e procura a chave neste no';
Duas coisas podem acontecer: (1) a chave esta' neste no' (2) a chave nao
est'a neste no.  No primeiro caso, a funcao retorna 1 e posicao recebe o
indice da chave; no segundo caso, a funcao retorna 0 e posicao recebe o
indice do filho onde a chave se encontra */
 
int BuscaChaveNo(ArvB *arv, int chave, int *posicao)
{
  int i=0;
  while((arv->info[i]<chave)&&(i<arv->elems))
	i++;
  (*posicao) = i;
  if ((arv->info[i] == chave)&&(i<arv->elems))
      return 1;
  else
      return 0;
}

/* InsereNovoValorEFilhoNo: Coloca os novos membros no local correto */
void InsereNovoValorEFilhoNo(ArvB *arvore, ArvB *aux, int valor, int pos) {
  int j;
  for (j = arvore->elems; j > pos; j--) {
    arvore->info[j] = arvore->info[j-1];
    arvore->filhos[j+1] = arvore->filhos[j];
  }
  /* Afasta todo mundo acima da posicao pos-1 para info,
     e pos para filhos, uma casa para a direita */
  arvore->info[pos] = valor;
  arvore->filhos[pos+1] = aux;
  arvore->elems++;
}

/* VerificaOverflow: retorna 1 se o no' passado esta' em overflow,
e zero caso contrario */
 
int VerificaOverflow(ArvB *arv)
{
  return arv->elems > arv->ordem;
}

/* VerificaUnderflow: retorna 1 se o no' passado esta' em underflow,
e zero caso contrario */
 
int VerificaUnderflow(ArvB *arv)
{
  return(arv->elems<(arv->ordem/2));
}

int ArvBInsereRec(ArvB **arvore, ArvB **aux, int *valor, int *quebrou)
{
  int i=0, j=0;
  if (*arvore==NULL) {
      (*quebrou) = 1;
      (*aux) = NULL;
      return 1;
  } else {
    if(BuscaChaveNo(*arvore, *valor, &i)) {
      /* Elemento encontrado na arvore, ignora inserção */
      (*quebrou) = 0;
      return 0;
    } else {
      if (ArvBInsereRec(&((*arvore)->filhos[i]),aux,valor,quebrou)) {
	/* Insere recursivamente o elemento no nó apropriado */
	if (*quebrou) {
	  /* O no' filho foi quebrado, então precisamos inserir a chave 
	     do filho no lugar de i (retornada em *valor) e verificar 
	     se o nó atual (pai) deve ser quebrado também */
	  
	  InsereNovoValorEFilhoNo(*arvore, *aux, *valor, i);

	  if (!VerificaOverflow(*arvore)) {
	    (*quebrou) = 0;
	    /* Verifica se houve estouro de folha */
	  } else {
	    /* Arvore arrebentada.*/

	    (*valor) = TrataOverflow(arvore, aux);

	    (*quebrou) = 1;
	  }
	}
	return 1;
      }
      return 0;
    }
  }
}


int ArvBBusca(ArvB *arvore, int valor)
/* Busca o valor "Valor" na arvore "arvore". 
   A funcao deve retornar 0 se o valor nao existir na arvore ou se 
   ocorrer algum tipo de Pau. Caso o valor esteja na arvore, a funcao
   deve retornar o nivel no qual o valor se encontra (a raiz 
   possui nivel 1
*/
{
  int nivel = 1, i = 0;
  ArvB *aux;
  aux = arvore;
  if (aux == NULL)
    return 0;
  while(nivel) {
    while((aux->info[i]<valor)&&(i<aux->elems))
      i++;
    /*procura o primeiro elemento maior que o valor, ou a posicao depois
      da arvore*/
    if ((aux->info[i] == valor)&&(i<aux->elems))
      return(nivel);
    /*verifica se achou o elemento (fora da arvore nao vale*/
    else {
      if (aux->filhos[i] != NULL) {
	aux = aux->filhos[i];
	i = 0;
	nivel++;
      } else
	return 0;
      /* se nao achou o elemento neste nivel, tenta descer um nivel. 
	 se nao conseguir, retorna 0 que faiou.
      */
    }
  }
  return 0;
}


/* ArvBRemoveRec: recursiva; faz o trabalho necessario para a remocao mas
restringe-se a um nivel.  Recebe um no de arvore B e uma chave a remover;
Cuida de localizar a chave neste no, chamar-se recursivamente para cuidar
dos niveis inferiores, e arrumar a casa neste nive em caso de underflow de
filho; Retorna um booleanos: underflow, que indica se o no corrente ficou 
em underflow depois da arrumacao. Alem disso, a funcao retorna 1 se 
a chave existia na arvore, ou 0 se nao existia.  Obs: Caso a chave esteja 
neste nivel mas o nivel nao e' o ultimo (ou seja, a chave nao estava 
numa folha), troca a chave com a chave imediatamente anterior, que
necessariamente estara' numa folha, para poder prosseguir com o usual.
So' se remove chave em folha neste esquema.
*/
 
int ArvBRemoveRec(ArvB **arv, int chave, int *underflow) {
  int pos;
  /* Primeiro, procura onde esta a chave */
   if (BuscaChaveNo(*arv, chave, &pos)) {
    /* a chave esta neste nivel */
    if ((*arv)->filhos[pos]!=NULL) {   /* Nao estamos na folha */
      TrocaChaveAnterior(*arv, pos);   /* manda a chave para baixo */
      ArvBRemoveRec(&((*arv)->filhos[pos]), chave, underflow);
      if (*underflow) TrataUnderflow(arv, pos);
    } else {
      RemoveChaveNo(*arv, pos);
    }
    (*underflow) = VerificaUnderflow(*arv);
    return 1;
  } else { /* a chave nao esta neste nivel */
    if ((*arv)->filhos[pos]!=NULL) {
      if (ArvBRemoveRec(&((*arv)->filhos[pos]), chave, underflow)) {
	/* existe o no abaixo */
	if (*underflow) TrataUnderflow(arv, pos);
	(*underflow) = VerificaUnderflow(*arv);
	return 1;
      } else
	return 0;/* nao existe o no abaixo */
    } else {  /* estamos na raiz e a chave nao esta neste nivel, 
	         logo, ela nao existe */
      (*underflow) = 0;
      return 0;
    }
  }
}


int ArvBInsere(ArvB **arvore, int valor);
int ArvBRemove(ArvB **arvore, int valor);
void ArvBImprimePreOrdem(ArvB *arv, int nivel);
int TrataOverflow(ArvB **arvore, ArvB **aux);
void TrataUnderflow(ArvB **arv, int pos);
void TrocaChaveAnterior(ArvB *arv, int pos);
void TrocaChaveAnterior(ArvB *arv, int pos);
void RemoveChaveNo(ArvB *arv, int pos);



