#include <stdio.h>

#define LINHAS 2
#define COLUNAS 3

// 1. Passagem de Vetor: Passa apenas o ponteiro base
void zerar_vetor(int *vet, int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        vet[i] = 0; // Equivalente a *(vet + i) = 0
    }
}

// 2. Passagem de Matriz: O número de COLUNAS é obrigatório na assinatura!
void exibir_matriz(int mat[][COLUNAS], int linhas) {
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < COLUNAS; j++) {
            printf("[%d] ", mat[i][j]);
        }
        printf("\n");
    }
}

int main(void) {
    int vetor[4] = {10, 20, 30, 40};
    int matriz[LINHAS][COLUNAS] = {
        {1, 2, 3},
        {4, 5, 6}
    };

    printf("=== INSPEÇÃO DE ENDEREÇOS NO VETOR ===\n");
    printf("Endereço base do vetor (vetor)   : %p\n", (void*)vetor);
    printf("Endereço do 1º elem (&vetor[0])   : %p\n\n", (void*)&vetor[0]);

    printf("=== EXIBINDO MATRIZ ORIGINAL ===\n");
    exibir_matriz(matriz, LINHAS);

    printf("\n=== ZERANDO VETOR VIA FUNÇÃO ===\n");
    zerar_vetor(vetor, 4);
    printf("Novo valor de vetor[0]: %d\n", vetor[0]);

    return 0;
}