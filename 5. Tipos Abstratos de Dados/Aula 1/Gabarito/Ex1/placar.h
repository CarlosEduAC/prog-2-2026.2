#ifndef PLACAR_H
#define PLACAR_H

#include <stdbool.h>

// DECLARAÇÃO INCOMPLETA (Ponteiro Opaco)
typedef struct Placar Placar;

Placar* placar_criar(const char *nome);
void placar_destruir(Placar *p);

void placar_adicionar_pontos(Placar *p, int qtd);
void placar_remover_vida(Placar *p);

int placar_get_pontos(const Placar *p);
int placar_get_vidas(const Placar *p);
const char* placar_get_nome(const Placar *p);

#endif