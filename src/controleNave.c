#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "../include/entrada.h"

int verificaMovimento(char direcao, Mapa* mapa,int x,int y,int* novoX,int* novoY, int** visitado){

    *novoX=x;
    *novoY=y;

    switch (direcao){
        case 'e':
            (*novoY)--;
            break;
        case 'd':
            (*novoY)++;
            break;

        case 'c':
            (*novoX)--;
            break;
        case 'b':
            (*novoX)++;
            break;
    }

    if (*novoX < 0 || *novoX >= mapa->altura || *novoY < 0 || *novoY >= mapa->largura || visitado[(*novoX)][(*novoY)])
        return 0;

    if (mapa->mapa[*novoX][*novoY] != '.')
        return 1;

    return 0;
}

int movimentarNave(Mapa* mapa, int** visitado, int** solucao,int x, int y, int xFim, int yFim) {

    printf("Linha: %d, Coluna: %d; D: %d, pecas restantes: %d\n",x,y,mapa->D,4-mapa->qtdPecas);

    if (x == xFim && y == yFim) {
        solucao[x][y] = 1;
        return 1;
    }

    if (x >= 0 && x < mapa->altura && y >= 0 && y < mapa->largura && mapa->mapa[x][y] != '.' && !visitado[x][y]) {

        visitado[x][y] = 1;
        solucao[x][y] = 1;

        char direcoes[] = {'e','d','c','b'};
        int novoX,novoY;

        for (int i = 0; i < 4; i++) {

            if (verificaMovimento(direcoes[i],mapa,x,y,&novoX,&novoY,visitado)){
                if (movimentarNave(mapa, visitado, solucao, novoX, novoY, xFim, yFim)){
                    return 1;
                }
            }
        }

        solucao[x][y] = 0;
        visitado[x][y] = 0;
    }
    printf("rota invalida\n");
    return 0;
}

void exibeCaminho(Mapa* mapa, int** solucao) {
    printf("\nRota:\n");
    for (int i = 0; i < mapa->altura; i++) {
        for (int j = 0; j < mapa->largura; j++) {
            if (solucao[i][j] == 1)
                printf("@ ");
            else
                printf("%c ", mapa->mapa[i][j]);
        }
        printf("\n");
    }
}

int encontraCaminho(Mapa* mapa) {
    int N=mapa->altura;
    int M=mapa->largura;

    int **visitado = malloc(N*sizeof(int*));
    int **solucao = malloc(N*sizeof(int*));

    for (int i = 0; i < N; i++) {
        visitado[i] = calloc(M, sizeof(int));
        solucao[i] = calloc(M, sizeof(int));
    }

    if (movimentarNave(mapa, visitado, solucao, mapa->linhaInicial, mapa->colunaInicial, mapa->linhaFinal, mapa->colunaFinal)) {
        exibeCaminho(mapa, solucao);
        return 1;
    } else {
        printf("nenhum caminho encontrado");
        return 0;
    }

    for (int i = 0; i < N; i++) {
        free(visitado[i]);
        free(solucao[i]);
    }
    free(visitado);
    free(solucao);
}
