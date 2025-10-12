#include <stdio.h>
#include <stdlib.h>
#include "../include/entrada.h"

int main() {
    char nomeArquivo[100];
    int opcao = 1;

    while (opcao != 0) {
        printf("\n====================================\n");
        printf("     EXPRESSO INTERESTELAR - PAA\n");
        printf("=====================================\n");
        printf("Nome do arquivo de entrada (ex: testes/mapa1.txt) ou digite '0' para sair: ");
        scanf("%s", nomeArquivo);

        if (nomeArquivo[0] == '0') {
            printf("\nEncerrando o programa...\n");
            break;
        }

        Mapa* m = lerArquivo(nomeArquivo);
        if (m == NULL) {
            printf("\n Erro: nao foi possivel ler o arquivo '%s'.\n", nomeArquivo);
            printf("Verifique o caminho e tente novamente.\n");
            continue; // volta para o início do loop
        }

        imprimirMapa(m);

        liberarMapa(m);

        printf("\nDeseja carregar outro arquivo?\n");
        printf("[1] Sim\n[0] Nao (sair)\n> ");
        scanf("%d", &opcao);
    }

    return 0;
}
