#ifndef LISTA_ALUNOS_H
#define LISTA_ALUNOS_H

#include <stdbool.h>

// APENAS o ponteiro opaco é exposto. A struct No é 100% privada ao .c
typedef struct ListaAlunos ListaAlunos;

ListaAlunos* lista_criar(void);
void lista_destruir(ListaAlunos *l);

bool lista_inserir(ListaAlunos *l, int matricula, float nota);
float lista_buscar_nota(const ListaAlunos *l, int matricula);

#endif