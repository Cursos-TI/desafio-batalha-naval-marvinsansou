#include <stdio.h>

// Desafio Batalha Naval - MateCheck
// Este código inicial serve como base para o desenvolvimento do sistema de Batalha Naval.
// Siga os comentários para implementar cada parte do desafio.

#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3

// Função para inicializar o tabuleiro com água (0)
void inicializarTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = 0;  // água
        }
    }
}

// Função para verificar se navio pode ser colocado sem sair dos limites
int navioCabe(int linha_inicial, int coluna_inicial, int tamanho, char orientacao) {
    if (orientacao == 'H') {
        // Horizontal: coluna inicial + tamanho <= limite
        return (coluna_inicial + tamanho <= TAMANHO_TABULEIRO);
    } else if (orientacao == 'V') {
        // Vertical: linha inicial + tamanho <= limite
        return (linha_inicial + tamanho <= TAMANHO_TABULEIRO);
    }
    return 0; // orientação inválida
}

// Função para verificar se a posição está livre para colocar navio (sem sobreposição)
int navioSemSobreposicao(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha_inicial, int coluna_inicial, int tamanho, char orientacao) {
    if (orientacao == 'H') {
        for (int i = 0; i < tamanho; i++) {
            if (tabuleiro[linha_inicial][coluna_inicial + i] == 3) {
                return 0; // já ocupado
            }
        }
    } else if (orientacao == 'V') {
        for (int i = 0; i < tamanho; i++) {
            if (tabuleiro[linha_inicial + i][coluna_inicial] == 3) {
                return 0; // já ocupado
            }
        }
    }
    return 1; // livre para colocar
}

// Função para posicionar o navio copiando vetor no tabuleiro
void posicionarNavio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int navio[TAMANHO_NAVIO], int linha_inicial, int coluna_inicial, char orientacao) {
    if (orientacao == 'H') {
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            tabuleiro[linha_inicial][coluna_inicial + i] = navio[i];
        }
    } else if (orientacao == 'V') {
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            tabuleiro[linha_inicial + i][coluna_inicial] = navio[i];
        }
    }
}

// Função para imprimir o tabuleiro
void imprimirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    printf("Tabuleiro (0=água, 3=navio):\n\n");
    printf("   ");
    for (int col = 0; col < TAMANHO_TABULEIRO; col++) {
        printf("%2d ", col);
    }
    printf("\n");

    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        printf("%2d ", i);
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            printf(" %d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int main() {
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    int navioHorizontal[TAMANHO_NAVIO] = {3, 3, 3};  // representa partes do navio
    int navioVertical[TAMANHO_NAVIO] = {3, 3, 3};

    // Definindo as coordenadas iniciais dos navios (podem ser alteradas)
    int linhaNavioH = 2, colunaNavioH = 4;  // Horizontal
    int linhaNavioV = 5, colunaNavioV = 7;  // Vertical

    // Inicializa o tabuleiro
    inicializarTabuleiro(tabuleiro);

    // Verifica se navio horizontal cabe e não sobrepõe
    if (!navioCabe(linhaNavioH, colunaNavioH, TAMANHO_NAVIO, 'H')) {
        printf("Navio horizontal não cabe no tabuleiro nas coordenadas fornecidas.\n");
        return 1;
    }
    if (!navioSemSobreposicao(tabuleiro, linhaNavioH, colunaNavioH, TAMANHO_NAVIO, 'H')) {
        printf("Navio horizontal sobrepõe outro navio.\n");
        return 1;
    }
    posicionarNavio(tabuleiro, navioHorizontal, linhaNavioH, colunaNavioH, 'H');

    // Verifica se navio vertical cabe e não sobrepõe
    if (!navioCabe(linhaNavioV, colunaNavioV, TAMANHO_NAVIO, 'V')) {
        printf("Navio vertical não cabe no tabuleiro nas coordenadas fornecidas.\n");
        return 1;
    }
    if (!navioSemSobreposicao(tabuleiro, linhaNavioV, colunaNavioV, TAMANHO_NAVIO, 'V')) {
        printf("Navio vertical sobrepõe outro navio.\n");
        return 1;
    }
    posicionarNavio(tabuleiro, navioVertical, linhaNavioV, colunaNavioV, 'V');

    // Imprime o tabuleiro final
    imprimirTabuleiro(tabuleiro);

    return 0;
}
