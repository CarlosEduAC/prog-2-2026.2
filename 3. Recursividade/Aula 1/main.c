
#include <stdio.h>

void contagem_correta(int n) {
    // 1. CASO BASE (Condição de Parada)
    if (n < 0) {
        printf("Fim da contagem!\n");
        return; // Interrompe as chamadas e inicia o desempilhamento
    }

    printf("n = %d\n", n);

    // 2. PASSO RECURSIVO
    contagem_correta(n - 1);
}

int main(void) {
    printf("Iniciando recursão sem parada...\n");

    contagem_correta(10);

    return 0;
}