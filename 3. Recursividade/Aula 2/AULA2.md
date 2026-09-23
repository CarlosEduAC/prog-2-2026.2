# Recursividade em Vetores e Algoritmos de Divisão e Conquista

## O Padrão de Projeto — Divisão e Conquista

A estratégia que fundamenta a maioria dos algoritmos eficientes em Ciência da Computação:

```txt

                    ESTRATÉGIA: DIVISÃO E CONQUISTA

                            [ PROBLEMA M ]
                                  │
                  ┌───────────────┴───────────────┐
                  ▼                               ▼
            [ SUBPROBLEMA M/2 ]             [ SUBPROBLEMA M/2 ]
                  │                               │
            ┌─────┴─────┐                   ┌─────┴─────┐
            ▼           ▼                   ▼           ▼
          [ BASE ]    [ BASE ]            [ BASE ]    [ BASE ]
            │           │                   │           │
            └─────┬─────┘                   └─────┬─────┘
                  ▼                               ▼
             [ SOLUÇÃO ]                     [ SOLUÇÃO ]
                  │                               │
                  └───────────────┬───────────────┘
                                  ▼
                          [ SOLUÇÃO FINAL ]

```

### O Segredo nos Vetores: Controle por Índices

Em vez de criar cópias do vetor (o que gastaria muita memória no Heap/Stack), passamos o mesmo ponteiro de vetor e alteramos apenas os índices delimitadores de escopo: inicio e fim.

## Processando Vetores com Recursão

Exemplo 1: Encontrar o Maior Elemento de um Vetor

```c

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

int main(void) {
    int dados[] = {12, 45, 78, 2, 99, 34, 61};
    int tam = sizeof(dados) / sizeof(dados[0]);

    int maior = maior_elementos_recursivo(dados, 0, tam - 1);
    printf("O maior elemento do vetor e: %d\n", maior); // Esperado: 99

    return 0;
}

```

Exemplo 2: Somatório dos Elementos de um Vetor

```c

int soma_vetor_recursivo(const int *v, int tam) {
    // CASO BASE: Vetor vazio
    if (tam == 0) {
        return 0;
    }

    // PASSO RECURSIVO: Último elemento + soma do restante do vetor (tam - 1)
    return v[tam - 1] + soma_vetor_recursivo(v, tam - 1);
}

```
