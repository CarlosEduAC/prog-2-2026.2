#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int linhas = 2;
    int colunas = 3;

    // 1. PASSO 1: Aloque o vetor de PONTEIROS (as linhas)
    // O tipo é (int **), usamos sizeof(int *) pois guarda endereços!
    int **matriz = (int **) malloc(linhas * sizeof(int *));

    if (matriz == NULL) {
        printf("Erro na alocação principal!\n");
        return 1;
    }

    // 2. PASSO 2: Para cada linha, aloque o vetor de VALORES (as colunas)
    for (int i = 0; i < linhas; i++) {
        matriz[i] = (int *) malloc(colunas * sizeof(int));

        if (matriz[i] == NULL) {
            printf("Erro na alocação da linha %d!\n", i);
            return 1;
        }
    }

    // 3. USO NORMAL: Usamos o duplo colchete matriz[i][j]
    matriz[0][0] = 10; matriz[0][1] = 20; matriz[0][2] = 30;
    matriz[1][0] = 40; matriz[1][1] = 50; matriz[1][2] = 60;

    // Exibindo os valores
    printf("=== CONTEÚDO DA MATRIZ ===\n");
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            printf("%d\t", matriz[i][j]);
        }
        printf("\n");
    }

    // 4. PASSO 3: DESALOCAÇÃO (Na ordem inversa!)

    // Primeiro: Libera cada linha (os vetores internos)
    for (int i = 0; i < linhas; i++) {
        free(matriz[i]);
        matriz[i] = NULL;
    }

    // Segundo: Libera o vetor principal de linhas
    free(matriz);
    matriz = NULL;

    printf("\nMatriz desalocada com sucesso!\n");
    return 0;
}