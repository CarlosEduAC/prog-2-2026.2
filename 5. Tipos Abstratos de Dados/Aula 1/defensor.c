#include "defensor.h"
#include <stdlib.h>

// DEFINIÇÃO CONCRETA (Privada apenas dentro deste arquivo .c)
struct Defensor {
    int x;
    int vida;
};

Defensor* defensor_criar(int x_inicial, int vida_inicial) {
    Defensor *d = (Defensor *) malloc(sizeof(Defensor));
    if (d == NULL) return NULL; // Validação de memória

    d->x = x_inicial;
    // Garantia da Invariante de Estado: Vida nunca pode iniciar negativa
    d->vida = (vida_inicial > 0) ? vida_inicial : 100;

    return d;
}

void defensor_causar_dano(Defensor *d, int dano) {
    if (d == NULL || dano <= 0) return;

    d->vida -= dano;
    if (d->vida < 0) d->vida = 0; // Proteção contra estado inválido
}

int defensor_get_vida(const Defensor *d) {
    if (d == NULL) return 0;
    return d->vida;
}

void defensor_destruir(Defensor *d) {
    if (d != NULL) {
        free(d);
    }
}