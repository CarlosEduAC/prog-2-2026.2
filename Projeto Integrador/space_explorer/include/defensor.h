#ifndef DEFENSOR_H
#define DEFENSOR_H

#include <stdbool.h>

// Ponteiro Opaco para o TAD Defensor
typedef struct Defensor Defensor;

Defensor* defensor_criar(float x, float y, float velocidade);
void defensor_destruir(Defensor *d);

void defensor_atualizar(Defensor *d, int largura_tela);
void defensor_renderizar(const Defensor *d);

float defensor_get_x(const Defensor *d);
float defensor_get_y(const Defensor *d);
int defensor_get_vida(const Defensor *d);
void defensor_causar_dano(Defensor *d, int dano);

// Operações da Pilha Dinâmica LIFO (Reversão Temporal)
void defensor_salvar_estado_pilha(Defensor *d);
bool defensor_executar_reversao_temporal(Defensor *d);
int defensor_get_qtd_undo(const Defensor *d);

#endif