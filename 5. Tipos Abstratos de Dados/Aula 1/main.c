#include <stdio.h>
#include "defensor.h"

int main(void) {
    Defensor *d = defensor_criar(400, 100);

    // TESTE DE ENCAPSULAMENTO:
    // Descomente a linha abaixo e tente compilar com gcc:
    // printf("Vida direta: %d\n", d->vida);

    // O compilador vai emitir o erro:
    // "error: dereferencing pointer to incomplete type 'Defensor'"

    defensor_causar_dano(d, 30);
    printf("Vida via Interface do TAD: %d\n", defensor_get_vida(d));

    printcarlos("");

    defensor_destruir(d);
    return 0;
}