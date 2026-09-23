#include <stdio.h>
#include <stdbool.h>

bool esta_ordenado(const int *v, int tam) {
    // 1. CASO BASE 1: Vetor com 0 ou 1 elemento esta sempre ordenado
    if (tam <= 1) {
        return true;
    }

    // 2. CASO BASE 2 (Falha): Se os dois primeiros elementos estão desordenados, interrompe
    if (v[0] > v[1]) {
        return false;
    }

    // 3. PASSO RECURSIVO: Avança o ponteiro do vetor (v + 1) e reduz o tamanho (tam - 1)
    return esta_ordenado(v + 1, tam - 1);
}

int main(void) {
    int v1[] = {2, 5, 8, 12};
    int v2[] = {2, 10, 5, 12};

    printf("v1 esta ordenado? %s\n", esta_ordenado(v1, 4) ? "Sim" : "Nao"); // Sim
    printf("v2 esta ordenado? %s\n", esta_ordenado(v2, 4) ? "Sim" : "Nao"); // Nao

    return 0;
}