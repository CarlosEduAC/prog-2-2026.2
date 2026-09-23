#include <stdio.h>
#include <stdbool.h>

// #define N 3
#define N 5

void exibir_tabuleiro(char lab[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%c ", lab[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

bool resolver_labirinto(char lab[N][N], int x, int y) {
    // 1. CASO BASE 1: Fora dos limites da matriz ou encontrou parede (x)
    if (x < 0 || x >= N || y < 0 || y >= N || lab[x][y] == 'x' || lab[x][y] == 'v') {
        return false;
    }

    // 2. CASO BASE 2 (Sucesso): Chegou ao destino (canto inferior direito [N-1][N-1])
    if (x == N - 1 && y == N - 1) {
        lab[x][y] = 'v'; // Marca caminho da solução
        return true;
    }

    // --- FAZER A ESCOLHA ---
    lab[x][y] = 'v'; // Marca temporariamente como parte do caminho

    // --- EXPLORAÇÃO (Tenta Direita, depois Baixo) ---
    if (resolver_labirinto(lab, x, y + 1)) return true; // Direita
    if (resolver_labirinto(lab, x + 1, y)) return true; // Baixo

    // --- DESFAZER A ESCOLHA (BACKTRACKING) ---
    // Se nenhum caminho deu certo, desfaz a marcação para permitir outras rotas
    lab[x][y] = ' ';
    return false;
}

int main(void) {
    // 1 = Caminho Livre, 0 = Parede
    // char labirinto[N][N] = {
    //     {' ', 'x', 'x'},
    //     {' ', 'x', 'x'},
    //     {'x', ' ', ' '}
    // };

    char labirinto[N][N] = {
        {' ', 'x', 'x', 'x', 'x'},
        {' ', ' ', 'x', ' ', 'x'},
        {'x', ' ', 'x', ' ', 'x'},
        {'x', ' ', ' ', ' ', ' '},
        {'x', 'x', 'x', 'x', ' '}
    };

    printf("=== LABIRINTO ORIGINAL ===\n");
    exibir_tabuleiro(labirinto);

    if (resolver_labirinto(labirinto, 0, 0)) {
        printf("=== CAMINHO ENCONTRADO (Caminho marcando com 'v') ===\n");
        exibir_tabuleiro(labirinto);
    } else {
        printf("Nao existe caminho ate a saída!\n");
    }

    return 0;
}