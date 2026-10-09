#include "inimigo.h"
#include "raylib.h"
#include <stdlib.h>

typedef struct NoFila {
    float x, y, velocidade;
    bool e_aglomerado;
    struct NoFila *proximo;
} NoFila;

struct FilaInimigos {
    NoFila *inicio;
    NoFila *fim;
    int qtd;
};

FilaInimigos* fila_inimigos_criar(void) {
    FilaInimigos *f = (FilaInimigos *) malloc(sizeof(FilaInimigos));
    if (!f) return NULL;
    f->inicio = f->fim = NULL;
    f->qtd = 0;
    return f;
}

void fila_inimigos_enqueue(FilaInimigos *f, float x, float y, float velocidade, bool e_aglomerado) {
    if (!f) return;
    NoFila *novo = (NoFila *) malloc(sizeof(NoFila));
    if (!novo) return;

    novo->x = x; novo->y = y; novo->velocidade = velocidade;
    novo->e_aglomerado = e_aglomerado;
    novo->proximo = NULL;

    if (!f->fim) { f->inicio = f->fim = novo; }
    else { f->fim->proximo = novo; f->fim = novo; }
    f->qtd++;
}

bool fila_inimigos_dequeue(FilaInimigos *f, float *x_out, float *y_out, float *vel_out, bool *aglomerado_out) {
    if (!f || !f->inicio) return false;
    NoFila *temp = f->inicio;

    if (x_out) *x_out = temp->x;
    if (y_out) *y_out = temp->y;
    if (vel_out) *vel_out = temp->velocidade;
    if (aglomerado_out) *aglomerado_out = temp->e_aglomerado;

    f->inicio = f->inicio->proximo;
    if (!f->inicio) f->fim = NULL;
    free(temp);
    f->qtd--;
    return true;
}

int fila_inimigos_qtd(const FilaInimigos *f) { return f ? f->qtd : 0; }

void fila_inimigos_destruir(FilaInimigos *f) {
    if (!f) return;
    float x, y, v; bool a;
    while (fila_inimigos_dequeue(f, &x, &y, &v, &a));
    free(f);
}

// Lista Dupla de Inimigos Ativos em Tela
typedef struct NoInimigo {
    float x, y, velocidade;
    bool e_aglomerado;
    struct NoInimigo *anterior;
    struct NoInimigo *proximo;
} NoInimigo;

struct GerenciadorInimigos {
    NoInimigo *head;
    NoInimigo *tail;
    int qtd;
};

AtivosInimigos* ativos_inimigos_criar(void) {
    AtivosInimigos *ai = (AtivosInimigos *) malloc(sizeof(AtivosInimigos));
    if (!ai) return NULL;
    ai->head = ai->tail = NULL;
    ai->qtd = 0;
    return ai;
}

void ativos_inimigos_adicionar(AtivosInimigos *ai, float x, float y, float velocidade, bool e_aglomerado) {
    if (!ai) return;
    NoInimigo *novo = (NoInimigo *) malloc(sizeof(NoInimigo));
    if (!novo) return;

    novo->x = x; novo->y = y; novo->velocidade = velocidade;
    novo->e_aglomerado = e_aglomerado;
    novo->proximo = NULL;
    novo->anterior = ai->tail;

    if (!ai->tail) { ai->head = ai->tail = novo; }
    else { ai->tail->proximo = novo; ai->tail = novo; }
    ai->qtd++;
}

void ativos_inimigos_atualizar_e_renderizar(AtivosInimigos *ai, int altura_tela) {
    if (!ai) return;
    NoInimigo *atual = ai->head;

    while (atual != NULL) {
        NoInimigo *proximo_no = atual->proximo;
        atual->y += atual->velocidade;

        // CORES VIVAS: Laranja brilhante para aglomerados e Vermelho para normais
        Color cor_corpo = atual->e_aglomerado ? ORANGE : RED;
        Color cor_borda = YELLOW;

        // Renderização Garantida: Corpo retangular + Ponta do Inimigo apontando para BAIXO
        int larg = 24;
        int alt = 20;
        int px = (int)atual->x - larg / 2;
        int py = (int)atual->y;

        // Desenha o corpo da nave inimiga
        DrawRectangle(px, py, larg, alt, cor_corpo);
        DrawRectangleLines(px, py, larg, alt, cor_borda); // Borda amarela em destaque

        // Cabine central amarela para alto contraste sobre o fundo preto
        DrawRectangle(px + 8, py + 12, 8, 6, YELLOW);

        // Se o inimigo passar do limite inferior da tela, remove da Lista Dupla em O(1)
        if (atual->y > altura_tela + 30) {
            if (atual->anterior) atual->anterior->proximo = atual->proximo;
            else ai->head = atual->proximo;

            if (atual->proximo) atual->proximo->anterior = atual->anterior;
            else ai->tail = atual->anterior;

            free(atual);
            ai->qtd--;
        }
        atual = proximo_no;
    }
}

// Função RECURSIVA de Explosão em Cadeia para Inimigos Aglomerados
static int destruicao_em_cadeia_recursiva(AtivosInimigos *ai, NoInimigo *centro, float raio_explosao) {
    if (!ai || !centro) return 0;
    int pontos = 100;

    NoInimigo *atual = ai->head;
    while (atual != NULL) {
        NoInimigo *prox = atual->proximo;
        if (atual != centro) {
            Vector2 p1 = { centro->x, centro->y };
            Vector2 p2 = { atual->x, atual->y };
            if (CheckCollisionCircles(p1, raio_explosao, p2, 10.0f)) {
                // Remove o vizinho atingido pela onda de choque
                if (atual->anterior) atual->anterior->proximo = atual->proximo;
                else ai->head = atual->proximo;

                if (atual->proximo) atual->proximo->anterior = atual->anterior;
                else ai->tail = atual->anterior;

                NoInimigo *alvo = atual;
                free(alvo);
                ai->qtd--;

                // Chamada Recursiva se o vizinho também for Aglomerado
                if (atual->e_aglomerado) {
                    pontos += destruicao_em_cadeia_recursiva(ai, atual, raio_explosao);
                } else {
                    pontos += 50;
                }
            }
        }
        atual = prox;
    }
    return pontos;
}

int ativos_inimigos_processar_colisoes(AtivosInimigos *ai, GerenciadorTiros *gt) {
    if (!ai || !gt) return 0;
    NoInimigo *atual = ai->head;
    int pontos_totais = 0;

    while (atual != NULL) {
        NoInimigo *proximo_no = atual->proximo;

        // Raio de colisão ajustado para 16 pixels
        if (tiros_verificar_colisao_alvo(gt, atual->x, atual->y + 10.0f, 16.0f)) {
            if (atual->e_aglomerado) {
                pontos_totais += destruicao_em_cadeia_recursiva(ai, atual, 70.0f);
            } else {
                pontos_totais += 100;
            }

            if (atual->anterior) atual->anterior->proximo = atual->proximo;
            else ai->head = atual->proximo;

            if (atual->proximo) atual->proximo->anterior = atual->anterior;
            else ai->tail = atual->anterior;

            free(atual);
            ai->qtd--;
        }
        atual = proximo_no;
    }
    return pontos_totais;
}

void ativos_inimigos_destruir(AtivosInimigos *ai) {
    if (!ai) return;
    NoInimigo *atual = ai->head;
    while (atual) {
        NoInimigo *temp = atual->proximo;
        free(atual);
        atual = temp;
    }
    free(ai);
}