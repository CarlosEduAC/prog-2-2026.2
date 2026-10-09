#include "lista_alunos.h"
#include <stdlib.h>

// Estrutura interna de Nó (Oculta)
typedef struct No {
    int matricula;
    float nota;
    struct No *proximo;
} No;

// Estrutura de Controle da Lista (Oculta)
struct ListaAlunos {
    No *cabeca;
    int quantidade;
};

ListaAlunos* lista_criar(void) {
    ListaAlunos *l = (ListaAlunos *) malloc(sizeof(ListaAlunos));
    if (l == NULL) return NULL;
    l->cabeca = NULL;
    l->quantidade = 0;
    return l;
}

bool lista_inserir(ListaAlunos *l, int matricula, float nota) {
    if (l == NULL) return false;

    No *novo = (No *) malloc(sizeof(No));
    if (novo == NULL) return false;

    novo->matricula = matricula;
    novo->nota = nota;
    novo->proximo = l->cabeca;
    l->cabeca = novo;
    l->quantidade++;

    return true;
}

float lista_buscar_nota(const ListaAlunos *l, int matricula) {
    if (l == NULL) return -1.0f;

    const No *atual = l->cabeca;
    while (atual != NULL) {
        if (atual->matricula == matricula) {
            return atual->nota;
        }
        atual = atual->proximo;
    }

    return -1.0f; // Matrícula não encontrada
}

void lista_destruir(ListaAlunos *l) {
    if (l == NULL) return;

    No *atual = l->cabeca;
    while (atual != NULL) {
        No *temp = atual->proximo;
        free(atual);
        atual = temp;
    }
    free(l);
}