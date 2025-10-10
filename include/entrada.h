#ifndef ENTRADA_H
#define ENTRADA_H

typedef struct {
    int D; //durabilidade inicial
    int Dperda; //quanto perde por movimento
    int Againho; //quanto ganha ao pegar uma peça
    int altura; //linhas
    int largura; //colunas
    char **mapa; //matriz dinâmica com o mapa
    int linhaInicial; //posição do 'X'
    int colunaInicial; //posição do 'X'
    int qtdPecas;//guarda quantas pecas ja foram pegas
} Mapa;

Mapa* lerArquivo(const char* nomeArquivo);
void liberarMapa(Mapa* m);

#endif
