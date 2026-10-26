#include "vetor.h"
#include <stdlib.h>
#include <stdbool.h>

struct VetorDinamico {
    int *dados;
    int tamanho;
    int capacidade;
};

VetorDinamico* vetor_criar(int capacidade_inicial) {
    if (capacidade_inicial <= 0) capacidade_inicial = 4;

    VetorDinamico *v = (VetorDinamico *) malloc(sizeof(VetorDinamico));
    if (v == NULL) return NULL;

    v->dados = (int *) malloc(capacidade_inicial * sizeof(int));
    if (v->dados == NULL) {
        free(v);
        return NULL;
    }

    v->tamanho = 0;
    v->capacidade = capacidade_inicial;
    return v;
}

bool vetor_inserir(VetorDinamico *v, int elemento) {
    if (v == NULL) return false;

    // Redimensionamento expansivo oculto do cliente
    if (v->tamanho == v->capacidade) {
        int nova_cap = v->capacidade * 2;
        int *temp = (int *) realloc(v->dados, nova_cap * sizeof(int));
        if (temp == NULL) return false;

        v->dados = temp;
        v->capacidade = nova_cap;
    }

    v->dados[v->tamanho] = elemento;
    v->tamanho++;
    return true;
}

bool vetor_obter(const VetorDinamico *v, int indice, int *valor_out) {
    if (v == NULL || indice < 0 || indice >= v->tamanho || valor_out == NULL) {
        return false;
    }
    *valor_out = v->dados[indice];
    return true;
}

int vetor_get_tamanho(const VetorDinamico *v) {
    return v ? v->tamanho : 0;
}

void vetor_destruir(VetorDinamico *v) {
    if (v != NULL) {
        free(v->dados);
        free(v);
    }
}