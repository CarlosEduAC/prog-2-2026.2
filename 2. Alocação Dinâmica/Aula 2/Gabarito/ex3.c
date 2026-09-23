#include <stdio.h>
#include <stdlib.h>

// Função que recebe um vetor, seu tamanho e retorna um NOVO vetor alocado no Heap
int* inverte_vetor(int *v, int n) {
    // 1. Aloque o novo vetor no Heap
    int *v_inv = (int *) malloc(n * sizeof(int));
    if (v_inv == NULL) {
        printf("[ERRO] Falha ao alocar memória na função!\n");
        return NULL;
    }

    // 2. Copia os elementos de v em ordem inversa para v_inv
    for (int i = 0; i < n; i++) {
        v_inv[i] = v[n - 1 - i];
    }

    return v_inv; // Retorna o ponteiro alocado no Heap
}

int main(void) {
    int n;

    printf("Digite o tamanho do vetor: ");
    if (scanf("%d", &n) != 1 || n <= 0) return 1;

    // 1. Aloca o primeiro vetor
    int *v1 = (int *) malloc(n * sizeof(int));
    if (v1 == NULL) {
        printf("[ERRO] Memória insuficiente!\n");
        return 1;
    }

    // 2. Preenche o vetor original
    printf("Digite os %d elementos:\n", n);
    for (int i = 0; i < n; i++) {
        printf("v1[%d] = ", i);
        scanf("%d", &v1[i]);
    }

    // 3. Chama a função que retorna o novo vetor alocado
    int *v2 = inverte_vetor(v1, n);
    if (v2 == NULL) {
        free(v1);
        return 1;
    }

    // 4. Exibe ambos os vetores
    printf("\n--- VETOR ORIGINAL (v1) ---\n");
    for (int i = 0; i < n; i++) printf("%d ", v1[i]);

    printf("\n--- VETOR INVERTIDO (v2) ---\n");
    for (int i = 0; i < n; i++) printf("%d ", v2[i]);
    printf("\n");

    // 5. REGRA DE OURO: Liberar AMBOS os ponteiros alocados
    free(v1);
    v1 = NULL;

    free(v2);
    v2 = NULL;

    printf("\n[SUCESSO] Toda a memória foi liberada corretamente.\n");
    return 0;
}