#include <stdio.h>

// Retorna o maior valor do vetor entre os índices 'inicio' e 'fim'
int maior_elementos_recursivo(const int *v, int inicio, int fim) {
    // 1. CASO BASE: Subvetor de tamanho 1 (início e fim se encontraram)
    if (inicio == fim) {
        return v[inicio];
    }

    // Calcula o meio para dividir o vetor
    int meio = inicio + (fim - inicio) / 2;

    // 2. PASSO RECURSIVO: Acha o maior na metade esquerda e na metade direita
    int maior_esq = maior_elementos_recursivo(v, inicio, meio);
    int maior_dir = maior_elementos_recursivo(v, meio + 1, fim);

    // CONQUISTA/COMBINAÇÃO: Retorna o maior dos dois lados
    return (maior_esq > maior_dir) ? maior_esq : maior_dir;
}

int soma_vetor_recursivo(const int *v, int tam) {
    // CASO BASE: Vetor vazio
    if (tam == 0) {
        return 0;
    }

    // PASSO RECURSIVO: Último elemento + soma do restante do vetor (tam - 1)
    return v[tam - 1] + soma_vetor_recursivo(v, tam - 1);
}

int main(void) {
    int dados[] = {12, 45, 78, 2, 99, 34, 61};
    int tam = sizeof(dados) / sizeof(dados[0]);

    int soma = soma_vetor_recursivo(dados, tam);
    // int maior = maior_elementos_recursivo(dados, 0, tam - 1);
    // printf("O maior elemento do vetor e: %d\n", maior); // Esperado: 99

    printf("A soma dos elementos do vetor e: %d\n", soma);

    return 0;
}