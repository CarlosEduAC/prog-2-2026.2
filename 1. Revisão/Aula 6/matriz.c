#include <stdio.h>

#define LINHAS 2
#define COLUNAS 3

void demonstrar_acesso_ram(int mat[][COLUNAS], int linhas) {
    // Convertemos o ponteiro da matriz para um ponteiro de inteiro simples
    int *ptr_ram = (int *)mat;
    int total_elementos = linhas * COLUNAS;

    printf("=== 1. VISÃO LOGICA (2D - LINHAS E COLUNAS) ===\n");
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < COLUNAS; j++) {
            printf("mat[%d][%d] = %2d  (Endereco: %p)\n", i, j, mat[i][j], (void*)&mat[i][j]);
        }
    }

    printf("\n=== 2. VISÃO REAL NA RAM (1D - PONTEIRO SEQUENCIAL) ===\n");
    for (int k = 0; k < total_elementos; k++) {
        // Percorremos a memória como uma linha única contínua
        printf("*(ptr_ram + %d) = %2d  (Endereco: %p)\n", k, *(ptr_ram + k), (void*)(ptr_ram + k));
    }

    printf("\n=== 3. PROVANDO A FORMULA DE ACESSO INTERNO ===\n");
    int i = 1, j = 1; // Queremos acessar mat[1][1] (valor 50)

    // Fórmula: Base + (i * COLUNAS + j)
    int offset = (i * COLUNAS) + j;
    int valor_calculado = *(ptr_ram + offset);

    printf("Acessando mat[%d][%d]:\n", i, j);
    printf("  • Sintaxe padrao mat[%d][%d] : %d\n", i, j, mat[i][j]);
    printf("  • Calculo offset (%d*%d + %d) : Pula %d inteiros\n", i, COLUNAS, j, offset);
    printf("  • Acesso via ponteiro       : %d\n", valor_calculado);
}

int main(void) {
    int matriz[LINHAS][COLUNAS] = {
        {10, 20, 30}, // Linha 0
        {40, 50, 60}  // Linha 1
    };

    demonstrar_acesso_ram(matriz, LINHAS);

    return 0;
}