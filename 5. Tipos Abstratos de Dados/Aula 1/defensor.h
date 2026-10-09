#ifndef DEFENSOR_H
#define DEFENSOR_H

#include <stdbool.h>

// DECLARAÇÃO INCOMPLETA (Ponteiro Opaco)
// O cliente sabe que 'Defensor' existe, mas NÃO sabe o que há dentro dele!
typedef struct Defensor Defensor;

// Funções Construtoras e Destrutoras (Gerenciamento do Heap)
Defensor* defensor_criar(int x_inicial, int vida_inicial);
void defensor_destruir(Defensor *d);

// Interface de Operações (Comportamento)
void defensor_causar_dano(Defensor *d, int dano);
int defensor_get_vida(const Defensor *d);

#endif