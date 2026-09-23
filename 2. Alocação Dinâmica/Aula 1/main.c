#include <stdio.h>
#include <stdlib.h> // Biblioteca OBRIGATÓRIA para malloc, free e NULL

int main(void) {
    // 1. Declaramos o ponteiro na Stack
    int *p = (int *) malloc(sizeof(int));
    if (p == NULL) {
        printf("[ ERRO CRÍTICO ] Memória RAM insuficiente!\n");
        return 1; // Encerra o programa com erro
    }

    // 4. Usamos a memória no Heap normalmente através da desreferenciação (*)
    *p = 42;

    printf("=== INSPEÇÃO DA MEMÓRIA ===\n");
    printf("Endereço do ponteiro 'p' (na Stack) : %p\n", (void*)&p);
    printf("Endereço apontado por 'p' (no Heap) : %p\n", (void*)p);
    printf("Valor armazenado no Heap (*p)       : %d\n\n", *p);

    // 5. MANDAMENTO 2: Devolver a memória ao Sistema Operacional
    free(p);
    p = NULL;

    printf("[ SUCESSO ] Memória desalocada e ponteiro redefinido para NULL.\n");

    return 0;
}