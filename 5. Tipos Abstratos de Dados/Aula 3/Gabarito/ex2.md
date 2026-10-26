1. Problemas Identificados:

A struct Municao está visível no .h, permitindo que o main.c modifique projeteis_restantes diretamente sem checar se ultrapassa a capacidade_maxima ou se o ponteiro é NULL.

2. Código Refatorado:
3.
municao.h (Interface com Ponteiro Opaco):

```c

#ifndef MUNICAO_H
#define MUNICAO_H

#include <stdbool.h>

// Declaração incompleta - O cliente não sabe o conteúdo da struct
typedef struct Municao Municao;

Municao* municao_criar(int capacidade);
void municao_destruir(Municao *m);
bool municao_recarregar(Municao *m, int qtd);

#endif

```

municao.c (Implementação Encapsulada):

```c
#include "municao.h"
#include <stdlib.h>

struct Municao {
    int projeteis_restantes;
    int capacidade_maxima;
};

Municao* municao_criar(int capacidade) {
    if (capacidade <= 0) return NULL;
    Municao *m = (Municao *) malloc(sizeof(Municao));
    if (!m) return NULL;
    m->capacidade_maxima = capacidade;
    m->projeteis_restantes = capacidade;
    return m;
}

bool municao_recarregar(Municao *m, int qtd) {
    if (!m || qtd <= 0) return false;
    m->projeteis_restantes += qtd;
    if (m->projeteis_restantes > m->capacidade_maxima) {
        m->projeteis_restantes = m->capacidade_maxima; // Proteção da invariante
    }
    return true;
}

void municao_destruir(Municao *m) {
    free(m);
}

```
