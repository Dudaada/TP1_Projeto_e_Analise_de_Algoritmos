#ifndef ROTA_H
#define ROTA_H

typedef struct Posicao{

    int linha;
    int coluna;
    int durabilidade;
    int pRestantes;
    struct Posicao* prox;

}Posicao;

typedef struct RotaFinal{

    Posicao* primeiro;
    Posicao* ultimo;

}RotaFinal;

RotaFinal* inicializaRotaFinal();
Posicao* criaPosicao(int linha,int coluna, int durabilidade, int pRestantes);
void registraPosicao(RotaFinal* rota, int linha, int coluna, int durabilidade, int pRestantes);
void imprimeRota(RotaFinal* rota);
void liberaRota(RotaFinal* rota);

#endif