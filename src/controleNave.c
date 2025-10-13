#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "../include/entrada.h"

int verificaMovimento(char direcao, Mapa* mapa,int x,int y,int* novoX,int* novoY, int** visitado){

    *novoX=x;
    *novoY=y;

    switch (direcao){ //calcula a nova posicao que vai ocupar na matriz de acordo com a direcao
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

    if (*novoX < 0 || *novoX >= mapa->altura || *novoY < 0 || *novoY >= mapa->largura) 
        return 0; //caiu fora das dimensões da matriz

    if (visitado[(*novoX)][(*novoY)]){
        return 0; //posição já visitada anteriormente (já foi verificada recursivamente)
    }

    if (mapa->mapa[*novoX][*novoY] == '.')
        return 0;  //encontrou uma parede

    return 1;
}

int movimentarNave(Mapa* mapa, int** visitado, int** solucao,int x, int y) {

    printf("Linha: %d, Coluna: %d; D: %d, pecas restantes: %d\n",x,y,mapa->D,4-mapa->qtdPecas);

    if (x == mapa->linhaFinal && y == mapa->colunaFinal) { //caso base, chegou ao destino
        solucao[x][y] = 1;
        return 1;
    }

    visitado[x][y] = 1;
    solucao[x][y] = 1;

    char direcoes[] = {'e','d','c','b'};
    int novoX,novoY;

    for (int i = 0; i < 4; i++) { //tenta movimentar a nave nas quatro direcoes
        if (verificaMovimento(direcoes[i],mapa,x,y,&novoX,&novoY,visitado)){ //verifica se é possível andar para a direção i
            if (movimentarNave(mapa, visitado, solucao, novoX, novoY)){ 
                return 1; //se a partir daquela direcao foi possível chegar numa rota, encerra a recursão
            }
        }
    }
    // caso contrario, retorna para as posições anteriores, que irão tentar outras direções
    printf("backtracking em (%d,%d)\n",x,y); 
    solucao[x][y] = 0;
    visitado[x][y] = 0; //desmarca as visitas para que seja possível testar a posição posteriormente vindo de outras rotas 

    return 0;
}

void exibeCaminho(Mapa* mapa, int** solucao) {  //mostra a rota encontrada no mapa
    printf("Rota:\n");
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
    } // alocação de matrizes auxiliares

    int rotaEncontrada = movimentarNave(mapa, visitado, solucao, mapa->linhaInicial, mapa->colunaInicial); //chamada do backtracking
    if (rotaEncontrada) {
        exibeCaminho(mapa, solucao);

    } else {
        printf("nenhum caminho encontrado");
    }

    for (int i = 0; i < N; i++) {
        free(visitado[i]);
        free(solucao[i]);
    }
    free(visitado);
    free(solucao);

    return rotaEncontrada;
}
