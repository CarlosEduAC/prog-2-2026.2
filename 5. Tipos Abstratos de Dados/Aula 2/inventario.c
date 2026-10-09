#include "inventario.h"
#include <stdlib.h>

typedef struct {
    int id_item;
    int quantidade;
} ItemSlot;

struct InventarioEspacial {
    ItemSlot *slots;
    int capacidade;
    int total_itens;
};

InventarioEspacial* inventario_criar(int capacidade_maxima) {
    if (capacidade_maxima <= 0) return NULL;

    InventarioEspacial *inv = (InventarioEspacial *) malloc(sizeof(InventarioEspacial));
    if (inv == NULL) return NULL;

    inv->slots = (ItemSlot *) calloc(capacidade_maxima, sizeof(ItemSlot));
    if (inv->slots == NULL) {
        free(inv); // Rollback em caso de falha
        return NULL;
    }

    inv->capacidade = capacidade_maxima;
    inv->total_itens = 0;
    return inv;
}

bool inventario_adicionar_item(InventarioEspacial *inv, int id_item, int quantidade) {
    if (inv == NULL || id_item < 0 || id_item >= inv->capacidade || quantidade <= 0) {
        return false;
    }

    if (inv->total_itens + quantidade > inv->capacidade) {
        return false; // Preserva a invariante de capacidade
    }

    inv->slots[id_item].id_item = id_item;
    inv->slots[id_item].quantidade += quantidade;
    inv->total_itens += quantidade;
    return true;
}

bool inventario_remover_item(InventarioEspacial *inv, int id_item, int quantidade) {
    if (inv == NULL || id_item < 0 || id_item >= inv->capacidade || quantidade <= 0) {
        return false;
    }

    if (inv->slots[id_item].quantidade < quantidade) {
        return false; // Não é possível remover mais do que existe
    }

    inv->slots[id_item].quantidade -= quantidade;
    inv->total_itens -= quantidade;
    return true;
}

int inventario_get_qtd_item(const InventarioEspacial *inv, int id_item) {
    if (inv == NULL || id_item < 0 || id_item >= inv->capacidade) {
        return 0;
    }
    return inv->slots[id_item].quantidade;
}

void inventario_destruir(InventarioEspacial *inv) {
    if (inv != NULL) {
        free(inv->slots); // Libera o vetor interno primeiro
        free(inv);        // Libera a estrutura principal
    }
}