#ifndef LISTA_H
    
    #define LISTA_H
    #define TRUE 1
    #define FALSE 0
    #define boolean int
    #define ERRO -3492391

    typedef struct lista_ LISTA;

    LISTA*  lista_criar            (void);
    int     lista_inserir_fim      (LISTA* lista, int i);
    boolean lista_busca            (LISTA* lista, int i);
    int     lista_remover          (LISTA* lista, int no1);
    void    lista_imprimir         (LISTA* lista);
    int     lista_proximo          (LISTA* lista);
    int     lista_primeiro_item    (LISTA* lista);
    int     lista_tamanho          (LISTA* lista); // Função que retorna o número de elementos inseridos na lista.
    boolean lista_cheia            (LISTA* lista);

    void lista_apagar(LISTA** lista); // Remove a lista da memória Heap.
    
#endif
