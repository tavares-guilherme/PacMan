#include "grafo.h"
#include <stdio.h>
#include <stdlib.h>
#include "fila.h"
#include "lista.h"

struct grafo_
{
    int vertices;
    int arestas;

    LISTA* *listas_de_adjascencia;
};

GRAFO* grafo_criar(int n) // Cria um grafo com n vértices
{
    GRAFO* g = (GRAFO*) malloc(sizeof(GRAFO));

    if(n >= 0 && g != NULL)
    {
        g->vertices = n;
        g->arestas = 0;

        g->listas_de_adjascencia = (LISTA**) malloc(sizeof(LISTA*) * g->vertices);

        for(int i = 0; i < g->vertices; i++) // Loop que cria as listas de adjascencia.
        {
            g->listas_de_adjascencia[i] = lista_criar();
            if(g-> listas_de_adjascencia[i] == NULL) return NULL;
        }
        return g;
    }
    
    return  NULL;
}

/*
 *   Função que insere uma aresta no grafo.
 *   Retorna 0 caso a inserção seja realizada sem problema e, caso contsrário, retorna 1;
 */
int grafo_inserir_aresta(GRAFO* g, int no1, int no2) // Insere uma dada aresta.
{
    if(g != NULL)
    {
        if(lista_inserir_fim(g->listas_de_adjascencia[no1], no2))
        {
            g->arestas++;
            return 1;
        }
        if(lista_inserir_fim(g->listas_de_adjascencia[no2], no1))
        {
            g->arestas++;
            return 1;
        }
        return 0;
    }

    return 1;
}

/*
 *   Função que realiza a remoção de um dado elemento no grafo.
 *   Retorna 0 caso a remoção tenha ocorrido sem problemas e, caso contrário, retorna 1;
 */
int grafo_remover_aresta(GRAFO* g, int no1, int no2) // Remove uma dada aresta.
{
    if(g != NULL)
    {
        if(lista_remover(g->listas_de_adjascencia[no1], no2)) return 1;
        if(lista_remover(g->listas_de_adjascencia[no2], no1)) return 1;

        return 0;
    }

    return 1;
}

/*
 *      Função que, nesta implementação, substitui as funções de inserção e remoção.
 *      Esta função insere os vértices e as dimensoes de forma que o gráfico representa um tabuleido de dimensão: dimensoes x dimensoes
 *      Cada vértice representa uma posição do tabuleiro, a as arestas representam quais posições estão adjascentes.
 */
int grafo_montaTabuleiro(GRAFO* tabuleiro, int dimensoes)
{
    if(tabuleiro != NULL)
    {
        // Insere as arestas "Horizontais"
        for(int i = 0; i < dimensoes; i++)
        {
            for(int j = 0; j < (dimensoes - 1); j++)
            {
                if(grafo_inserir_aresta(tabuleiro, dimensoes*i + j, dimensoes*i + j + 1)) return 0;
                
            }
        }

        // Insere as arestas Verticais
        for(int i = 0; i < dimensoes; i++)
        {
            for(int j = 0; j < (dimensoes - 1); j ++)
            {
                if(grafo_inserir_aresta(tabuleiro, i + j*dimensoes, i + (j+1)*dimensoes)) return 0;
            }
        }

        return 1;
    }
    return 0;
}

void grafo_imprimir(GRAFO* g) // Imprime a lista de adjascência.
{

    if(g != NULL)
    {    
        for(int i = 0; i < g->vertices; i++)
        {
            printf("%d:", i);
            lista_imprimir(g->listas_de_adjascencia[i]);
            printf("\n");
        }
    }

    return;
}

void grafo_deletar(GRAFO** g) // Apaga o grafo.
{
    if((*g) != NULL)
    {
        for(int i = 0; i < (*g)->vertices; i++) lista_apagar(&((*g) -> listas_de_adjascencia[i]));
        free((*g) -> listas_de_adjascencia);        
        free(*g);
        g = NULL;
    }
}

/*
 *      Função que, dada um grafo G e um vértice deste grafo, gera um vetor que contém as distâncias dos outros vértices
 *     ao vértice fornecido.
 * 
 *      O Algoritmo trata-se de uma Busca em Largura 
 */
int* grafo_wavefront(GRAFO* G, int posicaoFantasma)
{
    if(G != NULL && posicaoFantasma > 0 && posicaoFantasma < G->vertices)
    {
        FILA* f = fila_criar();
        int vertice;
        int verticeAdjascente;
        int* anterior;
        int* distancias;
        
        anterior   = (int*) malloc(sizeof(int) * G->vertices);
        distancias = (int*) malloc(sizeof(int) * G->vertices);

        // Inicializa o valor do Vetor "distancias":
        for(int i = 0; i < G->vertices; i++) distancias[i] = -2;
        distancias[posicaoFantasma] = -1;
        anterior  [posicaoFantasma] = posicaoFantasma;

        fila_inserir(f, posicaoFantasma);
            
        while(!fila_vazia(f))
        {
            vertice = fila_remover(f);
            
            verticeAdjascente = lista_primeiro_item(G->listas_de_adjascencia[vertice]);
            
            while(verticeAdjascente != ERRO)
            {
                if(distancias[verticeAdjascente] == -2)
                {
                    fila_inserir(f, verticeAdjascente);
                    anterior[verticeAdjascente] = vertice;
                    distancias[verticeAdjascente] = -1;
                }
                verticeAdjascente = lista_proximo(G->listas_de_adjascencia[vertice]);
            }

            distancias[vertice] = distancias[anterior[vertice]] + 1;
        }          

        fila_apagar(&f);
        return distancias;
    }   

    fprintf(stderr, "Erro ao realizar o algoritmo Wavefront\n");
    return NULL;
}

/*
 *          A função abaixo, dado um grafo G, uma posição desse grafo, e a marcação do grafo por um algoritmo Wavefront,
 *      atualiza a posição fornecida pelo usuário para uma posição que o deixará mais próximo do vértice a partir do qual
 *      o algoritmo Wavefront foi realizado. 
 */
int grafo_atualizaPacman(GRAFO* g, int posicaoPacman, int* distancias)
{
    if(g != NULL && posicaoPacman >= 0 && posicaoPacman < g->vertices)
    {
        int menor = lista_primeiro_item(g->listas_de_adjascencia[posicaoPacman]);
        int aux = menor;

        while(aux != ERRO)
        {
            if(distancias[aux] < distancias[menor]) menor = aux;
            aux = lista_proximo(g->listas_de_adjascencia[posicaoPacman]);
        }

        return(menor);
    }

    return -1;
}
