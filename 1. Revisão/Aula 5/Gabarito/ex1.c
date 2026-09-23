#include <stdio.h>

void encontrar_min_max(int a, int b, int c, int *menor, int *maior);

int main(void) {
    int n1 = 45, n2 = 12, n3 = 88;
    int min, max;

    // Passamos os endereços de 'min' e 'max' com o operador &
    encontrar_min_max(n1, n2, n3, &min, &max);

    printf("Valores informados: %d, %d, %d\n", n1, n2, n3);
    printf("Menor valor: %d\n", min);
    printf("Maior valor: %d\n", max);

    return 0;
}

void encontrar_min_max(int a, int b, int c, int *menor, int *maior) {
    // Inicializa os ponteiros apontando para o primeiro valor
    *menor = a;
    *maior = a;

    // Avalia o menor valor
    if (b < *menor) *menor = b;
    if (c < *menor) *menor = c;

    // Avalia o maior valor
    if (b > *maior) *maior = b;
    if (c > *maior) *maior = c;
}