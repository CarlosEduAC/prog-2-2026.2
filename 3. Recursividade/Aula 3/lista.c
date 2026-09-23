#include <stdio.h>

typedef struct No {
    int dado;
    struct No *proximo;
} No;

void imprimir_lista_recursiva(const No *no_atual) {
    if (no_atual == NULL) return; // Caso Base: Fim da Lista

    printf("%d -> ", no_atual->dado);
    imprimir_lista_recursiva(no_atual->proximo); // Passo Recursivo!
}

int main(void) {
    No no3 = {30, NULL};
    No no2 = {20, &no3};
    No no1 = {10, &no2};

    printf("\nLista: ");
    imprimir_lista_recursiva(&no1);
    printf("NULL\n"); // Indica o fim da lista

    return 0;
}