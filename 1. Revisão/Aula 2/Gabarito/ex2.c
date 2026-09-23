#include <stdio.h>

int main(void) {
    long long num;

    printf("Digite um numero inteiro positivo: ");
    if (scanf("%lld", &num) != 1 || num <= 0) {
        printf("Entrada invalida!\n");
        return 1;
    }

    long long temp = num;
    long long invertido = 0;

    int maior_digito = -1;
    int menor_digito = 10;

    int eh_crescente = 1;   // Considera ordem da esquerda para a direita
    int eh_decrescente = 1;
    int digito_anterior = -1;

    // Processa os dígitos da direita para a esquerda usando aritmética
    while (temp > 0) {
        int digito = temp % 10;

        // Atualiza a inversão
        invertido = (invertido * 10) + digito;

        // Atualiza maior e menor dígito
        if (digito > maior_digito) maior_digito = digito;
        if (digito < menor_digito) menor_digito = digito;

        // Valida a ordem dos dígitos
        if (digito_anterior != -1) {
            // Como estamos lendo da direita para a esquerda:
            if (digito >= digito_anterior) eh_crescente = 0;
            if (digito <= digito_anterior) eh_decrescente = 0;
        }

        digito_anterior = digito;
        temp /= 10;
    }

    printf("\nNumero Invertido: %lld\n", invertido);
    printf("E Palindromo: %s\n", (num == invertido) ? "SIM" : "NAO");
    printf("Maior Digito: %d | Menor Digito: %d\n", maior_digito, menor_digito);

    printf("Ordenacao dos digitos: ");
    if (num < 10) {
        printf("Apenas um digito\n");
    } else if (eh_crescente) {
        printf("Estritamente Crescente\n");
    } else if (eh_decrescente) {
        printf("Estritamente Decrescente\n");
    } else {
        printf("Desordenados\n");
    }

    return 0;
}