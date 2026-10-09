#ifndef INVENTARIO_H
#define INVENTARIO_H

#include <stdbool.h>

typedef struct InventarioEspacial InventarioEspacial;

InventarioEspacial* inventario_criar(int capacidade_maxima);
void inventario_destruir(InventarioEspacial *inv);

bool inventario_adicionar_item(InventarioEspacial *inv, int id_item, int quantidade);
bool inventario_remover_item(InventarioEspacial *inv, int id_item, int quantidade);

int inventario_get_qtd_item(const InventarioEspacial *inv, int id_item);

#endif