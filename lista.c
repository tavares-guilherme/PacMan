#include "lista.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

typedef struct no_ NO;

struct no_ {

    int item;  // Armazena o valor do próximo vértice. 
    NO* proximo;
};

struct lista_ {

    NO* inicio;
    NO* fim;
    int tamanho;

    NO* posicaoAtual;
};

LISTA* lista_criar(void){
    LISTA* L;

    L = (LISTA*) malloc(sizeof(LISTA));

    if(L != NULL){
        L -> inicio = NULL;
        L -> fim = NULL;
        L -> tamanho = 0;
    } 

    return (L);

}

boolean lista_busca(LISTA* lista, int i){
    NO* aux;

    aux = lista -> inicio;

    while(aux != NULL){
        if(aux -> item == i){
            return TRUE;
        }
        aux = aux -> proximo;
    }

    return FALSE;
}

// Retorna 0, se a inserção foi realizada corretamentem caso contrario, retorna 1
// Antes da inserção, a lista é percorrida para nao ocorrer a inserção de um mesmo item.
int lista_inserir_fim(LISTA* lista, int i){

    if(lista != NULL)
    {
        int verif = 0;
        NO* new = (NO*) malloc(sizeof(NO));

        if(lista->posicaoAtual == lista -> inicio) verif = 0;
        else verif = 1;

        if(new == NULL) return 1;

        new -> item = i;
        new -> proximo = NULL;

        if(lista -> inicio == NULL){
            lista -> inicio = new;
        }else{
            lista -> fim -> proximo = new;
        }
        lista -> fim = new;
        (lista -> tamanho)++;

        if(verif) lista->posicaoAtual = lista->inicio;
        return 0;
    }

    return 1;
}

void no_remover(NO** n)
{
    (*n) -> proximo = NULL;
    free(*n);
    n = NULL;
}

// Função que realiza uma busca na Lista, se o elemento for encontrado, ele será removido.
// Retorna 0 caso a remoção seja feita corretamente e, caso contrário, retorna 1;
int lista_remover(LISTA* lista, int no1)
{
    if(lista != NULL)
    {
        NO* atual;
        NO* anterior;

        atual = lista -> inicio;

        // Caso o item a ser removido estar no início da lista:
        if(atual -> item == no1)
        {
            lista -> inicio = atual -> proximo;
            no_remover(&atual);
            return 0;
        }

        while(atual != NULL)
        {
            if(atual -> item == no1)
            {
                if(atual == lista->fim)
                { 
                    anterior -> proximo = NULL;
                    lista->fim = anterior;
                    no_remover(&atual);
                }else
                {
                    anterior -> proximo = atual -> proximo;
                    no_remover(&atual);
                }
                return 0;
            }
            anterior = atual;
            atual = atual -> proximo;
        }
    }
    return 1;
}

void lista_imprimir(LISTA* lista){

    NO* aux;
    aux = lista -> inicio;

    while(aux != NULL){
        printf(" %d", aux -> item);
        aux = aux -> proximo;
    }

}

/* 
 *      Função que altera o atributo "PosicaoAtual" para a proxima posição, e retorna o item do nó alcançado.
 *  Caso o ponteiro chegue ao final da lista, ou seja, apontando para "NULL", a função retorna o valor de erro.
 *  mas mantém o ponteiro apontando para NULL.
 *  Caso o ponteiro comece apontando para NULL, apenas a saída de erro é retornada. * 
 */
int lista_proximo(LISTA* lista)
{
    if(lista != NULL && lista->posicaoAtual != NULL)
    {
        lista->posicaoAtual = lista->posicaoAtual ->proximo;
        if(lista->posicaoAtual == NULL) return ERRO;
        else return lista->posicaoAtual->item;
    }

    return ERRO;
}

/*
 *      Função que "seta" o atributo "PosicaoAtual" para o início da lista e retorna seu item.
 *      Caso o primeiro nó seja NULL, é retornado o valor de erro.
 */
int lista_primeiro_item(LISTA* lista)
{
    if(lista != NULL && lista->inicio != NULL)
    {
        lista->posicaoAtual = lista->inicio;
        return lista->posicaoAtual->item;
    }

    return ERRO;
}
int lista_tamanho(LISTA* lista)
{
    if(lista != NULL) return lista -> tamanho;
    else return 0;
}

boolean lista_cheia(LISTA* lista){

    if(lista -> tamanho == 100) return FALSE;
    else return TRUE;

}

void lista_apagar(LISTA** lista)
{

    if((*lista) != NULL)
    {
        NO* aux = (*lista) -> inicio;
        NO* proximo;

        while(aux != NULL)
        {
            proximo = aux -> proximo;
            no_remover(&aux);
            aux = proximo;
        }
        free(*lista);
        lista = NULL;
    }
}
