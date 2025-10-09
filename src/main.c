#include <stdio.h>
#include "../include/entrada.h"

int main() {
    char nomeArquivo[100];
    printf("Digite o nome do arquivo de entrada (ex: testes/mapa1.txt): ");
    scanf("%s", nomeArquivo);

    Mapa* m = lerArquivo(nomeArquivo);
    if (m == NULL) return 1;

    printf("\nMapa lido com sucesso!\n");
    printf("D = %d, D' = %d, A = %d\n", m->D, m->Dperda, m->Againho);
    printf("Altura = %d, Largura = %d\n", m->altura, m->largura);
    printf("Posicao inicial (X): linha %d, coluna %d\n\n", m->linhaInicial, m->colunaInicial);

    // Mostra o mapa
    for (int i = 0; i < m->altura; i++) {
        printf("%s\n", m->mapa[i]);
    }

    liberarMapa(m);
    return 0;
}

//Primeiro escreve 'make', dps 'make run' kkkkkk
