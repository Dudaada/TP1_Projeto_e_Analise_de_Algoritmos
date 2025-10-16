#include <stdio.h>
#include <stdlib.h>

#include "../include/rota.h"

RotaFinal* inicializaRotaFinal() {
    RotaFinal* rota = malloc(sizeof(RotaFinal));
    rota->primeiro = NULL;
    rota->ultimo = NULL;

    return rota;
}

Posicao* criaPosicao(int linha,int coluna, int durabilidade, int pRestantes){

    Posicao *situacao = malloc(sizeof(Posicao));
    (*situacao).linha=linha;
    (*situacao).coluna=coluna;
    (*situacao).durabilidade=durabilidade;
    (*situacao).pRestantes=pRestantes;
    (*situacao).prox=NULL;

    return situacao;
}

void registraPosicao(RotaFinal* rota, int linha, int coluna, int durabilidade, int pRestantes) {
    Posicao* nova = criaPosicao(linha, coluna, durabilidade, pRestantes);
    if (rota->primeiro == NULL) {
        rota->primeiro = nova;
        rota->ultimo = nova;
    } else {
        nova->prox = rota->primeiro;
        rota->primeiro = nova;
    }
}

void imprimeRota(RotaFinal* rota){ 

    Posicao* p = rota->primeiro;

    while(p!=NULL){
        printf("Linha: %d, Coluna: %d; D: %d, pecas restantes: %d\n", p->linha,p->coluna,p->durabilidade,p->pRestantes);
        p=p->prox;     
    }
    printf("\n");
}

void liberaRota(RotaFinal* rota) {
    Posicao* p = rota->primeiro;
    while (p != NULL) {
        Posicao* temp = p;  
        p = p->prox;
        free(temp);
    }
    free(rota);
}
