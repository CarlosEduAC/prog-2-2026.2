#include "stdio.h"

int main() {
    int numero;

    printf("Digite um numero: ");
    if (scanf("%d", &numero) != 1 || numero < 1 || numero > 100) {
        printf("Entrada invalida. Por favor, digite um numero inteiro.\n");
        return 1;
    }

    printf("\n");

    for (int i = 0; i < numero; i++) {
        for (int espaco = 0; espaco < numero - i - 1; espaco++) {
            printf(" ");
        }

        int termo = 1;

        for (int j = 0; j <= i; j++) {
            printf("%d ", termo);

            termo = termo * (i - j) / (j + 1);
        }

        printf("\n");
    }

    return 0;
}
