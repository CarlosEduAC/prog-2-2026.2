#include "tiro.h"
#include "raylib.h"
#include <stdlib.h>

// Nó da Lista Duplamente Encadeada
typedef struct NoTiro {
    float x, y;
    float vel_y;
    struct NoTiro *anterior;
    struct NoTiro *proximo;
} NoTiro;

struct GerenciadorTiros {
    NoTiro *head;
    NoTiro *tail;
    int qtd;
};

GerenciadorTiros* tiros_criar(void) {
    GerenciadorTiros *gt = (GerenciadorTiros *) malloc(sizeof(GerenciadorTiros));
    if (!gt) return NULL;
    gt->head = NULL;
    gt->tail = NULL;
    gt->qtd = 0;
    return gt;
}

void tiros_adicionar(GerenciadorTiros *gt, float x, float y, float vel_y) {
    if (!gt) return;
    NoTiro *novo = (NoTiro *) malloc(sizeof(NoTiro));
    if (!novo) return;

    novo->x = x;
    novo->y = y;
    novo->vel_y = vel_y;
    novo->proximo = NULL;
    novo->anterior = gt->tail;

    if (!gt->tail) {
        gt->head = novo;
        gt->tail = novo;
    } else {
        gt->tail->proximo = novo;
        gt->tail = novo;
    }
    gt->qtd++;
}

void tiros_atualizar_e_renderizar(GerenciadorTiros *gt, int altura_tela) {
    if (!gt) return;
    NoTiro *atual = gt->head;

    while (atual != NULL) {
        NoTiro *proximo_no = atual->proximo;
        atual->y += atual->vel_y;

        DrawRectangle((int)atual->x, (int)atual->y, 4, 10, YELLOW);

        // Remoção O(1) se sair da tela
        if (atual->y < 0 || atual->y > altura_tela) {
            if (atual->anterior) atual->anterior->proximo = atual->proximo;
            else gt->head = atual->proximo;

            if (atual->proximo) atual->proximo->anterior = atual->anterior;
            else gt->tail = atual->anterior;

            free(atual);
            gt->qtd--;
        }
        atual = proximo_no;
    }
}

bool tiros_verificar_colisao_alvo(GerenciadorTiros *gt, float alvo_x, float alvo_y, float raio_alvo) {
    if (!gt) return false;
    NoTiro *atual = gt->head;

    while (atual != NULL) {
        Vector2 pos_tiro = { atual->x, atual->y };
        Vector2 pos_alvo = { alvo_x, alvo_y };

        if (CheckCollisionPointCircle(pos_tiro, pos_alvo, raio_alvo)) {
            if (atual->anterior) atual->anterior->proximo = atual->proximo;
            else gt->head = atual->proximo;

            if (atual->proximo) atual->proximo->anterior = atual->anterior;
            else gt->tail = atual->anterior;

            free(atual);
            gt->qtd--;
            return true;
        }
        atual = atual->proximo;
    }
    return false;
}

void tiros_destruir(GerenciadorTiros *gt) {
    if (!gt) return;
    NoTiro *atual = gt->head;
    while (atual) {
        NoTiro *temp = atual->proximo;
        free(atual);
        atual = temp;
    }
    free(gt);
}