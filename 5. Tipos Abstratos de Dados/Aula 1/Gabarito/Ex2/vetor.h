#ifndef VETOR_H
#define VETOR_H

#include <stdbool.h>

typedef struct VetorDinamico VetorDinamico;

VetorDinamico* vetor_criar(int capacidade_inicial);
void vetor_destruir(VetorDinamico *v);

bool vetor_inserir(VetorDinamico *v, int elemento);
bool vetor_obter(const VetorDinamico *v, int indice, int *valor_out);
int vetor_get_tamanho(const VetorDinamico *v);

#endif