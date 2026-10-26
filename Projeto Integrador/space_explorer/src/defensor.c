#include "defensor.h"
#include "raylib.h"
#include <stdlib.h>

// Nó da Pilha Dinâmica LIFO
typedef struct NoPilha {
    float x;
    int vida;
    struct NoPilha *proximo;
} NoPilha;

// Estrutura Concreta Oculta
struct Defensor {
    float x, y;
    float velocidade;
    int vida;
    int largura, altura;
    NoPilha *pilha_undo; // Topo da Pilha
    int qtd_undo;
};

Defensor* defensor_criar(float x, float y, float velocidade) {
    Defensor *d = (Defensor *) malloc(sizeof(Defensor));
    if (!d) return NULL;

    d->x = x;
    d->y = y;
    d->velocidade = velocidade;
    d->vida = 100;
    d->largura = 40;
    d->altura = 20;
    d->pilha_undo = NULL;
    d->qtd_undo = 0;
    return d;
}

void defensor_salvar_estado_pilha(Defensor *d) {
    if (!d) return;
    NoPilha *novo = (NoPilha *) malloc(sizeof(NoPilha));
    if (!novo) return;

    novo->x = d->x;
    novo->vida = d->vida;
    novo->proximo = d->pilha_undo;
    d->pilha_undo = novo;
    d->qtd_undo++;
}

bool defensor_executar_reversao_temporal(Defensor *d) {
    if (!d || !d->pilha_undo) return false;

    // Pop na Pilha LIFO
    NoPilha *topo = d->pilha_undo;
    d->x = topo->x;
    d->vida = topo->vida;

    d->pilha_undo = topo->proximo;
    free(topo);
    d->qtd_undo--;
    return true;
}

void defensor_destruir(Defensor *d) {
    if (!d) return;
    while (d->pilha_undo) {
        NoPilha *temp = d->pilha_undo;
        d->pilha_undo = d->pilha_undo->proximo;
        free(temp);
    }
    free(d);
}

void defensor_atualizar(Defensor *d, int largura_tela) {
    if (!d) return;

    if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) {
        if (d->x > 10) {
            d->x -= d->velocidade;
            defensor_salvar_estado_pilha(d);
        }
    }
    if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) {
        if (d->x < largura_tela - d->largura - 10) {
            d->x += d->velocidade;
            defensor_salvar_estado_pilha(d);
        }
    }

    // Tecla 'Z' aciona a Reversão Temporal (Pop LIFO)
    if (IsKeyPressed(KEY_Z)) {
        defensor_executar_reversao_temporal(d);
    }
}

void defensor_renderizar(const Defensor *d) {
    if (!d) return;
    // Corpo do Canhão Defensor
    DrawRectangle((int)d->x, (int)d->y, d->largura, d->altura, LIME);
    DrawRectangle((int)d->x + 15, (int)d->y - 8, 10, 8, GREEN);
}

float defensor_get_x(const Defensor *d) { return d ? d->x : 0; }
float defensor_get_y(const Defensor *d) { return d ? d->y : 0; }
int defensor_get_vida(const Defensor *d) { return d ? d->vida : 0; }
int defensor_get_qtd_undo(const Defensor *d) { return d ? d->qtd_undo : 0; }
void defensor_causar_dano(Defensor *d, int dano) { if (d) d->vida -= dano; }