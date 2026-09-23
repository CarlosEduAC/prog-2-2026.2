#include <stdio.h>

int main(void) {
    int x = 0;
    int a = 5;
    double b = 20;
    char c = 'X';


    printf("=== INSPECAO DE ENDERECOS DE MEMORIA ===\n\n");

    // %p é o especificador de formato para imprimir endereços de memória (em hexadecimal)
    printf("Variavel 'x': Valor = %-5d | Endereco = %p\n", x, (void*)&x);
    printf("Variavel 'a': Valor = %-5d | Endereco = %p\n", a, (void*)&a);
    printf("Variavel 'b': Valor = %-5f | Endereco = %p\n", b, (void*)&b);
    printf("Variavel 'c': Valor = '%c'   | Endereco = %p\n", c, (void*)&c);

    return 0;
}