#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int n_alunos = 3;

    // 1. Vetor dinâmico usando calloc (inicia zerado)
    float *notas = (float *) calloc(n_alunos, sizeof(float));
    if (notas == NULL) return 1;

    notas[0] = 8.5;
    notas[1] = 7.0;

    // 2. Redimensionando o vetor para 4 alunos com realloc
    n_alunos = 4;
    float *temp = realloc(notas, n_alunos * sizeof(float));
    if (temp != NULL) {
        notas = temp; // Sempre use uma variável temporária ao checar o realloc
        notas[3] = 9.5;
    }

    for (int i = 0; i < n_alunos; i++) {
        printf("Nota %d: %f \n", i, notas[i]);
    }

    // 3. Liberação do vetor
    free(notas);
    notas = NULL;

    return 0;
}