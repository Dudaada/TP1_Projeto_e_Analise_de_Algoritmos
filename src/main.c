#include <stdio.h>
#include "../include/entrada.h"

int main() {
    char nomeArquivo[100];
    printf("Digite o nome do arquivo de entrada (ex: testes/mapa1.txt): ");
    scanf("%s", nomeArquivo);

    Mapa* m = lerArquivo(nomeArquivo);
    if (m == NULL) return 1;

    imprimirMapa(m);

    liberarMapa(m);
    return 0;
}

//Primeiro escreve 'make', dps 'make run' kkkkkk
