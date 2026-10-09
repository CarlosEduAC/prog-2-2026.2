#ifndef TIRO_H
#define TIRO_H

#include <stdbool.h>

typedef struct GerenciadorTiros GerenciadorTiros;

GerenciadorTiros* tiros_criar(void);
void tiros_destruir(GerenciadorTiros *gt);

void tiros_adicionar(GerenciadorTiros *gt, float x, float y, float vel_y);
void tiros_atualizar_e_renderizar(GerenciadorTiros *gt, int altura_tela);
bool tiros_verificar_colisao_alvo(GerenciadorTiros *gt, float alvo_x, float alvo_y, float raio_alvo);

#endif