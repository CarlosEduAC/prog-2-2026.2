#include <stdio.h>
#include <stdbool.h>

// O Tamanho das Variáveis (sizeof) e os Bytes

int main(void) {
    printf("=== TAMANHO DOS TIPOS NA MEMORIA RAM ===\n\n");

    printf("char        : %lu byte  (8 bits)\n", sizeof(char));
    printf("bool        : %lu byte  (8 bits)\n", sizeof(bool));
    printf("int         : %lu bytes (32 bits)\n", sizeof(int));
    printf("float       : %lu bytes (32 bits)\n", sizeof(float));
    printf("double      : %lu bytes (64 bits)\n", sizeof(double));
    printf("long long   : %lu bytes (64 bits)\n", sizeof(long long));

    return 0;
}