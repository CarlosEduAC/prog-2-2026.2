#include <stdio.h>
#include <stdbool.h>

bool eh_palindromo_vetor(const int *v, int inicio, int fim) {
    // 1. CASO BASE 1 (Sucesso): Os índices se cruzaram ou se encontraram no meio
    if (inicio >= fim) {
        return true;
    }

    // 2. CASO BASE 2 (Falha): Elementos nas extremidades são diferentes
    if (v[inicio] != v[fim]) {
        return false;
    }

    // 3. PASSO RECURSIVO: Aproxima os índices das extremidades em direção ao centro
    return eh_palindromo_vetor(v, inicio + 1, fim - 1);
}

int main(void) {
    int v1[] = {1, 4, 9, 4, 1};
    int v2[] = {1, 4, 9, 8, 1};

    int tam = 5;

    printf("v1 e palindromo? %s\n", eh_palindromo_vetor(v1, 0, tam - 1) ? "Sim" : "Nao"); // Sim
    printf("v2 e palindromo? %s\n", eh_palindromo_vetor(v2, 0, tam - 1) ? "Sim" : "Nao"); // Nao

    return 0;
}