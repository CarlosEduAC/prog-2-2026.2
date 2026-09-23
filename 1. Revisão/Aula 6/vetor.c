#include <stdio.h>

int main(void) {
    int vetor[4] = {10, 20, 30, 40};

    // O nome do vetor 'vetor' se decai para o endereço do primeiro elemento (&vetor[0])
    int *p = vetor;

    printf("=== 1. COMPROVANDO QUE O VETOR É UM PONTEIRO ===\n");
    printf("Endereço base de 'vetor' : %p\n", (void*)vetor);
    printf("Endereço armazenado em p : %p\n", (void*)p);
    printf("Endereço de &vetor[0]    : %p\n\n", (void*)&vetor[0]);

    printf("=== 2. EQUIVALÊNCIA SINTÁTICA: vet[i] vs *(p + i) ===\n");
    for (int i = 0; i < 4; i++) {
        printf("Índice [%d] | Notação vet[%d]: %d | Notação *(p + %d): %d | Endereço: %p\n",
               i, i, vetor[i], i, *(p + i), (void*)(p + i));
    }

    printf("\n=== 3. MODIFICANDO O VETOR NAVEGANDO COM O PONTEIRO ===\n");

    // Avançamos o ponteiro 2 posições para frente (salta 8 bytes na RAM!)
    p += 2;
    printf("Ponteiro p após 'p += 2' aponta para o valor: %d (Endereço: %p)\n", *p, (void*)p);

    // Alteramos o elemento vetor[2] através da desreferenciação do ponteiro
    *p = 999;

    printf("Novo valor de vetor[2] lido direto do vetor original: %d\n", vetor[2]);

    return 0;
}