#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../include/entrada.h"

Mapa* lerArquivo(const char* nomeArquivo) {
    FILE* arquivo = fopen(nomeArquivo, "r");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo: %s\n", nomeArquivo);
        return NULL;
    }

    //aloca a estrutura principal
    Mapa* m = (Mapa*) malloc(sizeof(Mapa));
    if (!m) {
        printf("Erro de alocação de memória para Mapa.\n");
        fclose(arquivo);
        return NULL;
    }

    //lê os valores iniciais
    fscanf(arquivo, "%d %d %d", &m->D, &m->Dperda, &m->Againho);
    fscanf(arquivo, "%d %d", &m->altura, &m->largura);

    //aloca a matriz do mapa
    m->mapa = (char**) malloc(m->altura * sizeof(char*));
    for (int i = 0; i < m->altura; i++) {
        m->mapa[i] = (char*) malloc((m->largura + 1) * sizeof(char)); // +1 pro '\0'
    }

    for (int i = 0; i < m->altura; i++) {
        fscanf(arquivo, "%s", m->mapa[i]);
    }

    fclose(arquivo);

    //localiza a posição inicial 'X' e final 'Y'
    m->linhaInicial = -1;
    m->colunaInicial = -1;

    m->linhaFinal=-1;
    m->colunaFinal=-1;
    
    int fim=0;

    for (int i = 0; i < m->altura && !fim; i++) {
        for (int j = 0; j < m->largura; j++) {
            if (m->mapa[i][j] == 'X') {
                m->linhaInicial = i;
                m->colunaInicial = j;
            }
            else if (m->mapa[i][j] == 'F') {
                m->linhaFinal = i;
                m->colunaFinal = j;
            }
            if (m->linhaInicial!=-1 && m->linhaFinal!=-1){
                fim=1;
                break;
            }
        }
    }

    if (m->linhaInicial == -1) {
        printf("Aviso: posição inicial 'X' não encontrada no mapa.\n");
    }

    // inicializa o contador de pecas
    m->qtdPecas = 0;
    return m;
}

void liberarMapa(Mapa* m) {
    if (m == NULL) return;

    for (int i = 0; i < m->altura; i++) {
        free(m->mapa[i]);
    }
    free(m->mapa);
    free(m);
}

void imprimirMapa(Mapa* m) {
    printf("\nMapa lido com sucesso!\n");
    printf("D = %d, D' = %d, A = %d\n", m->D, m->Dperda, m->Againho);
    printf("Altura = %d, Largura = %d\n", m->altura, m->largura);
    printf("Posicao inicial (X): linha %d, coluna %d\n\n", m->linhaInicial, m->colunaInicial);
    printf("Posicao final (F): linha %d, coluna %d\n\n", m->linhaFinal, m->colunaFinal);

    for (int i = 0; i < m->altura; i++) {
        for (int j = 0; j < m->largura; j++) {
            char c = m->mapa[i][j];
            switch (c) {
                case 'X':  
                    printf(RED "X" RESET);
                    break;
                case 'F': 
                    printf(GREEN "F" RESET);
                    break;
                case 'P':  
                    printf(YELLOW "P" RESET);
                    break;
                case '-':  
                    printf(CYAN "-" RESET);
                    break;
                case '|':  
                    printf(CYAN "|" RESET);
                    break;
                case '+':  
                    printf(MAGENTA "+" RESET);
                    break;
                case '.':  
                    printf(GRAY "." RESET);
                    break;
                default:   
                    printf(WHITE "%c" RESET, c);
                    break;
            }
        }
        printf("\n");
    }
    printf("\n");
}

//função auxiliar para gerar caracteres do mapa com base na dificuldade
char gerarCaractereCaminho(int dificuldade) {
    int r = rand() % 100;
    switch (dificuldade) {
        case 1: // fácil
            if (r < 60) return '-';
            else if (r < 80) return '|';
            else if (r < 90) return '+';
            else return '.';
        case 2: // médio
            if (r < 40) return '-';
            else if (r < 55) return '|';
            else if (r < 65) return '+';
            else return '.';
        case 3: // difícil
            if (r < 25) return '-';
            else if (r < 35) return '|';
            else if (r < 40) return '+';
            else return '.';
        default:
            return '.';
    }
}

//função principal de geração do mapa
Mapa gerarMapaAutomaticamente() {
    srand(time(NULL));

    int D, Dperda, Againho;
    int altura, largura, pecas, dificuldade;
    char nomeArquivo[100];

    printf("\n=== GERADOR DE MAPAS AUTOMATICOS ===\n\n");

    printf("Durabilidade inicial (D): ");
    scanf("%d", &D);

    printf("Perda por movimento (D'): ");
    scanf("%d", &Dperda);

    printf("Ganho por peça (A): ");
    scanf("%d", &Againho);

    printf("Altura do mapa: ");
    scanf("%d", &altura);

    printf("Largura do mapa: ");
    scanf("%d", &largura);

    printf("Quantidade de peças (P): ");
    scanf("%d", &pecas);

    printf("Nivel de dificuldade (1 = facil, 2 = medio, 3 = dificil): ");
    scanf("%d", &dificuldade);

    printf("Nome do arquivo de saida (ex: testes/mapaN.txt, sendo N um número): ");
    scanf("%s", nomeArquivo);

    //aloca o mapa
    char **mapa = malloc(altura * sizeof(char *));
    for (int i = 0; i < altura; i++)
        mapa[i] = malloc((largura + 1) * sizeof(char));

    //gera o conteúdo
    for (int i = 0; i < altura; i++) {
        for (int j = 0; j < largura; j++) {
            mapa[i][j] = gerarCaractereCaminho(dificuldade);
        }
        mapa[i][largura] = '\0';
    }

    //define início e destino
    int xLinha = rand() % altura;
    int xColuna = rand() % largura;
    int fLinha, fColuna;
    do {
        fLinha = rand() % altura;
        fColuna = rand() % largura;
    } while (fLinha == xLinha && fColuna == xColuna);

    mapa[xLinha][xColuna] = 'X';
    mapa[fLinha][fColuna] = 'F';

    //adiciona peças
    for (int k = 0; k < pecas; k++) {
        int pLinha, pColuna;
        do {
            pLinha = rand() % altura;
            pColuna = rand() % largura;
        } while (mapa[pLinha][pColuna] == 'X' || mapa[pLinha][pColuna] == 'F' || mapa[pLinha][pColuna] == 'P');
        mapa[pLinha][pColuna] = 'P';
    }

    //salva o arquivo
    FILE *arq = fopen(nomeArquivo, "w");
    if (!arq) {
        printf("\nErro ao criar o arquivo!\n");
        Mapa m = {0};
        return m; //retorna um mapa vazio em caso de erro
    }

    fprintf(arq, "%d %d %d\n", D, Dperda, Againho);
    fprintf(arq, "%d %d\n", altura, largura);
    for (int i = 0; i < altura; i++)
        fprintf(arq, "%s\n", mapa[i]);
    fclose(arq);

    printf("\nArquivo '%s' gerado com sucesso!\n\n", nomeArquivo);

    //cria a struct Mapa
    Mapa m;
    m.D = D;
    m.Dperda = Dperda;
    m.Againho = Againho;
    m.altura = altura;
    m.largura = largura;
    m.mapa = mapa;
    m.linhaInicial = xLinha;
    m.colunaInicial = xColuna;

    imprimirMapa(&m);

    return m; 
}
