#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "../include/entrada.h"
#include "../include/Pecas.h"
#include "../include/controleNave.h"
#include "../include/rota.h"

extern int g_modo_exibicao;
extern int g_modo_analise;
extern long int g_chamadas_recursivas;
extern int g_profundidade_maxima;
extern int g_profundidade_atual;


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

void defineDirecoes(char c, char *vetor, int* possibilidades) {

    char encruzilhada[] = {'e', 'd', 'c', 'b', '\0'};
    char horizontal[]   = {'e', 'd', '\0'};
    char vertical[]     = {'c', 'b', '\0'};

    switch (c) {
        case '-':
            strcpy(vetor, horizontal);
            (*possibilidades)=2;
            break;
        case '|':
            strcpy(vetor, vertical);
            (*possibilidades)=2;
            break;
        default:
            strcpy(vetor, encruzilhada);
            (*possibilidades)=4;
            break;
    }
}


int movimentarNave(Mapa* mapa, int** visitado, int** solucao, int x, int y,RotaFinal* rota) {

    //logica do modo analise
    if (g_modo_analise == 1) {
        g_chamadas_recursivas++; // Contabiliza a chamada
        g_profundidade_atual++; // Aumenta um nível de profundidade
        if (g_profundidade_atual > g_profundidade_maxima) {
            g_profundidade_maxima = g_profundidade_atual; // Atualiza o máximo
        }
    }

    bool pecaColetada = false;
    bool danoMeteoro = false;
    int pecasRoubadas = 0;

    char evento = mapa->mapa[x][y];

    switch (evento) {
    case 'P':
        ConcertarNave(mapa);
        pecaColetada = true;
        mapa->mapa[x][y] = '+';
        break;
    case '#':
        UmMeteoroAcertou(mapa);
        danoMeteoro = true;
        break;
    case '&':
        pecasRoubadas = RouboExtraterrestre(mapa);
        break;
    }

    int dAtual = mapa->D;
    int pRestanteAtual = 4 - mapa->qtdPecas;

    if (g_modo_exibicao == 1) {
        printf("Linha: %d, Coluna: %d; D: %d, pecas restantes: %d\n", x, y, mapa->D, 4 - mapa->qtdPecas);
    }

    if (x == mapa->linhaFinal && y == mapa->colunaFinal) {
        solucao[x][y] = 1;
        registraPosicao(rota,x,y,mapa->D,4-mapa->qtdPecas);
        if (g_modo_analise == 1) g_profundidade_atual--; // Diminui um nível ao sair
        return 1;
    }

    if (mapa->D <= 0 && mapa->qtdPecas < 4) {
        // Pula para o bloco de reversão no final da função
    } else {
        visitado[x][y] = 1;
        solucao[x][y] = 1;

        char direcoes[5];
        int possibilidades=0;
        int novoX, novoY;

        defineDirecoes(mapa->mapa[x][y], direcoes, &possibilidades);

        for (int i = 0; i < possibilidades; i++) {

            if (verificaMovimento(direcoes[i], mapa, x, y, &novoX, &novoY, visitado)) {
                AndarnoMapa(mapa);

                if (movimentarNave(mapa, visitado, solucao, novoX, novoY,rota)) {
                    if (g_modo_analise == 1) g_profundidade_atual--; // Diminui um nível ao sair
                    registraPosicao(rota,x,y,dAtual,pRestanteAtual);
                    return 1;
                }

                if (mapa->qtdPecas < 4) {
                    mapa->D += mapa->Dperda;
                }
            }
        }
    }

    if (pecaColetada) {
        mapa->qtdPecas--;
        mapa->D -= mapa->Againho;
        mapa->mapa[x][y] = 'P';
    }
    if (danoMeteoro) {
        mapa->D += mapa->Dperda;
    }
    if (pecasRoubadas > 0) {
        mapa->qtdPecas += pecasRoubadas;
    }

    if (g_modo_exibicao == 1) {
        printf("...backtracking em (%d,%d)\n", x, y);
    }

    solucao[x][y] = 0;
    visitado[x][y] = 0;

    if (g_modo_analise == 1) g_profundidade_atual--; // Diminui um nível ao sair

    return 0;
}

void exibeCaminho(Mapa* mapa, int** solucao) {  //mostra a rota encontrada no mapa
    printf("Rota:\n");
    for (int i = 0; i < mapa->altura; i++) {
        for (int j = 0; j < mapa->largura; j++) {
            if (solucao[i][j] == 1)
                printf(RED "%c " RESET, mapa->mapa[i][j]);
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

    RotaFinal* rota = inicializaRotaFinal();

    int rotaEncontrada = movimentarNave(mapa, visitado, solucao, mapa->linhaInicial, mapa->colunaInicial, rota); //chamada do backtracking

    if (g_modo_exibicao == 2) {
        if (rotaEncontrada){
            imprimeRota(rota);
            exibeCaminho(mapa, solucao); 
        }else{
            printf("Nao foi possivel encontrar uma rota\n");
        }
    }

    for (int i = 0; i < N; i++) {
        free(visitado[i]);
        free(solucao[i]);
    }
    free(visitado);
    free(solucao);
    liberaRota(rota);

    return rotaEncontrada;
}
