#include <stdio.h>

int busca_binaria_recursiva(const int *vetor, int inicio, int fim, int chave) {
    // 1. CASO BASE 1 (Falha): Espaço de busca esgotado
    if (inicio > fim) {
        return -1; // Chave não encontrada
    }

    // Cálculo do índice do meio (evita estouro de inteiro)
    int meio = inicio + (fim - inicio) / 2;

    // 2. CASO BASE 2 (Sucesso): Elemento encontrado
    if (vetor[meio] == chave) {
        return meio;
    }

    // 3. PASSO RECURSIVO: Ajusta os limites para a metade adequada
    if (chave < vetor[meio]) {
        // Busca na metade esquerda (de inicio ate meio - 1)
        return busca_binaria_recursiva(vetor, inicio, meio - 1, chave);
    } else {
        // Busca na metade direita (de meio + 1 ate fim)
        return busca_binaria_recursiva(vetor, meio + 1, fim, chave);
    }
}

int main(void) {
    int dados[] = {10, 23, 35, 42, 58, 67, 71, 89, 95};
    int tam = sizeof(dados) / sizeof(dados[0]);
    int chave = 67;

    int idx = busca_binaria_recursiva(dados, 0, tam - 1, chave);

    if (idx != -1) {
        printf("Chave %d encontrada no indice [%d].\n", chave, idx);
    } else {
        printf("Chave %d nao encontrada no vetor.\n", chave);
    }

    return 0;
}