#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int tam_inicial = 3;

    // 1. CALLOC: Aloque 3 inteiros. Diferente do malloc, ele zera a memória!
    int *v = (int *) calloc(tam_inicial, sizeof(int));
    if (v == NULL) {
        printf("Erro na alocação!\n");
        return 1;
    }

    printf("=== Valores após calloc (zerados automaticamente) ===\n");
    for (int i = 0; i < tam_inicial; i++) {
        printf("v[%d] = %d\n", i, v[i]); // Exibe: 0, 0, 0
    }

    // Atribuindo valores
    v[0] = 10; v[1] = 20; v[2] = 30;

    // 2. REALLOC: O array ficou pequeno. Vamos expandir para 5 posições!
    int novo_tam = 5;

    // Boa prática: usar ponteiro auxiliar ao fazer realloc
    int *temp = (int *) realloc(v, novo_tam * sizeof(int));
    if (temp == NULL) {
        printf("Erro ao realocar!\n");
        free(v); // Se realloc falhar, o ponteiro original ainda precisa ser liberado
        return 1;
    }
    v = temp; // Atualiza o ponteiro principal com o novo endereço

    // Atribuindo novos valores nas posições adicionadas
    v[3] = 40;
    v[4] = 50;

    printf("\n=== Valores após realloc (expandido para 5) ===\n");
    for (int i = 0; i < novo_tam; i++) {
        printf("v[%d] = %d\n", i, v[i]);
    }

    // Liberação
    free(v);
    v = NULL;

    return 0;
}