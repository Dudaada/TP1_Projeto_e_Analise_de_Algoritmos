#include <stdio.h>
#include <stdlib.h>
#include "../include/entrada.h"
#include "../include/Pecas.h"
#include "../include/controleNave.h"
int main() {
    char nomeArquivo[100];
    int opcao = 1;

    while (opcao != 0) {
        printf("\n====================================\n");
        printf("     EXPRESSO INTERESTELAR \n");
        printf("=====================================\n");
        printf("[1] Executar programa com os arquivos ja criados da pasta 'testes'\n");
        printf("[2] Gerar novo arquivo de teste\n");
        printf("[0] Sair\n> ");
        scanf("%d", &opcao);

        if (opcao == 0) {
            printf("\nEncerrando o programa...\n");
            break;
        }

        if (opcao == 2) {
            gerarMapaAutomaticamente();
            continue;
        }

        if (opcao == 1) {
            printf("\nDigite o nome do arquivo de entrada (ex: testes/mapa1.txt): ");
            scanf("%s", nomeArquivo);

            if (nomeArquivo[0] == '0') {
                printf("\nEncerrando o programa...\n");
                break;
            }

            Mapa* m = lerArquivo(nomeArquivo);
            if (m == NULL) {
                printf("\nErro: nao foi possivel ler o arquivo '%s'.\n", nomeArquivo);
                printf("Verifique o caminho e tente novamente.\n");
                continue; 
            }
            imprimirMapa(m);
            encontraCaminho(m);
            liberarMapa(m);

            printf("\nDeseja carregar outro arquivo?\n");
            printf("[1] Sim\n[0] Nao (sair)\n> ");
            scanf("%d", &opcao);
        } 
        else {
            printf("\nOpcao invalida! Tente novamente.\n");
        }
    }

    return 0;
}
