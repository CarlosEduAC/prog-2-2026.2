#include <stdio.h>

int contar_pares(const int *v, int tam) {
    // 1. CASO BASE: Vetor vazio (tamanho zero) possui 0 pares
    if (tam == 0) {
        return 0;
    }

    // Verifica se o último elemento atual é par (1 se verdadeiro, 0 se falso)
    int eh_par = (v[tam - 1] % 2 == 0) ? 1 : 0;

    // 2. PASSO RECURSIVO: Soma o resultado atual ao da chamada para o restante do vetor (tam - 1)
    return eh_par + contar_pares(v, tam - 1);
}

int main(void) {
    int dados[] = {3, 8, 12, 5, 10};
    int tam = sizeof(dados) / sizeof(dados[0]);

    int total = contar_pares(dados, tam);
    printf("Quantidade de elementos pares: %d\n", total); // Esperado: 3

    return 0;
}