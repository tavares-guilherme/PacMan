#ifndef GRAFO_H

    #define GRAFO_H
    typedef struct grafo_ GRAFO;

    GRAFO* grafo_criar          (int n); // Cria um grafo com n vértices
    int    grafo_montaTabuleiro (GRAFO* g, int dimensoes); // Insere os valores do grafo para montar um tabuleiro.
    void   grafo_imprimir       (GRAFO* g);  // Imprime a lista de adjascência.
    void   grafo_deletar        (GRAFO** g); // Apaga o grafo.
    int*   grafo_wavefront      (GRAFO* G, int posicaoFantasma); 
    int    grafo_atualizaPacman (GRAFO* G, int posicaoPacman, int* distancias);

#endif