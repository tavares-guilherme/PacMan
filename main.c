#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"
#include <time.h>
#include <string.h>

# define DIREITA  "direita\0"
# define ESQUERDA "esquerda\0"
# define CIMA     "cima\0"
# define BAIXO    "baixo\0"
# define NENHUM   "nenhum\0"
# define DEBUG 0

void imprimeTabuleiro(GRAFO* tabuleiro, int dimensoes, int posicaoFantasma, int posicaoPacman, int posicaoCereja)
{
    for(int i = 0; i <= (dimensoes-1)*dimensoes; i += dimensoes)
    {
        for(int j = 0; j < dimensoes; j++)
        {
            if((i+j) == posicaoPacman) printf("ᗤ  ");
            else
            {
                if((i+j) == posicaoFantasma) printf("ᗣ  ");
                else
                {
                    if((i+j) == posicaoCereja) printf("🍒 ");
                    else printf("•  ");
                }
            }            
        }
        printf("\n");
    }
}

int main()
{   
    /*
     * Variável que armazena as dimensões do Tabuleiro:
     */
    int dimensoes;

    /*
     * Vetor que armazena a distância de cada vértice ao vértice em que o Fantasma se encontra.
     */
    int* distancias;

    GRAFO* tabuleiro;
    char comandoUsuario[9];

    int posicaoFantasma;
    int posicaoPacman;
    int posicaoCereja;
    
    time_t seed;
    srand((unsigned) time(&seed));

    printf("Insira as dimensões do Tabuleiro (Deve ser inserido apenas um valor inteiro): ");
    scanf ("%d", &dimensoes);

    if(dimensoes > 1) 
    {   

        distancias = (int*) malloc(sizeof(dimensoes * dimensoes));

        // Gera aleatoriamente as posições relevantes do tabuleiro.
        posicaoFantasma = rand() % (dimensoes * dimensoes);
        do{
            posicaoPacman   = rand() % (dimensoes * dimensoes);
        }while(posicaoPacman == posicaoFantasma);
        do{
            posicaoCereja   = rand() % (dimensoes * dimensoes);
        } while(posicaoCereja == posicaoFantasma && posicaoCereja != posicaoPacman);

        tabuleiro = grafo_criar(dimensoes * dimensoes);
        if(!grafo_montaTabuleiro(tabuleiro, dimensoes)) return 1;
    
        if(!DEBUG) printf("PosiFantasma: %d\nPosiPacman: %d\n", posicaoFantasma, posicaoPacman);

        distancias = grafo_wavefront(tabuleiro, posicaoFantasma);

        if(DEBUG)
        {
            printf("*** Resultado Wavefront ***\n\n");
            for(int i = 0; i <= dimensoes*(dimensoes-1); i+= dimensoes)
            {
                for(int j = 0 ; j < dimensoes; j++) printf("%d\t", distancias[i + j]);
                printf("\n");
            }
            printf("\n*** Fim WaveFront ***\n");
        }

        imprimeTabuleiro(tabuleiro, dimensoes, posicaoFantasma, posicaoPacman, posicaoCereja);
        printf("\n");int verif = 0;
        while(posicaoFantasma != posicaoPacman && posicaoCereja != posicaoFantasma)
        {   
            // A condicional abaixo recebe e processa a entrada do Usuário.
            while(verif == 0)
            {
                printf("\nEntradas Aceitadas: (cima/direita/esquerda/baixo/nenhum)\nInsira a posição para a qual deseja movimentar o fantasma: ");
                scanf("%s", comandoUsuario);

                if(strcmp(CIMA, comandoUsuario) == 0)
                {
                    if(posicaoFantasma >= dimensoes){
                        verif = 1;
                        posicaoFantasma -= dimensoes;
                        distancias = grafo_wavefront(tabuleiro, posicaoFantasma);
                    }else printf("\n*** IMPOSSIVEL REALIZAR ESTE MOVIMENTO! ***\n");
                }
                if(strcmp(DIREITA, comandoUsuario) == 0)
                {
                    if(posicaoFantasma%dimensoes < (dimensoes - 1))
                    {
                        verif = 1;
                        posicaoFantasma++;
                        distancias = grafo_wavefront(tabuleiro, posicaoFantasma);
                    }else printf("\n*** IMPOSSIVEL REALIZAR ESTE MOVIMENTO! ***\n");
                }
                if(strcmp(ESQUERDA, comandoUsuario) == 0)
                {
                    if(posicaoFantasma%dimensoes > 0)
                    {
                        verif = 1;
                        posicaoFantasma--;
                        distancias = grafo_wavefront(tabuleiro, posicaoFantasma);
                    }else printf("\n*** IMPOSSIVEL REALIZAR ESTE MOVIMENTO! ***\n");
                }
                if(strcmp(BAIXO, comandoUsuario) == 0)
                {
                    if((posicaoFantasma+dimensoes) < dimensoes*dimensoes)
                    {
                        verif = 1;
                        posicaoFantasma += dimensoes;
                        distancias = grafo_wavefront(tabuleiro, posicaoFantasma);
                    }else printf("\n*** IMPOSSIVEL REALIZAR ESTE MOVIMENTO! ***\n");
                }
                if(strcmp(NENHUM, comandoUsuario) == 0) verif = 1;

                if(verif == 0) printf("\n**** ENTRADA INVÁLIDA! ***\n");
            }
            verif = 0;printf("\n");

            // Imprime a Jogada do usuário: 
            printf("\nSeu movimento: \n");
            imprimeTabuleiro(tabuleiro, dimensoes, posicaoFantasma, posicaoPacman, posicaoCereja);
            printf("\n");

            if(posicaoCereja == posicaoFantasma)
            {
                printf("\n*** PARABÉNS, VOCÊ VENCEU! ***\n");
                break;
            }
            if(posicaoPacman == posicaoFantasma)
            {
                printf("\n*** VOCÊ PERDEU, TENTE OUTRA VEZ ***\n");
                break;
            }

            // Calcula e Imprime a Jogada do Computador: 
            printf("\nMovimento do Computador: \n");
            posicaoPacman = grafo_atualizaPacman(tabuleiro, posicaoPacman, distancias);
            imprimeTabuleiro(tabuleiro, dimensoes, posicaoFantasma, posicaoPacman, posicaoCereja);
            printf("\n");
            if(posicaoPacman == posicaoFantasma)
            {
                printf("\n*** VOCÊ PERDEU, TENTE OUTRA VEZ ***\n");
                break;
            }
        }

    }    
    else
    {
        fprintf(stderr, "Valor inválido, deve ser inserido um valor maior ou igual a 2.\n");
        return 1;
    }
    
    grafo_deletar(&tabuleiro);
    free(distancias);
    return 0;
}