#include <stdio.h>
#include <stdlib.h>

// 1. Definição da Estrutura Auto-Referenciada
typedef struct No {
    int valor;
    struct No *proximo; // Ponteiro para o próximo nó do mesmo tipo
} No;

// 2. Função Recursiva para percorrer a corrente de nós
int somar_nos(const No *p) {
    // CASO BASE: Chegou ao fim da corrente (ponteiro nulo)
    if (p == NULL) {
        return 0;
    }

    // PASSO RECURSIVO: Valor do nó atual + soma dos nós restantes
    return p->valor + somar_nos(p->proximo);
}

int main(void) {
    // 3. Alocação manual dos 3 nós no Heap
    No *n1 = (No *) malloc(sizeof(No));
    No *n2 = (No *) malloc(sizeof(No));
    No *n3 = (No *) malloc(sizeof(No));

    if (n1 == NULL || n2 == NULL || n3 == NULL) {
        printf("Erro ao alocar memoria!\n");
        return 1;
    }

    // Atribuição de valores
    n1->valor = 10;
    n2->valor = 20;
    n3->valor = 30;

    // Encadeamento manual dos elos
    n1->proximo = n2;
    n2->proximo = n3;
    n3->proximo = NULL; // Fim da lista

    // Chamada da função recursiva passando o primeiro nó (cabeça da lista)
    int total = somar_nos(n1);

    printf("=== RECURSÃO EM ESTRUTURAS AUTO-REFERENCIADAS ===\n");
    printf("Soma dos valores na corrente (10 + 20 + 30): %d\n", total);

    // Desalocação manual de cada nó
    free(n1);
    free(n2);
    free(n3);

    n1 = NULL;
    n2 = NULL;
    n3 = NULL;

    return 0;
}