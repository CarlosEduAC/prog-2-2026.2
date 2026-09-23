#include <stdio.h>

int somatorio(int n) {
    // 1. CASO BASE: A soma até 1 (ou menor/igual a 0) é o próprio valor
    if (n <= 1) {
        return n;
    }

    // 2. PASSO RECURSIVO: n + somatorio(n - 1)
    return n + somatorio(n - 1);
}

int main(void) {
    int n = 5;
    printf("Somatorio de 1 ate %d: %d\n", n, somatorio(n)); // Esperado: 15
    return 0;
}