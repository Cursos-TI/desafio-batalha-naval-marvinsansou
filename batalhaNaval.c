#include <stdio.h>


#define TAMANHO_TABULEIRO 10
#define TAMANHO_HABILIDADE 5

#define AGUA 0
#define NAVIO 3
#define AREA_HABILIDADE 5

// Inicializa tabuleiro com água
void inicializarTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }
}

// Posiciona alguns navios fixos para exemplo (simples)
// Navios são marcados com 3 no tabuleiro
void posicionarNavios(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    // Exemplo: um navio horizontal no topo
    for (int i = 1; i <= 3; i++) {
        tabuleiro[0][i] = NAVIO;
    }
    // Exemplo: um navio vertical na coluna 7
    for (int i = 5; i < 8; i++) {
        tabuleiro[i][7] = NAVIO;
    }
}

// Constrói a matriz do Cone (ponto no topo, expande para base)
// 1 = área afetada, 0 = não afetada
void construirCone(int cone[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            // Condição para formar um cone centrado na coluna do meio e que vai ampliando a área para baixo
            int meio = TAMANHO_HABILIDADE / 2;
            if (i >= 0 && j >= (meio - i) && j <= (meio + i)) {
                cone[i][j] = 1;
            } else {
                cone[i][j] = 0;
            }
        }
    }
}

// Constrói a matriz da Cruz (ponto de origem no centro)
void construirCruz(int cruz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    int meio = TAMANHO_HABILIDADE / 2;
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            if (i == meio || j == meio) {
                cruz[i][j] = 1;
            } else {
                cruz[i][j] = 0;
            }
        }
    }
}

// Constrói a matriz do Octaedro (losango com ponto de origem no centro)
void construirOctaedro(int octaedro[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    int meio = TAMANHO_HABILIDADE / 2;
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            // Forma de losango: a soma das distâncias do centro nas duas direções <= meio
            int dist = abs(i - meio) + abs(j - meio);
            if (dist <= meio) {
                octaedro[i][j] = 1;
            } else {
                octaedro[i][j] = 0;
            }
        }
    }
}

// Sobrepõe matriz de habilidade no tabuleiro centrada em (origem_linha, origem_coluna)
void aplicarHabilidade(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE], int origem_linha, int origem_coluna) {
    int meio = TAMANHO_HABILIDADE / 2;

    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            if (habilidade[i][j] == 1) {
                int tab_linha = origem_linha + (i - meio);
                int tab_coluna = origem_coluna + (j - meio);

                // Verifica limites do tabuleiro
                if (tab_linha >= 0 && tab_linha < TAMANHO_TABULEIRO && tab_coluna >= 0 && tab_coluna < TAMANHO_TABULEIRO) {
                    // Marca área de habilidade sem apagar navios (navios continuam visíveis)
                    if (tabuleiro[tab_linha][tab_coluna] == AGUA) {
                        tabuleiro[tab_linha][tab_coluna] = AREA_HABILIDADE;
                    }
                }
            }
        }
    }
}

// Imprime o tabuleiro
void imprimirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    printf("Tabuleiro (0=agua, 3=navio, 5=area habilidade):\n\n  ");
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
    int cone[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];
    int cruz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];
    int octaedro[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];

    // Inicializa o tabuleiro
    inicializarTabuleiro(tabuleiro);

    // Posiciona navios para visualização
    posicionarNavios(tabuleiro);

    // Constrói as matrizes de habilidade dinamicamente
    construirCone(cone);
    construirCruz(cruz);
    construirOctaedro(octaedro);

    // Define pontos de origem para as habilidades no tabuleiro
    int origem_cone_linha = 2, origem_cone_coluna = 2;
    int origem_cruz_linha = 5, origem_cruz_coluna = 5;
    int origem_octaedro_linha = 7, origem_octaedro_coluna = 7;

    // Aplica as habilidades sobre o tabuleiro
    aplicarHabilidade(tabuleiro, cone, origem_cone_linha, origem_cone_coluna);
    aplicarHabilidade(tabuleiro, cruz, origem_cruz_linha, origem_cruz_coluna);
    aplicarHabilidade(tabuleiro, octaedro, origem_octaedro_linha, origem_octaedro_coluna);

    // Imprime o resultado final
    imprimirTabuleiro(tabuleiro);

    return 0;
}
