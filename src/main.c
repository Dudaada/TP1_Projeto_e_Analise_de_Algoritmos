#include <stdio.h>
#include <stdlib.h> 

#include "../include/entrada.h"
#include "../include/controleNave.h"
#include "../include/Pecas.h"

// Variável global que controla o modo analise
int g_modo_analise = 0; // 0 = desligado, 1 = ligado
long int g_chamadas_recursivas = 0;
int g_profundidade_maxima = 0;
int g_profundidade_atual = 0; // Variável auxiliar



// Variável global que controla o nível de detalhe da saída
int g_modo_exibicao = 1;

int main() {
    Mapa *mapa_atual = NULL; 
    char nomeArquivoCarregado[100]; 
    int opcao;

    printf("Deseja ativar o MODO ANALISE para esta sessao? (contabiliza chamadas recursivas)\n");
    printf("[1] Sim\n[0] Nao\nEscolha uma opcao: ");
    scanf("%d", &g_modo_analise);
    if (g_modo_analise == 1) {
        printf(">>> MODO ANALISE ATIVADO <<<\n");
    }


    // O laço principal continua enquanto a opção não for 0
    do {
        printf("\n====================================\n");
        printf("     EXPRESSO INTERESTELAR\n");
        printf("====================================\n");
        if (mapa_atual != NULL) {
            printf(">>> Mapa carregado: %s <<<\n\n", nomeArquivoCarregado);
        }
        printf("[1] Carregar Mapa da Nave\n");
        printf("[2] Iniciar Jornada (Encontrar Caminho)\n");
        printf("[3] Gerar Novo Mapa\n");
        printf("[0] Sair do Programa\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: // Carrega mapa
                printf("\n--- Carregar Mapa ---\n");
                printf("Digite o nome do arquivo de entrada (ex: testes/mapa1.txt): ");
                scanf("%s", nomeArquivoCarregado);

                // Se já existir um mapa na memória, libera antes de carregar um novo
                if (mapa_atual != NULL) {
                    liberarMapa(mapa_atual);
                }

                mapa_atual = lerArquivo(nomeArquivoCarregado);

                if (mapa_atual != NULL) {
                    printf("Mapa '%s' carregado com sucesso!\n", nomeArquivoCarregado);
                    imprimirMapa(mapa_atual); // Mostra o mapa para o usuário confirmar
                }
                // Se falhar, a função lerArquivo já avisa o erro
                
                printf("\nPressione Enter para voltar ao menu principal...");
                while (getchar() != '\n');
                getchar();
                break;

            case 2: // Inicia jornada
                if (mapa_atual == NULL) {
                    printf("\nERRO: Nenhum mapa carregado. Por favor, use a Opcao [1] primeiro.\n");
                } else {
                    printf("\n--- Iniciar Jornada em '%s' ---\n", nomeArquivoCarregado);
                    printf("Escolha como deseja ver o resultado:\n");
                    printf("[1] Relatorio Detalhado\n[2] Relatorio com apenas casos de sucessos\n[3] Apenas o Mapa Final\n");
                    printf("Escolha uma opcao de exibicao: ");
                    scanf("%d", &g_modo_exibicao);

                    // ZERA OS CONTADORES ANTES DE CADA EXECUÇÃO
                    if (g_modo_analise == 1) {
                        g_chamadas_recursivas = 0;
                        g_profundidade_maxima = 0;
                        g_profundidade_atual = 0;
                    }


                    int resultado = encontraCaminho(mapa_atual);

                    printf("\n--- Fim da Jornada ---\n");
                    if (resultado == 1) {
                        if (mapa_atual->qtdPecas >= 4) {
                            printf("A jornada sera finalizada sem mais desafios\n");
                        } else {
                            printf("A tripulacao finalizou sua jornada\n");
                        }
                    } else {
                        printf("Apesar da bravura a tripulacao falhou em sua jornada\n");
                    }

                    // EXIBE O RELATÓRIO DE ANÁLISE
                    if (g_modo_analise == 1) {
                        printf("\n--- RELATORIO DE ANALISE ---\n");
                        printf("Total de chamadas da funcao recursiva: %ld\n", g_chamadas_recursivas);
                        printf("Nivel maximo de recursao alcancado: %d\n", g_profundidade_maxima);
                    }
                    
                    // "Reseta" o mapa, recarregando o arquivo original para permitir uma nova execução
                    liberarMapa(mapa_atual);
                    mapa_atual = lerArquivo(nomeArquivoCarregado);
                }
                
                printf("\nPressione Enter para voltar ao menu principal...");
                while (getchar() != '\n');
                getchar();
                break;

            case 3: // Gerar novo mapa
                printf("\n--- Gerador de Mapas ---\n");
                gerarMapaAutomaticamente(); 
                printf("\nMapa gerado! Pressione Enter para voltar ao menu principal...");
                while (getchar() != '\n');
                getchar(); 
                break;

            case 0: // Sair
                printf("\nEncerrando o Expresso Interestelar. Ate a proxima!\n");
                break;

            default:
                printf("\nOpcao invalida! Tente novamente.\n");
                break;
        }

    } while (opcao != 0);

    // Limpeza final antes de fechar o programa
    if (mapa_atual != NULL) {
        liberarMapa(mapa_atual);
    }

    return 0;
}