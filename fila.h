#ifndef FILA_H

    #define FILA_H
    #define TRUE 1
    #define FALSE 0
    #define boolean int
    #define ITEM int
    #define ERRO -3492391

    typedef struct fila_ FILA;

    //Aloca a fila na memoria
    FILA* fila_criar(void);
    
    boolean fila_vazia(FILA* fila);


    //Insere um elemento na fila
    boolean fila_inserir(FILA* fila, ITEM item);
    void fila_imprimir(FILA* fila);
    ITEM fila_remover(FILA* fila); //Remove e retorna o topo da fila
    ITEM fila_topo(FILA* fila);
    void fila_apagar(FILA **fila);
#endif