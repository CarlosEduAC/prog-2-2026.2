#include "placar.h"
#include <stdlib.h>
#include <string.h>

struct Placar {
    char nome[30];
    int pontos;
    int vidas;
};

Placar* placar_criar(const char *nome) {
    if (nome == NULL) return NULL;

    Placar *p = (Placar *) malloc(sizeof(Placar));
    if (p == NULL) return NULL;

    strncpy(p->nome, nome, sizeof(p->nome) - 1);
    p->nome[sizeof(p->nome) - 1] = '\0';
    p->pontos = 0;
    p->vidas = 3;

    return p;
}

void placar_destruir(Placar *p) {
    if (p != NULL) {
        free(p);
    }
}

void placar_adicionar_pontos(Placar *p, int qtd) {
    if (p == NULL || qtd <= 0) return;
    p->pontos += qtd;
}

void placar_remover_vida(Placar *p) {
    if (p == NULL || p->vidas <= 0) return;
    p->vidas--;
}

int placar_get_pontos(const Placar *p) { return p ? p->pontos : 0; }
int placar_get_vidas(const Placar *p) { return p ? p->vidas : 0; }
const char* placar_get_nome(const Placar *p) { return p ? p->nome : ""; }