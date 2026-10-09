#include "ranking.h"
#include <stdio.h>

static int particionar(RegistroScore *v, int inicio, int fim) {
    int pivo = v[fim].pontos;
    int i = inicio - 1;

    for (int j = inicio; j < fim; j++) {
        if (v[j].pontos >= pivo) { // Ordenação Decrescente
            i++;
            RegistroScore temp = v[i];
            v[i] = v[j];
            v[j] = temp;
        }
    }
    RegistroScore temp = v[i + 1];
    v[i + 1] = v[fim];
    v[fim] = temp;
    return i + 1;
}

void ranking_ordenar_quicksort(RegistroScore *vetor, int inicio, int fim) {
    if (inicio < fim) {
        int p = particionar(vetor, inicio, fim);
        ranking_ordenar_quicksort(vetor, inicio, p - 1);
        ranking_ordenar_quicksort(vetor, p + 1, fim);
    }
}

void ranking_salvar_binario(const char *caminho, RegistroScore *vetor, int qtd) {
    FILE *arq = fopen(caminho, "wb");
    if (!arq) return;
    fwrite(vetor, sizeof(RegistroScore), qtd, arq);
    fclose(arq);
}