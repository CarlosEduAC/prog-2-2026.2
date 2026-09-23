#include <stdio.h>


//? => Combinação n! / p! * (n - p)!

int main(void) {
    int n;

    printf("Digite o numero de linhas do Triangulo de Pascal (max 12): ");
    if (scanf("%d", &n) != 1 || n < 1 || n > 12) {
        printf("Entrada invalida! Digite um valor entre 1 e 12.\n");
        return 1;
    }

    printf("\n");

    for (int i = 0; i < n; i++) {
        // 1. Imprime os espaços à esquerda para alinhar em forma de pirâmide
        for (int espaco = 0; espaco < n - i - 1; espaco++) {
            printf("  ");
        }

        long long termo = 1; // Primeiro termo de qualquer linha é sempre 1

        // 2. Calcula e imprime os termos C(i, k) usando a relação multiplicativa
        for (int k = 0; k <= i; k++) {
            printf("%4lld", termo);

            // Atualiza o termo diretamente sem usar fatoriais ou vetores:
            // C(i, k+1) = C(i, k) * (i - k) / (k + 1)
            termo = termo * (i - k) / (k + 1);
        }

        printf("\n");
    }

    return 0;
}