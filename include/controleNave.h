#ifndef CONTROLE_NAVE_H
#define CONTROLE_NAVE_H

#include "entrada.h"
#include "Pecas.h"
#include "rota.h"

int verificaMovimento(char direcao, Mapa* mapa,int x,int y,int* novoX,int* novoY, int** visitado);
int movimentarNave(Mapa* mapa, int** visitado, int** solucao,int x,int y,RotaFinal* rota);
void exibeCaminho(Mapa* mapa, int** solucao);
int encontraCaminho(Mapa* mapa);

#endif
