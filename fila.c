#include <stdio.h>
#include <stdlib.h>
#include "fila.h"

typedef struct no_ NO;

struct no_ {

    ITEM item;
    NO* proximo;
};


struct fila_ {
    
    NO* inicio;
    NO* fim;

    int tamanho;
};

FILA* fila_criar(void){

    FILA* fila;
    fila = (FILA*) malloc(sizeof(FILA));

    fila -> inicio = NULL;
    fila -> fim  = NULL;
    fila -> tamanho = 0;

    return(fila);
}   

boolean fila_vazia(FILA* fila){
    if(fila -> tamanho == 0) return TRUE;
    else return FALSE;
}

boolean fila_inserir(FILA* fila, ITEM item){
    
    NO* novo = (NO*) malloc(sizeof(NO));

    if(novo != NULL){
        
        novo -> item = item;

        if(fila -> fim == NULL)
        {   
            novo -> proximo = NULL;
            fila -> fim = novo;
            fila -> inicio = novo;
        }else
        {
            fila -> inicio -> proximo = novo;    
            fila  -> inicio = novo;    
        }
               
        (fila->tamanho)++;
        return(TRUE);
    }

    return(FALSE);
}

void fila_imprimir(FILA* fila)
{
    if(fila != NULL)
    {
        NO* aux = fila->fim;

        while(aux != NULL)
        {
            printf("%d\t", aux->item);
            aux = aux -> proximo;
        }
        printf("\n");
    }
}

ITEM fila_remover(FILA* fila){

    if(fila != NULL && !fila_vazia(fila)){
        NO* aux = (fila -> fim);
        ITEM i = aux -> item;

        fila -> fim = aux -> proximo;
    
        (fila -> tamanho)--;

        free(aux);
        aux = NULL;
        return(i);
    }
    return ERRO;
}

ITEM fila_inicio(FILA* fila){
    if(fila != NULL && !fila_vazia(fila)){
        return(fila -> inicio -> item);
    }
    return(-1);
}

void fila_apagar(FILA **fila){

    if(*fila != NULL)
    {    
        NO* aux;

        if(!fila_vazia(*fila)){
            aux = (*fila) -> inicio;
        }

        while(!fila_vazia(*fila)){

            aux = (*fila) -> inicio -> proximo;
            fila_remover((*fila));    
        }

        free(*fila);
        *fila = NULL;
    }
}