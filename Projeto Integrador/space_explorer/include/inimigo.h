#ifndef INIMIGO_H
#define INIMIGO_H

#include <stdbool.h>
#include "tiro.h"

typedef struct FilaInimigos FilaInimigos;
typedef struct GerenciadorInimigos AtivosInimigos;

// Fila Dinâmica FIFO (Spawn Queue)
FilaInimigos* fila_inimigos_criar(void);
void fila_inimigos_destruir(FilaInimigos *f);
void fila_inimigos_enqueue(FilaInimigos *f, float x, float y, float velocidade, bool e_aglomerado);
bool fila_inimigos_dequeue(FilaInimigos *f, float *x_out, float *y_out, float *vel_out, bool *aglomerado_out);
int fila_inimigos_qtd(const FilaInimigos *f);

// Gerenciador de Inimigos Ativos na Tela
AtivosInimigos* ativos_inimigos_criar(void);
void ativos_inimigos_destruir(AtivosInimigos *ai);
void ativos_inimigos_adicionar(AtivosInimigos *ai, float x, float y, float velocidade, bool e_aglomerado);
void ativos_inimigos_atualizar_e_renderizar(AtivosInimigos *ai, int altura_tela);

int ativos_inimigos_processar_colisoes(AtivosInimigos *ai, GerenciadorTiros *gt);

#endif