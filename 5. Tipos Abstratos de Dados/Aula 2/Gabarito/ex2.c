#include <stdlib.h>

typedef struct {
    int **matriz;
    int linhas;
    int colunas;
} MatrizBuffer;

MatrizBuffer* matriz_buffer_criar(int linhas, int colunas) {
    // 1. Validação de entradas
    if (linhas <= 0 || colunas <= 0) return NULL;

    // 2. Alocação da Estrutura Principal
    MatrizBuffer *mb = (MatrizBuffer *) malloc(sizeof(MatrizBuffer));
    if (mb == NULL) return NULL;

    mb->linhas = linhas;
    mb->colunas = colunas;

    // 3. Alocação do Vetor de Ponteiros para as Linhas
    mb->matriz = (int **) malloc(linhas * sizeof(int *));
    if (mb->matriz == NULL) {
        free(mb); // ROLLBACK NÍVEL 1: Libera a estrutura principal
        return NULL;
    }

    // 4. Alocação Dinâmica de Cada Linha Individualmente
    for (int i = 0; i < linhas; i++) {
        mb->matriz[i] = (int *) malloc(colunas * sizeof(int));

        // FALHA NA ALOCAÇÃO DA LINHA i: Iniciar Rollback Recursivo/Gradual
        if (mb->matriz[i] == NULL) {

            // ROLLBACK NÍVEL 2: Libera todas as linhas alocadas com sucesso até i-1
            for (int k = 0; k < i; k++) {
                free(mb->matriz[k]);
            }

            // Libera o vetor de ponteiros e a estrutura
            free(mb->matriz);
            free(mb);
            return NULL; // Retorna NULL sinalizando erro de memória ao cliente
        }
    }

    return mb; // Sucesso absoluto na alocação!
}

void matriz_buffer_destruir(MatrizBuffer *mb) {
    if (mb == NULL) return;

    if (mb->matriz != NULL) {
        for (int i = 0; i < mb->linhas; i++) {
            free(mb->matriz[i]);
        }
        free(mb->matriz);
    }
    free(mb);
}