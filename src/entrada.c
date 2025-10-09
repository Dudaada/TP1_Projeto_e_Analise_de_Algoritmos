#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/entrada.h"

Mapa* lerArquivo(const char* nomeArquivo) {
    FILE* arquivo = fopen(nomeArquivo, "r");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo: %s\n", nomeArquivo);
        return NULL;
    }

    //aloca a estrutura principal
    Mapa* m = (Mapa*) malloc(sizeof(Mapa));
    if (!m) {
        printf("Erro de alocação de memória para Mapa.\n");
        fclose(arquivo);
        return NULL;
    }

    //lê os valores iniciais
    fscanf(arquivo, "%d %d %d", &m->D, &m->Dperda, &m->Againho);
    fscanf(arquivo, "%d %d", &m->altura, &m->largura);

    //aloca a matriz do mapa
    m->mapa = (char**) malloc(m->altura * sizeof(char*));
    for (int i = 0; i < m->altura; i++) {
        m->mapa[i] = (char*) malloc((m->largura + 1) * sizeof(char)); // +1 pro '\0'
    }

    //lê o mapa linha por linha
    for (int i = 0; i < m->altura; i++) {
        fscanf(arquivo, "%s", m->mapa[i]);
    }

    fclose(arquivo);

    //localiza a posição inicial 'X'
    m->linhaInicial = -1;
    m->colunaInicial = -1;

    for (int i = 0; i < m->altura; i++) {
        for (int j = 0; j < m->largura; j++) {
            if (m->mapa[i][j] == 'X') {
                m->linhaInicial = i;
                m->colunaInicial = j;
                break;
            }
        }
    }

    if (m->linhaInicial == -1) {
        printf("Aviso: posição inicial 'X' não encontrada no mapa.\n");
    }

    return m;
}

void liberarMapa(Mapa* m) {
    if (m == NULL) return;

    for (int i = 0; i < m->altura; i++) {
        free(m->mapa[i]);
    }
    free(m->mapa);
    free(m);
}
