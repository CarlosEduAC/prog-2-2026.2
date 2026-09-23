#include <stdio.h>

void trocar(int *a, int *b);
void troca_errada(int a, int b);
void calcular_dobro_e_triplo(int numero, int *dobro, int *triplo);

int main(void) {
    int x = 5, y = 20;

    printf("=== ANTES DA TROCA ===\n");
    printf("x = %d | y = %d\n\n", x, y);

    // Passamos os ENDEREÇOS das variáveis usando o operador &
    //trocar(&x, &y);
    // troca_errada(x, y); // Não altera os valores de x e y

    printf("=== DEPOIS DA TROCA ===\n");
    printf("x = %d | y = %d\n\n", x, y);

    // Testando o cálculo múltiplo
    int dobro, triplo;
    calcular_dobro_e_triplo(x, &dobro, &triplo);
    printf("Dobro de %d = %d | Triplo = %d\n", x, dobro, triplo);

    return 0;
}

// Os parâmetros recebem ENDEREÇOS de memória (ponteiros)
void trocar(int *a, int *b) {
    int temp = *a; // temp guarda o valor contido no endereço 'a'
    *a = *b;       // O endereço 'a' recebe o valor contido no endereço 'b'
    *b = temp;     // O endereço 'b' recebe o valor de temp
}

void troca_errada(int a, int b) {
    int temp = a;
    a = b;
    b = temp;
} // 'a' e 'b' morrem aqui sem alterar a main()

// Solução do desafio inicial: Retornando múltiplos valores via ponteiros
void calcular_dobro_e_triplo(int numero, int *dobro, int *triplo) {
    *dobro = numero * 2;
    *triplo = numero * 3;
}
