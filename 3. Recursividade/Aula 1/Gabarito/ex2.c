#include <stdio.h>

void imprimir_reverso(const char *str) {
    // 1. CASO BASE: Se o caractere atual for o fim da string ('\0'), encerra
    if (*str == '\0') {
        return;
    }

    // 2. PASSO RECURSIVO: Avança o ponteiro para o próximo caractere
    imprimir_reverso(str + 1);

    // 3. AÇÃO APÓS A RECURSÃO: Imprime na fase de desempilhamento da Stack
    putchar(*str);
}

int main(void) {
    const char palavra[] = "ALGORITMO";

    printf("String original: %s\n", palavra);
    printf("String invertida: ");
    imprimir_reverso(palavra);
    printf("\n");

    return 0;
}