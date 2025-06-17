#include <stdio.h>


#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3
#define NAVIO_VALOR 3

// Inicializa o tabuleiro com água (0)
void inicializarTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = 0;
        }
    }
}

// Verifica se posição está dentro dos limites
int estaDentroLimites(int linha, int coluna) {
    return (linha >= 0 && linha < TAMANHO_TABULEIRO && coluna >= 0 && coluna < TAMANHO_TABULEIRO);
}

// Verifica se navio cabe e não sobrepõe em orientação horizontal ou vertical
int podePosicionarHV(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha_inicial, int coluna_inicial, char orientacao) {
    if (orientacao == 'H') {
        if (coluna_inicial + TAMANHO_NAVIO > TAMANHO_TABULEIRO) return 0;
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            if (tabuleiro[linha_inicial][coluna_inicial + i] == NAVIO_VALOR) return 0;
        }
    } else if (orientacao == 'V') {
        if (linha_inicial + TAMANHO_NAVIO > TAMANHO_TABULEIRO) return 0;
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            if (tabuleiro[linha_inicial + i][coluna_inicial] == NAVIO_VALOR) return 0;
        }
    } else {
        return 0; // orientação inválida
    }
    return 1;
}

// Verifica se navio diagonal cabe e não sobrepõe
// sentido: 'D' = diagonal descendente (linha++, coluna++)
//          'S' = diagonal ascendente (linha--, coluna++)
int podePosicionarDiagonal(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha_inicial, int coluna_inicial, char sentido) {
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        int linha = (sentido == 'D') ? linha_inicial + i : linha_inicial - i;
        int coluna = coluna_inicial + i;
        if (!estaDentroLimites(linha, coluna)) return 0;
        if (tabuleiro[linha][coluna] == NAVIO_VALOR) return 0;
    }
    return 1;
}

// Posiciona navio horizontal ou vertical
void posicionarNavioHV(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha_inicial, int coluna_inicial, char orientacao) {
    if (orientacao == 'H') {
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            tabuleiro[linha_inicial][coluna_inicial + i] = NAVIO_VALOR;
        }
    } else if (orientacao == 'V') {
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            tabuleiro[linha_inicial + i][coluna_inicial] = NAVIO_VALOR;
        }
    }
}

// Posiciona navio diagonal
void posicionarNavioDiagonal(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha_inicial, int coluna_inicial, char sentido) {
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        int linha = (sentido == 'D') ? linha_inicial + i : linha_inicial - i;
        int coluna = coluna_inicial + i;
        tabuleiro[linha][coluna] = NAVIO_VALOR;
    }
}

// Imprime o tabuleiro formatado
void imprimirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    printf("Tabuleiro (0=água, 3=navio):\n\n  ");
    for (int c = 0; c < TAMANHO_TABULEIRO; c++) {
        printf("%2d ", c);
    }
    printf("\n");
    for (int l = 0; l < TAMANHO_TABULEIRO; l++) {
        printf("%2d ", l);
        for (int c = 0; c < TAMANHO_TABULEIRO; c++) {
            printf(" %d ", tabuleiro[l][c]);
        }
        printf("\n");
    }
    printf("\n");
}

int main() {
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];

    // Inicializa o tabuleiro com água
    inicializarTabuleiro(tabuleiro);

    // Coordenadas e orientações dos navios
    int linhaH1 = 1, colunaH1 = 1;  // Horizontal
    int linhaV1 = 5, colunaV1 = 3;  // Vertical
    int linhaD1 = 2, colunaD1 = 5;  // Diagonal descendente
    int linhaD2 = 7, colunaD2 = 0;  // Diagonal ascendente

    // Posiciona navio horizontal
    if (podePosicionarHV(tabuleiro, linhaH1, colunaH1, 'H')) {
        posicionarNavioHV(tabuleiro, linhaH1, colunaH1, 'H');
    } else {
        printf("Erro: não foi possível posicionar navio horizontal 1\n");
    }

    // Posiciona navio vertical
    if (podePosicionarHV(tabuleiro, linhaV1, colunaV1, 'V')) {
        posicionarNavioHV(tabuleiro, linhaV1, colunaV1, 'V');
    } else {
        printf("Erro: não foi possível posicionar navio vertical 1\n");
    }

    // Posiciona navio diagonal descendente
    if (podePosicionarDiagonal(tabuleiro, linhaD1, colunaD1, 'D')) {
        posicionarNavioDiagonal(tabuleiro, linhaD1, colunaD1, 'D');
    } else {
        printf("Erro: não foi possível posicionar navio diagonal descendente\n");
    }

    // Posiciona navio diagonal ascendente
    if (podePosicionarDiagonal(tabuleiro, linhaD2, colunaD2, 'S')) {
        posicionarNavioDiagonal(tabuleiro, linhaD2, colunaD2, 'S');
    } else {
        printf("Erro: não foi possível posicionar navio diagonal ascendente\n");
    }

    // Imprime o tabuleiro final
    imprimirTabuleiro(tabuleiro);

    return 0;
}
