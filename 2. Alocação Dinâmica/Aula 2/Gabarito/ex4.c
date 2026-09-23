#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int capacidade = 2; // Tamanho inicial pequeno para testar o realloc
    int qtd = 0;        // Elementos atualmente armazenados
    int num;

    // 1. Alocação inicial para 2 elementos
    int *v = (int *) malloc(capacidade * sizeof(int));
    if (v == NULL) {
        printf("[ERRO] Falha ao alocar vetor inicial!\n");
        return 1;
    }

    printf("=== Digite números inteiros (Digite -1 para encerrar) ===\n");

    while (1) {
        printf("Número %d: ", qtd + 1);
        scanf("%d", &num);

        if (num == -1) break; // Flag de encerramento

        // 2. Checa se o vetor encheu
        if (qtd == capacidade) {
            capacidade *= 2; // Dobra a capacidade atual
            printf("--> [REALLOC] Vetor cheio! Expandindo capacidade para %d elementos...\n", capacidade);

            int *temp = (int *) realloc(v, capacidade * sizeof(int));
            if (temp == NULL) {
                printf("[ERRO CRÍTICO] Falha ao reallocar! Mantendo os dados anteriores.\n");
                break;
            }
            v = temp;
        }

        // 3. Insere o elemento
        v[qtd] = num;
        qtd++;
    }

    // 4. Exibe o resumo final
    printf("\n================ RESUMO DO VETOR ================\n");
    printf("Elementos armazenados: %d\n", qtd);
    printf("Capacidade final alocada no Heap: %d posições (%lu bytes)\n",
            capacidade, capacidade * sizeof(int));

    printf("\nValores digitados: ");
    for (int i = 0; i < qtd; i++) {
        printf("[%d] ", v[i]);
    }
    printf("\n");

    // 5. Liberação
    free(v);
    v = NULL;

    return 0;
}