#ifndef ENTRADA_H
#define ENTRADA_H

// Códigos ANSI de cor
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"
#define GRAY    "\033[90m"

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
void imprimirMapa(Mapa* m);

char gerarCaractereCaminho(int dificuldade);
Mapa gerarMapaAutomaticamente();

#endif
